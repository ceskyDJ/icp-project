/**
 * @file ClassDiagram.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include <map>
#include "ClassDiagram.h"
#include "Class.h"

/**
 * Removes class from diagram
 *
 * @param classToRemove Pointer to class to remove from diagram
 * @throw std::invalid_argument Class is not in diagram
 */
void ClassDiagram::removeClass(Class *classToRemove)
{
    for (auto iterator = classes.begin(); iterator != classes.end(); iterator++) {
        if (*iterator == classToRemove) {
            classes.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Class is not in class diagram"};
}

/**
 * Finds class by name
 *
 * @param name Name of the class to search for
 * @return Pointer to found class
 * @throw std::invalid_argument Non-existing class with this name
 */
Class *ClassDiagram::findClassByName(const std::string &name) const
{
    for (Class *currClass: classes) {
        if (currClass->getName() == name) {
            return currClass;
        }
    }

    throw std::invalid_argument{"Class with name \"" + name + "\" doesn't exist in class diagram"};
}

/**
 * Removes relationship from class diagram
 *
 * @param relationshipToRemove Relationship to remove
 * @throw std::invalid_argument Relationship is not in class diagram
 */
void ClassDiagram::removeRelationship(Relationship *relationshipToRemove)
{
    for (auto iterator = relationships.begin(); iterator != relationships.end(); iterator++) {
        if (*iterator == relationshipToRemove) {
            relationships.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Relationship is not in class diagram"};
}

/**
 * Creates memento of current state
 *
 * @return Created memento
 */
ClassDiagramMemento ClassDiagram::createMemento()
{
    auto clonedClasses = deepCloneClasses(classes);
    std::vector<Relationship *> clonedRelationships = deepCloneRelationships(relationships, std::get<1>(clonedClasses));

    return ClassDiagramMemento{std::get<0>(clonedClasses), clonedRelationships};
}

/**
 * Sets state from memento
 *
 * @param memento Memento to use
 */
void ClassDiagram::setMemento(const ClassDiagramMemento &memento)
{
    std::map<QUuid, std::set<ReferenceUpdater *>> classReferenceUpdaters;
    std::map<QUuid, std::set<ReferenceUpdater *>> methodReferenceUpdaters;

    // Backup pointers to reference updaters
    for (auto currentClass: classes) {
        classReferenceUpdaters.insert({currentClass->getUuid(), currentClass->getClassReferenceUpdaters()});

        for (auto &currentMethod: currentClass->getMethods()) {
            methodReferenceUpdaters.insert({currentMethod.getUuid(), currentMethod.getMethodReferenceUpdaters()});
        }
    }

    // Deallocate all classes
    for (auto item: classes) {
        delete item;
    }
    // Deallocate all relationships
    for (auto item: relationships) {
        delete item;
    }

    // Clear vectors with pointers to deallocated stuff
    classes.clear();
    relationships.clear();

    // Load data from memento
    auto clonedClasses = deepCloneClasses(memento.classes);
    classes = std::get<0>(clonedClasses);
    relationships = deepCloneRelationships(memento.relationships, std::get<1>(clonedClasses));

    // Recover pointers to reference updaters
    for (auto currentClass: classes) {
        std::set<ReferenceUpdater *> classUpdaters = classReferenceUpdaters.find(currentClass->getUuid())->second;

        // Notify about pointer change
        for (auto item: classUpdaters) {
            item->targetChanged(currentClass);
        }

        // Connect updaters with class
        currentClass->setClassReferenceUpdaters(classUpdaters);

        for (auto &currentMethod: currentClass->getMethods()) {
            std::set<ReferenceUpdater *> methodUpdaters = methodReferenceUpdaters.find(currentMethod.getUuid())->second;

            // Notify about pointer change
            for (auto &item: methodUpdaters) {
                item->targetChanged(&currentMethod);
            }

            // Connect updaters with class method
            currentMethod.setMethodReferenceUpdaters(methodUpdaters);
        }
    }
}

/**
 * Creates a deep clone of classes
 *
 * @param sourceClasses Classes to clone (as pointers)
 * @return Pointers to newly allocated space with classes deep clone and map of old and new pointers (in tuple)
 */
inline std::tuple<std::vector<Class *>, std::map<Class *, Class *>> deepCloneClasses(
    const std::vector<Class *> &sourceClasses
) {
    std::vector<Class *> clonedClasses{};
    std::map<Class *, Class *> classesMap{};

    for (const auto item: sourceClasses) {
        auto classBackup = new Class{*item};
        clonedClasses.push_back(classBackup);
        classesMap.insert({item, classBackup});
    }

    return {clonedClasses, classesMap};
}

/**
 * Creates a deep clone of relationships
 *
 * @param sourceRelationships Relationships to clone (as pointers)
 * @param classMap Map of old and new class pointers (for updating pointers in relationships)
 * @return Pointers to newly allocated space with relationships deep clone
 */
inline std::vector<Relationship *> deepCloneRelationships(
        const std::vector<Relationship *> &sourceRelationships,
        const std::map<Class *, Class *> &classMap
) {
    std::vector<Relationship *> clonedRelationships{};

    // Deep clone relationships
    for (const auto item: sourceRelationships) {
        Relationship *relationshipBackup;

        // It must be done separately, because different relationships have different attributes
        const std::type_info &relationshipType = typeid(*item);
        if (relationshipType == typeid(Aggregation)) {
            auto aggregation = dynamic_cast<Aggregation *>(item);
            relationshipBackup = new Aggregation{*aggregation};
        } else if (relationshipType == typeid(Composition)) {
            auto composition = dynamic_cast<Composition *>(item);
            relationshipBackup = new Composition{*composition};
        } else if (relationshipType == typeid(DirectedAssociation)) {
            auto directedAssociation = dynamic_cast<DirectedAssociation *>(item);
            relationshipBackup = new DirectedAssociation{*directedAssociation};
        } else if (relationshipType == typeid(Generalization)) {
            auto generalization = dynamic_cast<Generalization *>(item);
            relationshipBackup = new Generalization{*generalization};
        } else if (relationshipType == typeid(Realization)) {
            auto realization = dynamic_cast<Realization *>(item);
            relationshipBackup = new Realization{*realization};
        } else if (relationshipType == typeid(UndirectedAssociation)) {
            auto undirectedAssociation = dynamic_cast<UndirectedAssociation *>(item);
            relationshipBackup = new UndirectedAssociation{*undirectedAssociation};
        } else {
            throw std::logic_error{"Unknown relationship"};
        }

        Class *newFirstClass = classMap.find(relationshipBackup->getFirstClass())->second;
        Class *newSecondClass = classMap.find(relationshipBackup->getSecondClass())->second;

        relationshipBackup->setFirstClass(newFirstClass);
        relationshipBackup->setSecondClass(newSecondClass);

        clonedRelationships.push_back(relationshipBackup);
    }

    return clonedRelationships;
}
