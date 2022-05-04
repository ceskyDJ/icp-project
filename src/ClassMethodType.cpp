/**
 * @file
 * TODO: File description (short information about what is inside)
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include <stdexcept>
#include "ClassMethodType.h"

/**
 * Converts to string form for persistence, etc.
 *
 * @return String form of object state
 */
std::string ClassMethodType::serialize()
{
    switch (storedValue) {
        case NORMAL:
            return "NORMAL";
        case ABSTRACT:
            return "ABSTRACT";
    }
}

/**
 * Creates an object of this class using deserialization
 *
 * @param serializedForm Serialized (string) from of the object
 * @return Instance of ClassMethodType
 * @throw std::invalid_argument Invalid value for deserialization
 */
ClassMethodType ClassMethodType::deserialize(std::string &serializedForm)
{
    if (serializedForm == "NORMAL") {
        return ClassMethodType::NORMAL;
    } else if (serializedForm == "ABSTRACT") {
        return ClassMethodType::ABSTRACT;
    } else {
        throw std::invalid_argument("Cannot deserialized ClassMethodType from: \""+ serializedForm + "\"");
    }
}
