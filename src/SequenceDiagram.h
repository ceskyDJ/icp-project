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
    void setActor(std::vector<Actor> &newActors)
    {
        actors = newActors;
    }

    /**
     * Adds a new actor to diagram
     *
     * @param actor New actor to add
     */
    void addActor(Actor &actor)
    {
        actors.push_back(actor);
    }

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
    void addObject(Object &newObject)
    {
        objects.push_back(newObject);
    }

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
    void addMessage(Message &newMessage)
    {
        messages.push_back(newMessage);
    }
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_H
