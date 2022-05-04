/**
 * @file
 * TODO: File description (short information about what is inside)
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include <stdexcept>
#include "MessageType.h"

/**
 * Converts to string form for persistence, etc.
 *
 * @return String form of object state
 */
std::string MessageType::serialize()
{
    switch (storedValue) {
        case SYNC:
            return "SYNC";
        case ASYNC:
            return "ASYNC";
        case CREATE:
            return "CREATE";
        case DESTROY:
            return "DESTROY";
        case REPLY:
            return "REPLY";
    }
}

/**
 * Creates an object of this class using deserialization
 *
 * @param serializedForm Serialized (string) from of the object
 * @return Instance of MessageType
 * @throw std::invalid_argument Invalid value for deserialization
 */
MessageType MessageType::deserialize(std::string &serializedForm)
{
    if (serializedForm == "SYNC") {
        return MessageType::SYNC;
    } else if (serializedForm == "ASYNC") {
        return MessageType::ASYNC;
    } else if (serializedForm == "CREATE") {
        return MessageType::CREATE;
    } else if (serializedForm == "DESTROY") {
        return MessageType::DESTROY;
    } else if (serializedForm == "REPLY") {
        return MessageType::REPLY;
    } else {
        throw std::invalid_argument("Cannot deserialized MessageType from: \""+ serializedForm + "\"");
    }
}
