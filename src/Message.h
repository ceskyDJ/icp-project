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
#include "MethodReference.h"

/**
 * Message from sequence diagram
 */
class Message
{
  public:
    // Type names for better understandability
    /**
     * Node that sends messages
     */
    using MessageSender = MessageNode;
    /**
     * Node that receives messages
     */
    using MessageRecipient = MessageNode;

  private:
    /**
     * Pointer to method the message is bind to
     */
    MethodReference method;
    /**
     * Type of the message
     */
    MessageType type;
    /**
     * Node sending the message
     */
    MessageSender *messageSender;
    /**
     * Node receiving the message
     */
    MessageRecipient *messageRecipient;
    /**
     * Time when the message should be sent (value at timeline, normalized - interval \<0; 1\>)
     */
    double sendingTime;

  public:
    /**
     * Constructor for initializing with known name, type of the message and sender and recipient nodes
     *
     * @param method Pointer to method the message is bind to
     * @param messageType Type of the message
     * @param messageSender Pointer to node sending the message
     * @param messageRecipient Pointer to node receiving the message
     * @param sendingTime Time when to send the message (at timeline, normalized - interval \<0; 1\>)
     */
    Message(
            MethodReference method,
            MessageType messageType,
            MessageSender *messageSender,
            MessageRecipient *messageRecipient,
            double sendingTime
    ): method{method}, type{messageType}, messageSender{messageSender}, messageRecipient{messageRecipient},
        sendingTime{sendingTime} {};

    /**
     * Getter for bind method
     *
     * @return Pointer to method the message is bind to
     */
    MethodReference getMethod() const
    {
        return method;
    }

    /**
     * Setter for bind method
     *
     * @param newMethod Pointer to new method message is bind to
     */
    void setName(MethodReference newMethod)
    {
        method = newMethod;
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
     * @return Pointer to message sending node
     */
    MessageSender *getMessageSender() const
    {
        return messageSender;
    }

    /**
     * Setter for message sender
     *
     * @param newMessageSender Pointer to new node sending the message
     */
    void setMessageSender(MessageSender *newMessageSender)
    {
        messageSender = newMessageSender;
    }

    /**
     * Getter for message recipient
     *
     * @return Pointer to message receiving node
     */
    MessageRecipient *getMessageRecipient() const
    {
        return messageRecipient;
    }

    /**
     * Setter for message recipient
     *
     * @param newMessageRecipient Pointer to new node receiving the message
     */
    void setMessageRecipient(MessageRecipient *newMessageRecipient)
    {
        messageRecipient = newMessageRecipient;
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

    /**
     * Equals operator
     *
     * @param other Message to compare with
     * @return Are both messages equal?
     */
    bool operator==(Message &other)
    {
        return method->getName() == other.method->getName() && type == other.type && messageSender == other.messageSender
            && messageRecipient == other.messageRecipient && sendingTime == other.sendingTime;
    }

    /**
     * Not equals operator
     *
     * @param other Message to compare with
     * @return Are both messages not equal?
     */
    bool operator!=(Message &other)
    {
        return !operator==(other);
    }
};

#endif //ICP_PROJECT_MESSAGE_H
