/**
 * @file ClassDiagram.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_DIAGRAM_H
#define ICP_PROJECT_CLASS_DIAGRAM_H

#include "Class.h"
#include "Relationship.h"
#include "ClassDiagramMemento.h"
#include "Aggregation.h"
#include "Composition.h"
#include "DirectedAssociation.h"
#include "Generalization.h"
#include "Realization.h"
#include "UndirectedAssociation.h"

/**
 * Entity for complete class diagram
 */
class ClassDiagram
{
    /**
     * Pointers to classes contained in class diagram
     */
    std::vector<Class *> classes;
    /**
     * Pointers to relationships between classes
     */
    std::vector<Relationship *> relationships;

  public:
    /**
     * Constructor for empty class diagram
     */
    ClassDiagram(): classes{}, relationships{} {};
    /**
     * Constructor for initializing class diagram with known classes and relationships
     *
     * @param classes Pointers to classes
     * @param relationships Pointers to relationships between classes
     */
    ClassDiagram(
        std::vector<Class *> classes,
        std::vector<Relationship *> relationships
    ): classes{classes}, relationships{relationships} {};

    /**
     * Getter for classes
     *
     * @return Vector of pointers to stored classes
     */
    std::vector<Class *> &getClasses()
    {
        return classes;
    }

    /**
     * Constant getter for classes
     *
     * @return Vector of pointers to stored classes
     */
    const std::vector<Class *> &getClasses() const
    {
        return classes;
    }

    /**
     * Setter for classes
     *
     * @param newClasses New vector of pointers to classes to store
     */
    void setClasses(std::vector<Class *> &newClasses)
    {
        classes = newClasses;
    }

    /**
     * Adds a new class to diagram
     *
     * @param newClass Pointer to new class to add
     */
    void addClass(Class *newClass)
    {
        classes.push_back(newClass);
    }

    /**
     * Removes class from diagram
     *
     * @param classToRemove Pointer to class to remove from diagram
     * @throw std::invalid_argument Class is not in diagram
     */
    void removeClass(Class *classToRemove);

    /**
     * Finds class by name
     *
     * @param name Name of the class to search for
     * @return Pointer to found class
     * @throw std::invalid_argument Non-existing class with this name
     */
    Class *findClassByName(const std::string &name) const;

    /**
     * Finds class by name
     *
     * @param name Name of the class to search for
     * @return Pointer to found class
     * @throw std::invalid_argument Non-existing class with this name
     */
    Class *findClassByName(const std::string &&name) const
    {
        return findClassByName(name);
    }

    /**
     * Getter for relationships between classes
     *
     * @return Vector of pointers to relationships
     */
    std::vector<Relationship *> &getRelationships()
    {
        return relationships;
    }

    /**
     * Constant getter for relationships between classes
     *
     * @return Vector of pointers to relationships
     */
    const std::vector<Relationship *> &getRelationships() const
    {
        return relationships;
    }

    /**
     * Adds a new relationship to diagram
     *
     * @param newRelationship Pointer to new relationship to add
     */
    void addRelationship(Relationship *newRelationship)
    {
        relationships.push_back(newRelationship);
    }

    /**
     * Removes relationship from class diagram
     *
     * @param relationshipToRemove Relationship to remove
     * @throw std::invalid_argument Relationship is not in class diagram
     */
    void removeRelationship(Relationship *relationshipToRemove);

    /**
     * Setter for relationships between classes
     *
     * @param newRelationships New vector of pointers to relationships
     */
    void setRelationships(std::vector<Relationship *> &newRelationships)
    {
        relationships = newRelationships;
    }

    /**
     * Creates memento of current state
     *
     * @return Created memento
     */
    ClassDiagramMemento createMemento();

    /**
     * Sets state from memento
     *
     * @param memento Memento to use
     */
    void setMemento(const ClassDiagramMemento &memento);
};

/**
 * Creates a deep clone of classes
 *
 * @param sourceClasses Classes to clone (as pointers)
 * @return Pointers to newly allocated space with classes deep clone and map of old and new pointers (in tuple)
 */
inline std::tuple<std::vector<Class *>, std::map<Class *, Class *>> deepCloneClasses(
    const std::vector<Class *> &sourceClasses
);

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
);

#endif //ICP_PROJECT_CLASS_DIAGRAM_H
