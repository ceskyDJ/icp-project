/**
 * @file MessageType.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_MESSAGE_TYPE_H
#define ICP_PROJECT_MESSAGE_TYPE_H

/**
 * Enumeration for type of sequence diagram message
 */
enum class MessageType
{
    /**
     * Classic message (practically known as calling method)
     */
    SYNC,
    /**
     * Classic message but with asynchronous behaviour (without active waiting on result)
     */
    ASYNC,
    /**
     * Special message for creating new object (practically known as calling constructor)
     */
    CREATE,
    /**
     * Special message for destroying existing object (practically known as calling destructor)
     */
    DESTROY,
    /**
     * Theoretical way (special message) how to handle responding after sending some of the classic messages
     */
    REPLY
};

#endif //ICP_PROJECT_MESSAGE_TYPE_H
