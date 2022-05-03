/**
 * @file Message.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_MESSAGE_H
#define ICP_PROJECT_MESSAGE_H

#include <string>
#include "MessageType.h"
#include "Actor.h"
#include "Object.h"

/**
 * Message from sequence diagram
 */
class Message
{
    /**
     * Name of the message
     */
    std::string name;
    /**
     * Type of the message
     */
    MessageType type;
    /**
     * Actor sending the message (nullptr if sendingObject set)
     */
    Actor *actor;
    /**
     * Object sending the message (nullptr if actor set)
     */
    Object *sendingObject;
    /**
     * Object receiving the message
     */
    Object *receivingObject;

  public:
    /**
     * Constructor for initializing with known name and type of the message for ACTOR sending message
     *
     * @param name Message name
     * @param messageType Type of the message
     * @param actor Pointer to actor sending the message
     * @param receivingObject Pointer to object receiving the message
     */
    Message(
        std::string name,
        MessageType messageType,
        Actor *actor,
        Object *receivingObject
    ): name{name}, type{messageType}, actor{actor}, sendingObject{nullptr}, receivingObject{receivingObject} {};
    /**
     * Constructor for initializing with known name and type of the message for OBJECT sending message
     *
     * @param name Message name
     * @param messageType Type of the message
     * @param sendingObject Pointer to object sending the message
     * @param receivingObject Pointer to object receiving the message
     */
    Message(
            std::string name,
            MessageType messageType,
            Object *sendingObject,
            Object *receivingObject
    ): name{name}, type{messageType}, actor{nullptr}, sendingObject{sendingObject}, receivingObject{receivingObject} {};

    /**
     * Getter for message name
     *
     * @return Name of the message
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for message name
     *
     * @param newName New message name
     */
    void setName(const std::string &newName)
    {
        name = newName;
    }

    /**
     * Getter for message type
     *
     * @return Message type
     */
    MessageType getType() const
    {
        return type;
    }

    /**
     * Getter for message sender
     *
     * @return Message sender (actor or sending object)
     */
    MessageSender *getMessageSender()
    {
        if (actor != nullptr) {
            return actor;
        }

        // No other case could happen
        return sendingObject;
    }

    /**
     * Setter for message sender when ACTOR sending the message
     *
     * @param newActor Pointer to actor (new message sender)
     */
    void setMessageSender(Actor *newActor)
    {
        actor = newActor;
        sendingObject = nullptr;
    }

    /**
     * Setter for message sender when OBJECT sending the message
     *
     * @param newSendingObject Pointer to sending object (new message sender)
     */
    void setMessageSender(Object *newSendingObject)
    {
        actor = nullptr;
        sendingObject = newSendingObject;
    }
};

#endif //ICP_PROJECT_MESSAGE_H
