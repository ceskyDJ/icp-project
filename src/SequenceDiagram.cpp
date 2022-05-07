/**
 * @file
 * TODO: File description (short information about what is inside)
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "Object.h"
#include "SequenceDiagram.h"

/**
 * Finds actor by its name
 *
 * @param name Name of the actor to search for
 * @return Found actor
 * @throw std::invalid_argument Actor doesn't exist in sequence diagram
 */
Actor *SequenceDiagram::findActorByName(std::string name)
{
    for (Actor &actor: actors) {
        if (actor.getName() == name) {
            return &actor;
        }
    }

    throw std::invalid_argument{"Actor with name \"" + name + "\" doesn't exist in sequence diagram"};
}

/**
 * Finds object by its name
 *
 * @param name Name of the object to search for
 * @return Found object
 * @throw std::invalid_argument Object doesn't exist in sequence diagram
 */
Object *SequenceDiagram::findObjectByName(std::string name)
{
    for (Object &object: objects) {
        if (object.getName() == name) {
            return &object;
        }
    }

    throw std::invalid_argument{"Object with name \"" + name + "\" doesn't exist in sequence diagram"};
}
