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
 * Finds class by name
 *
 * @param name Name of the class to search for
 * @return Pointer to found class
 * @throw std::invalid_argument Non-existing class with this name
 */
Class *ClassDiagram::findClassByName(std::string name)
{
    for (Class &currClass: classes) {
        if (currClass.getName() == name) {
            return &currClass;
        }
    }

    throw std::invalid_argument{"Class with name \"" + name + "\" doesn't exist in class diagram"};
}
