/**
 * @file ClassType.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include <stdexcept>
#include "ClassType.h"

/**
 * Converts to string form for persistence, etc.
 *
 * @return String form of object state
 */
std::string ClassType::serialize()
{
    switch (storedValue) {
        case NORMAL_CLASS:
            return "NORMAL_CLASS";
        case ABSTRACT_CLASS:
            return "ABSTRACT_CLASS";
        case INTERFACE:
            return "INTERFACE";
    }

    return "";
}

/**
 * Creates an object of this class using deserialization
 *
 * @param serializedForm Serialized (string) from of the object
 * @return Instance of ClassType
 * @throw std::invalid_argument Invalid value for deserialization
 */
ClassType ClassType::deserialize(std::string &serializedForm)
{
    if (serializedForm == "NORMAL_CLASS") {
        return ClassType::NORMAL_CLASS;
    } else if (serializedForm == "ABSTRACT_CLASS") {
        return ClassType::ABSTRACT_CLASS;
    } else if (serializedForm == "INTERFACE") {
        return ClassType::INTERFACE;
    } else {
        throw std::invalid_argument("Cannot deserialized ClassType from: \""+ serializedForm + "\"");
    }
}
