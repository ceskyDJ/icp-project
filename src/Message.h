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
    Actor *sendingActor;
    /**
     * Object sending the message (nullptr if sendingActor set)
     */
    Object *sendingObject;
    /**
     * Actor receiving the message (nullptr if receivingObject set)
     */
    Actor *receivingActor;
    /**
     * Object receiving the message (nullptr if receivingActor set)
     */
    Object *receivingObject;
    /**
     * Time when the message should be sent (value at timeline, normalized - interval \<0; 1\>)
     */
    double sendingTime;

    // Type names for better understandability
    using MessageSender = MessageNode;
    using MessageRecipient = MessageNode;

  public:
    /**
     * Constructor for initializing with known name and type of the message
     * for ACTOR sending message and OBJECT receiving message
     *
     * @param name Message name
     * @param messageType Type of the message
     * @param sendingActor Pointer to actor sending the message
     * @param receivingObject Pointer to object receiving the message
     * @param sendingTime Time when to send the message (at timeline, normalized - interval \<0; 1\>)
     */
    Message(
            std::string name,
            MessageType messageType,
            Actor *sendingActor,
            Object *receivingObject,
            double sendingTime
    ): name{name}, type{messageType}, sendingActor{sendingActor}, sendingObject{nullptr},
       receivingActor{nullptr}, receivingObject{receivingObject}, sendingTime{sendingTime} {};

    /**
     * Constructor for initializing with known name and type of the message
     * for OBJECT sending message and OBJECT receiving message
     *
     * @param name Message name
     * @param messageType Type of the message
     * @param sendingObject Pointer to object sending the message
     * @param receivingObject Pointer to object receiving the message
     * @param sendingTime Time when to send the message (at timeline, normalized - interval \<0; 1\>)
     */
    Message(
            std::string name,
            MessageType messageType,
            Object *sendingObject,
            Object *receivingObject,
            double sendingTime
    ): name{name}, type{messageType}, sendingActor{nullptr}, sendingObject{sendingObject},
        receivingActor{nullptr}, receivingObject{receivingObject}, sendingTime{sendingTime} {};

    /**
     * Constructor for initializing with known name and type of the message
     * for OBJECT sending message and ACTOR receiving message
     *
     * @param name Message name
     * @param messageType Type of the message
     * @param sendingObject Pointer to object sending the message
     * @param receivingActor Pointer to actor receiving the message
     * @param sendingTime Time when to send the message (at timeline, normalized - interval \<0; 1\>)
     */
    Message(
            std::string name,
            MessageType messageType,
            Object *sendingObject,
            Actor *receivingActor,
            double sendingTime
    ): name{name}, type{messageType}, sendingActor{nullptr}, sendingObject{sendingObject},
       receivingActor{receivingActor}, receivingObject{nullptr}, sendingTime{sendingTime} {};

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
     * @return Pointer to message sender (sending actor or sending object)
     */
    MessageSender *getMessageSender() const
    {
        if (sendingActor != nullptr) {
            return sendingActor;
        }

        // No other case could happen
        return sendingObject;
    }

    /**
     * Setter for message sender when ACTOR sending the message
     *
     * @param newActor Pointer to sendingActor (new message sender)
     */
    void setMessageSender(Actor *newActor)
    {
        sendingActor = newActor;
        sendingObject = nullptr;
    }

    /**
     * Setter for message sender when OBJECT sending the message
     *
     * @param newSendingObject Pointer to sending object (new message sender)
     */
    void setMessageSender(Object *newSendingObject)
    {
        sendingActor = nullptr;
        sendingObject = newSendingObject;
    }

    /**
     * Getter for message recipient
     *
     * @return Pointer to message recipient (receiving actor or receiving object)
     */
    MessageRecipient *getMessageRecipient() const
    {
        if (receivingActor != nullptr) {
            return receivingActor;
        }

        // No other case could happen
        return receivingObject;
    }

    /**
     * Setter for message recipient when ACTOR receiving the message
     *
     * @param newActor Pointer to receiving actor (new message recipient)
     */
    void setMessageRecipient(Actor *newActor)
    {
        receivingActor = newActor;
        receivingObject = nullptr;
    }

    /**
     * Setter for message recipient when OBJECT receiving the message
     *
     * @param newObject Pointer to receiving object (new message recipient)
     */
    void setMessageRecipient(Object *newObject)
    {
        receivingActor = nullptr;
        receivingObject = newObject;
    }

    /**
     * Getter for sending time
     *
     * @return Time to send the message in form of interval \<0; 1\> (place at timeline)
     */
    double getSendingTime() const {
        return sendingTime;
    }

    /**
     * Setter for sending time
     *
     * @param newSendingTime Time to send the message - place at timeline (interval \<0; 1\>)
     */
    void setSendingTime(double newSendingTime) {
        sendingTime = newSendingTime;
    }
};

#endif //ICP_PROJECT_MESSAGE_H
