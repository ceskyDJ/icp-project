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
     * Used actors
     */
    std::vector<Actor> actors;
    /**
     * Used objects
     */
    std::vector<Object> objects;
    /**
     * Contained messages
     */
    std::vector<Message> messages;

  public:
    /**
     * Constructor for empty sequence diagram
     */
    SequenceDiagram(): actors{}, objects{}, messages{} {};
    /**
     * Constructor for initializing sequence diagram with known actors, objects and messages
     *
     * @param actors Actors to use
     * @param objects Objects to use
     * @param messages Messages to use
     */
    SequenceDiagram(
        std::vector<Actor> actors,
        std::vector<Object> objects,
        std::vector<Message> messages
    ): actors{actors}, objects{objects}, messages{messages} {};

    /**
     * Getter for used actors
     *
     * @return Vector of used actors
     */
    std::vector<Actor> &getActors()
    {
        return actors;
    }

    /**
     * Constant getter for used actors
     *
     * @return Vector of used actors
     */
    const std::vector<Actor> &getActors() const
    {
        return actors;
    }

    /**
     * Setter for actors
     *
     * @param newActor New vector of actors to use
     */
    void setActors(std::vector<Actor> &newActors)
    {
        actors = newActors;
    }

    /**
     * Adds a new actor to diagram
     *
     * @param actor New actor to add
     */
    void addActor(Actor actor)
    {
        actors.push_back(actor);
    }

    /**
     * Removes actor from sequence diagram
     *
     * @param actorToRemove Actor to remove from sequence diagram
     * @throw std::invalid_argument Actor is not in sequence diagram
     */
    void removeActor(Actor actorToRemove);

    /**
     * Finds actor by its name
     *
     * @param name Name of the actor to search for
     * @return Found actor
     * @throw std::invalid_argument Actor doesn't exist in sequence diagram
     */
    Actor *findActorByName(std::string name);

    /**
     * Getter for used objects
     *
     * @return Vector of used objects
     */
    std::vector<Object> &getObjects()
    {
        return objects;
    }

    /**
     * Constant getter for used objects
     *
     * @return Vector of used objects
     */
    const std::vector<Object> &getObjects() const
    {
        return objects;
    }

    /**
     * Setter for used objects
     *
     * @param newObjects New vector of objects to use
     */
    void setObjects(std::vector<Object> &newObjects)
    {
        objects = newObjects;
    }

    /**
     * Adds a new object to diagram
     *
     * @param newObject New object to add
     */
    void addObject(Object newObject)
    {
        objects.push_back(newObject);
    }

    /**
     * Removes object from sequence diagram
     *
     * @param objectToRemove Object to remove from sequence diagram
     * @throw std::invalid_argument Object is not in sequence diagram
     */
    void removeObject(Object objectToRemove);

    /**
     * Finds object by its name
     *
     * @param name Name of the object to search for
     * @return Found object
     * @throw std::invalid_argument Object doesn't exist in sequence diagram
     */
    Object *findObjectByName(std::string name);

    /**
     * Getter for used messages
     *
     * @return Vector of used messages
     */
    std::vector<Message> &getMessages()
    {
        return messages;
    }

    /**
     * Constant getter for used messages
     *
     * @return Vector of used messages
     */
    const std::vector<Message> &getMessages() const
    {
        return messages;
    }

    /**
     * Setter for used messages
     *
     * @param newMessages New vector of messages to use
     */
    void setMessages(std::vector<Message> &newMessages)
    {
        messages = newMessages;
    }

    /**
     * Adds a new message to diagram
     *
     * @param newMessage New message to add
     */
    void addMessage(Message newMessage)
    {
        messages.push_back(newMessage);
    }

    /**
     * Removes message from sequence diagram
     *
     * @param messageToRemove Message to remove from sequence diagram
     * @throw std::invalid_argument Message is not in sequence diagram
     */
    void removeMessage(Message messageToRemove);

    /**
     * Creates memento of current state
     *
     * @return Created memento
     */
    SequenceDiagramMemento createMemento()
    {
        return SequenceDiagramMemento{actors, objects, messages};
    }

    /**
     * Sets state from memento
     *
     * @param memento Memento to use
     */
    void setMemento(SequenceDiagramMemento memento)
    {
        actors = memento.getActors();
        objects = memento.getObjects();
        messages = memento.getMessages();
    }
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_H
