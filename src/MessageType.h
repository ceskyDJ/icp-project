/**
 * @file MessageType.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_MESSAGE_TYPE_H
#define ICP_PROJECT_MESSAGE_TYPE_H

#include <cstdint>
#include <string>

/**
 * Enumeration for type of sequence diagram message
 *
 * @par Inspired by: https://stackoverflow.com/a/53284026
 */
class MessageType
{
  public:
    /**
     * Enumeration type for items of this class
     *
     * @par MessageType class needs to have (de)serialization methods
     * which are the thing classic C++ doesn't know
     */
    enum Value: uint8_t {
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

  private:
    /**
     * Stored (selected) value
     */
    Value storedValue;

  public:
    /**
     * Default implicit class constructor
     */
    MessageType() = default;
    /**
     * Classic constructor for creating object from enumeration
     *
     * @param value Selected enumerated value
     */
    constexpr MessageType(Value value): storedValue{value} {}; // NOLINT(google-explicit-constructor)


    /**
     * Delete conversion operator to boolean
     */
    explicit operator bool() = delete;

    /**
     * Implicit conversion operator for stored value (usage in return statements, etc.)
     *
     * @return Stored value
     */
    constexpr operator Value() const // NOLINT(google-explicit-constructor)
    {
        return storedValue;
    }

    /**
     * Equals operator
     *
     * @param other Access modifier to compare with
     * @return Are access modifiers equal?
     */
    constexpr bool operator==(MessageType other) const
    {
        return storedValue == other.storedValue;
    }

    /**
     * Not equals operator
     *
     * @param other Access modifier to compare with
     * @return Are access modifier not equal?
     */
    constexpr bool operator!=(MessageType other) const
    {
        return storedValue != other.storedValue;
    }

    /**
     * Converts to string form for persistence, etc.
     *
     * @return String form of object state
     */
    std::string serialize();

    /**
     * Creates an object of this class using deserialization
     *
     * @param serializedForm Serialized (string) from of the object
     * @return Instance of MessageType
     * @throw std::invalid_argument Invalid value for deserialization
     */
    static MessageType deserialize(std::string &serializedForm);
};

#endif //ICP_PROJECT_MESSAGE_TYPE_H
