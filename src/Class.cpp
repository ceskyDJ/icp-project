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
 * @return Pointer to found class method or nullptr when method with searched name isn't in this class
 */
ClassMethod *Class::findMethodByName(const std::string &nameToFind)
{
    for (ClassMethod &method: methods) {
        if (method.getName() == nameToFind) {
            return &method;
        }
    }

    return nullptr;
}
