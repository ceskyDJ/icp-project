/**
 * @file SequenceDiagram.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_SEQUENCE_DIAGRAM_H
#define ICP_PROJECT_SEQUENCE_DIAGRAM_H

#include "Actor.h"
#include "Object.h"
#include "Message.h"
#include "SequenceDiagramMemento.h"

/**
 * Entity for complete sequence diagram
 */
class SequenceDiagram
{
    /**
     * Pointers to used actors
     */
    std::vector<Actor *> actors;
    /**
     * Pointers to used objects
     */
    std::vector<Object *> objects;
    /**
     * Pointers to contained messages
     */
    std::vector<Message *> messages;

  public:
    /**
     * Constructor for empty sequence diagram
     */
    SequenceDiagram(): actors{}, objects{}, messages{} {};
    /**
     * Constructor for initializing sequence diagram with known actors, objects and messages
     *
     * @param actors Pointers to actors to use
     * @param objects Pointers to objects to use
     * @param messages Pointers to messages to use
     */
    SequenceDiagram(
        std::vector<Actor *> actors,
        std::vector<Object *> objects,
        std::vector<Message *> messages
    ): actors{actors}, objects{objects}, messages{messages} {};

    /**
     * Getter for used actors
     *
     * @return Pointers to used actors
     */
    std::vector<Actor *> &getActors()
    {
        return actors;
    }

    /**
     * Constant getter for used actors
     *
     * @return Pointer to used actors
     */
    const std::vector<Actor *> &getActors() const
    {
        return actors;
    }

    /**
     * Setter for actors
     *
     * @param newActor New pointers to actors to use
     */
    void setActors(std::vector<Actor *> &newActors)
    {
        actors = newActors;
    }

    /**
     * Adds a new actor to diagram
     *
     * @param actor Pointer to new actor to add
     */
    void addActor(Actor *actor)
    {
        actors.push_back(actor);
    }

    /**
     * Removes actor from sequence diagram
     *
     * @param actorToRemove Pointer to actor to remove from sequence diagram
     * @throw std::invalid_argument Actor is not in sequence diagram
     */
    void removeActor(Actor *actorToRemove);

    /**
     * Finds actor by its name
     *
     * @param name Name of the actor to search for
     * @return Pointer to found actor or nullptr when actor with given name isn't in the sequence diagram
     */
    Actor *findActorByName(const std::string &name);

    /**
     * Finds actor by its name
     *
     * @param name Name of the actor to search for
     * @return Pointer to found actor or nullptr when actor with given name isn't in the sequence diagram
     */
    Actor *findActorByName(const std::string &&name)
    {
        return findActorByName(name);
    }

    /**
     * Getter for used objects
     *
     * @return Pointers to used objects
     */
    std::vector<Object *> &getObjects()
    {
        return objects;
    }

    /**
     * Constant getter for used objects
     *
     * @return Pointers to used objects
     */
    const std::vector<Object *> &getObjects() const
    {
        return objects;
    }

    /**
     * Setter for used objects
     *
     * @param newObjects New pointers to objects to use
     */
    void setObjects(std::vector<Object *> &newObjects)
    {
        objects = newObjects;
    }

    /**
     * Adds a new object to diagram
     *
     * @param newObject Pointer to new object to add
     */
    void addObject(Object *newObject)
    {
        objects.push_back(newObject);
    }

    /**
     * Removes object from sequence diagram
     *
     * @param objectToRemove Pointer to object to remove from sequence diagram
     * @throw std::invalid_argument Object is not in sequence diagram
     */
    void removeObject(Object *objectToRemove);

    /**
     * Finds object by its name
     *
     * @param name Name of the object to search for
     * @return Pointer to found object or nullptr when object with given name isn't in the sequence diagram
     */
    Object *findObjectByName(const std::string &name);

    /**
     * Finds object by its name
     *
     * @param name Name of the object to search for
     * @return Pointer to found object or nullptr when object with given name isn't in the sequence diagram
     */
    Object *findObjectByName(const std::string &&name)
    {
        return findObjectByName(name);
    }

    /**
     * Getter for used messages
     *
     * @return Pointers to used messages
     */
    std::vector<Message *> &getMessages()
    {
        return messages;
    }

    /**
     * Constant getter for used messages
     *
     * @return Pointers to used messages
     */
    const std::vector<Message *> &getMessages() const
    {
        return messages;
    }

    /**
     * Setter for used messages
     *
     * @param newMessages New pointers to messages to use
     */
    void setMessages(std::vector<Message *> &newMessages)
    {
        messages = newMessages;
    }

    /**
     * Adds a new message to diagram
     *
     * @param newMessage Pointer to new message to add
     */
    void addMessage(Message *newMessage)
    {
        messages.push_back(newMessage);
    }

    /**
     * Removes message from sequence diagram
     *
     * @param messageToRemove Pointer to message to remove from sequence diagram
     * @throw std::invalid_argument Message is not in sequence diagram
     */
    void removeMessage(Message *messageToRemove);

    /**
     * Creates memento of current state
     *
     * @return Created memento
     */
    SequenceDiagramMemento createMemento();

    /**
     * Sets state from memento
     *
     * @param memento Memento to use
     */
    void setMemento(const SequenceDiagramMemento &memento);
};

/**
 * Creates a deep clone of actors
 *
 * @param sourceActors Actors to clone (as pointers)
 * @return Pointers to newly allocated space with actors deep clone and map of old pointers to new ones
 */
inline std::tuple<std::vector<Actor *>, std::unordered_map<MessageNode *, MessageNode*>> deepCloneActors(
    const std::vector<Actor *> &sourceActors
);

/**
 * Creates a deep clone of objects
 *
 * @param sourceObjects Objects to clone (as pointers)
 * @return Pointers to newly allocated space with objects deep clone and map of old pointers to new ones
 */
inline std::tuple<std::vector<Object *>, std::unordered_map<MessageNode *, MessageNode *>> deepCloneObjects(
    const std::vector<Object *> &sourceObjects
);

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
);

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_H
