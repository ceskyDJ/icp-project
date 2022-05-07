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
 * Removes actor from sequence diagram
 *
 * @param actorToRemove Actor to remove from sequence diagram
 * @throw std::invalid_argument Actor is not in sequence diagram
 */
void SequenceDiagram::removeActor(Actor actorToRemove)
{
    for (auto iterator = actors.begin(); iterator != actors.end(); iterator++) {
        if (*iterator == actorToRemove) {
            actors.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Actor is not in sequence diagram"};
}

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
 * Removes object from sequence diagram
 *
 * @param objectToRemove Object to remove from sequence diagram
 * @throw std::invalid_argument Object is not in sequence diagram
 */
void SequenceDiagram::removeObject(Object objectToRemove)
{
    for (auto iterator = objects.begin(); iterator != objects.end(); iterator++) {
        if (*iterator == objectToRemove) {
            objects.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Object is not in sequence diagram"};
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

/**
 * Removes message from sequence diagram
 *
 * @param messageToRemove Message to remove from sequence diagram
 * @throw std::invalid_argument Message is not in sequence diagram
 */
void SequenceDiagram::removeMessage(Message messageToRemove)
{
    for (auto iterator = messages.begin(); iterator != messages.end(); iterator++) {
        if (*iterator == messageToRemove) {
            messages.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Object is not in sequence diagram"};
}
