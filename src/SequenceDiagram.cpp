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
 * @param actorToRemove Pointer to actor to remove from sequence diagram
 * @throw std::invalid_argument Actor is not in sequence diagram
 */
void SequenceDiagram::removeActor(Actor *actorToRemove)
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
 * @return Pointer to found actor or nullptr when actor with given name isn't in the sequence diagram
 */
Actor *SequenceDiagram::findActorByName(const std::string &name)
{
    for (Actor *actor: actors) {
        if (actor->getName() == name) {
            return actor;
        }
    }

    return nullptr;
}

/**
 * Removes object from sequence diagram
 *
 * @param objectToRemove Pointer to object to remove from sequence diagram
 * @throw std::invalid_argument Object is not in sequence diagram
 */
void SequenceDiagram::removeObject(Object *objectToRemove)
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
 * @return Pointer to found object or nullptr when object with given name isn't in the sequence diagram
 */
Object *SequenceDiagram::findObjectByName(const std::string &name)
{
    for (Object *object: objects) {
        if (object->getName() == name) {
            return object;
        }
    }

    return nullptr;
}

/**
 * Removes message from sequence diagram
 *
 * @param messageToRemove Pointer to message to remove from sequence diagram
 * @throw std::invalid_argument Message is not in sequence diagram
 */
void SequenceDiagram::removeMessage(Message *messageToRemove)
{
    for (auto iterator = messages.begin(); iterator != messages.end(); iterator++) {
        if (*iterator == messageToRemove) {
            messages.erase(iterator);

            return;
        }
    }

    throw std::invalid_argument{"Object is not in sequence diagram"};
}

/**
 * Creates memento of current state
 *
 * @return Created memento
 */
SequenceDiagramMemento SequenceDiagram::createMemento()
{
    std::unordered_map<MessageNode *, MessageNode *> messageNodesMap;

    auto clonedActors = deepCloneActors(actors);
    auto clonedObjects = deepCloneObjects(objects);

    // Connect message node maps
    messageNodesMap.merge(std::get<1>(clonedActors));
    messageNodesMap.merge(std::get<1>(clonedObjects));

    std::vector<Message *> clonedMessages = deepCloneMessages(messages, messageNodesMap);

    return SequenceDiagramMemento{std::get<0>(clonedActors), std::get<0>(clonedObjects), clonedMessages};
}

/**
 * Sets state from memento
 *
 * @param memento Memento to use
 */
void SequenceDiagram::setMemento(const SequenceDiagramMemento &memento)
{
    std::unordered_map<MessageNode *, MessageNode *> messageNodesMap;

    // Deallocate all actors
    for (auto item: actors) {
        delete item;
    }

    // Deallocate all objects
    for (auto item: objects) {
        delete item;
    }

    // Deallocate all messages
    for (auto item: messages) {
        delete item;
    }

    // Clear pointers to deallocated data
    actors.clear();
    objects.clear();
    messages.clear();

    // Load data from memento
    auto clonedActors = deepCloneActors(memento.actors);
    auto clonedObjects = deepCloneObjects(memento.objects);

    // Connect message node maps
    messageNodesMap.merge(std::get<1>(clonedActors));
    messageNodesMap.merge(std::get<1>(clonedObjects));

    actors = std::get<0>(clonedActors);
    objects = std::get<0>(clonedObjects);
    messages = deepCloneMessages(memento.messages, messageNodesMap);
}

/**
 * Creates a deep clone of actors
 *
 * @param sourceActors Actors to clone (as pointers)
 * @return Pointers to newly allocated space with actors deep clone and map of old pointers to new ones
 */
inline std::tuple<std::vector<Actor *>, std::unordered_map<MessageNode *, MessageNode*>> deepCloneActors(
    const std::vector<Actor *> &sourceActors
) {
    std::vector<Actor *> clonedActors{};
    std::unordered_map<MessageNode *, MessageNode *> actorsMap;

    for (const auto item: sourceActors) {
        auto actorBackup = new Actor{*item};
        clonedActors.push_back(actorBackup);

        actorsMap.insert({item, actorBackup});
    }

    return {clonedActors, actorsMap};
}

/**
 * Creates a deep clone of objects
 *
 * @param sourceObjects Objects to clone (as pointers)
 * @return Pointers to newly allocated space with objects deep clone and map of old pointers to new ones
 */
inline std::tuple<std::vector<Object *>, std::unordered_map<MessageNode *, MessageNode *>> deepCloneObjects(
    const std::vector<Object *> &sourceObjects
) {
    std::vector<Object *> clonesObjects{};
    std::unordered_map<MessageNode *, MessageNode *> objectsMap;

    for (const auto item: sourceObjects) {
        auto objectBackup = new Object{*item};
        clonesObjects.push_back(objectBackup);

        objectsMap.insert({item, objectBackup});
    }

    return {clonesObjects, objectsMap};
}

/**
 * Creates a deep clone of messages
 *
 * @param sourceMessages Messages to clone (as pointers)
 * @param messageNodesMap Map of old pointer to the new ones
 * @return Pointers to newly allocated space with messages deep clone
 */
inline std::vector<Message *> deepCloneMessages(
    const std::vector<Message *> &sourceMessages,
    const std::unordered_map<MessageNode *, MessageNode *> &messageNodesMap
) {
    std::vector<Message *> clonedMessages{};

    for (const auto item: sourceMessages) {
        auto messageBackup = new Message{*item};

        MessageNode *newMessageSender = messageNodesMap.find(item->getMessageSender())->second;
        MessageNode *newMessageRecipient = messageNodesMap.find(item->getMessageRecipient())->second;

        messageBackup->setMessageSender(newMessageSender);
        messageBackup->setMessageRecipient(newMessageRecipient);

        clonedMessages.push_back(messageBackup);
    }

    return clonedMessages;
}
