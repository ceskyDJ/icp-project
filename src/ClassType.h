/**
 * @file ClassType.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_TYPE_H
#define ICP_PROJECT_CLASS_TYPE_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * Enumeration for type of the "class" from class diagram
 *
 * @par Inspired by: https://stackoverflow.com/a/53284026
 */
class ClassType
{
  public:
    /**
     * Enumeration type for items of this class
     *
     * @par ClassType class needs to have (de)serialization methods
     * which are the thing classic C++ doesn't know
     */
    enum Value: uint8_t {
        /**
         * Classic class without abstract methods, etc.
         */
        NORMAL_CLASS,
        /**
         * Abstract class with at least one abstract method. No instance could be created from it
         */
        ABSTRACT_CLASS,
        /**
         * Not a class but something like special type of it. Definition of interface (required public methods) for classes
         */
        INTERFACE
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
    ClassType() = default;
    /**
     * Classic constructor for creating object from enumeration
     *
     * @param value Selected enumerated value
     */
    constexpr ClassType(Value value): storedValue{value} {}; // NOLINT(google-explicit-constructor)


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
    constexpr bool operator==(const ClassType &other) const
    {
        return storedValue == other.storedValue;
    }

    /**
     * Not equals operator
     *
     * @param other Access modifier to compare with
     * @return Are access modifier not equal?
     */
    constexpr bool operator!=(const ClassType &other) const
    {
        return !operator==(other);
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
     * @return Instance of ClassType
     * @throw std::invalid_argument Invalid value for deserialization
     */
    static ClassType deserialize(std::string serializedForm);

    /**
     * Getter for all available values
     *
     * @return All available values
     */
    static std::vector<ClassType> values()
    {
        return std::vector<ClassType>{Value::NORMAL_CLASS, Value::ABSTRACT_CLASS, Value::INTERFACE};
    }
};

#endif //ICP_PROJECT_CLASS_TYPE_H
