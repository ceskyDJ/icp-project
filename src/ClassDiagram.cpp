/**
 * @file ClassDiagram.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

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
Class *ClassDiagram::findClassByName(std::string name)
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
