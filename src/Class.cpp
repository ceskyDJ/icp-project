/**
 * @file Class.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "ClassMethod.h"
#include "Class.h"

/**
 * Finds class method by its name
 *
 * @param nameToFind Name of the class method search for
 * @return Pointer to found class method
 * @throw std::invalid_argument Non-existing class method with searched name in this class
 */
ClassMethod *Class::findMethodByName(std::string nameToFind)
{
    for (ClassMethod &method: methods) {
        if (method.getName() == nameToFind) {
            return &method;
        }
    }

    throw std::invalid_argument{"Class method with name \"" + name + "\" doesn't exist in the class"};
}