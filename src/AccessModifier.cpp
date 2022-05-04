/**
 * @file AccessModifier.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include "AccessModifier.h"

/**
 * Converts to string form for persistence, etc.
 *
 * @return String form of object state
 */
std::string AccessModifier::serialize()
{
    switch (storedValue) {
        case PUBLIC:
            return "PUBLIC";
        case PRIVATE:
            return "PRIVATE";
        case PROTECTED:
            return "PROTECTED";
        case PACKAGE_PRIVATE:
            return "PACKAGE_PRIVATE";
    }

    return "";
}

/**
 * Creates an object of this class using deserialization
 *
 * @param serializedForm Serialized (string) from of the object
 * @return Instance of AccessModifier
 * @throw std::invalid_argument Invalid value for deserialization
 */
AccessModifier AccessModifier::deserialize(std::string &serializedForm)
{
    if (serializedForm == "PUBLIC") {
        return AccessModifier::PUBLIC;
    } else if (serializedForm == "PRIVATE") {
        return Value::PRIVATE;
    } else if (serializedForm == "PROTECTED") {
        return Value::PROTECTED;
    } else if (serializedForm == "PACKAGE_PRIVATE") {
        return Value::PACKAGE_PRIVATE;
    } else {
        throw std::invalid_argument("Cannot deserialized AccessModifier from: \""+ serializedForm + "\"");
    }
}
