/**
 * @file ClassMethodType.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_METHODTYPE_H
#define ICP_PROJECT_CLASS_METHODTYPE_H

#include <cstdint>
#include <string>

/**
 * Enumeration for class method type
 *
 * @par Inspired by: https://stackoverflow.com/a/53284026
 */
class ClassMethodType
{
  public:
    /**
     * Enumeration type for items of this class
     *
     * @par ClassMethodType class needs to have (de)serialization methods
     * which are the thing classic C++ doesn't know
     */
    enum Value: uint8_t {
        /**
         * Classic method
         */
        NORMAL,
        /**
         * Abstract method (without implementation/body)
         */
        ABSTRACT
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
    ClassMethodType() = default;
    /**
     * Classic constructor for creating object from enumeration
     *
     * @param value Selected enumerated value
     */
    constexpr ClassMethodType(Value value): storedValue{value} {}; // NOLINT(google-explicit-constructor)


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
    constexpr bool operator==(ClassMethodType other) const
    {
        return storedValue == other.storedValue;
    }

    /**
     * Not equals operator
     *
     * @param other Access modifier to compare with
     * @return Are access modifier not equal?
     */
    constexpr bool operator!=(ClassMethodType other) const
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
     * @return Instance of ClassMethodType
     * @throw std::invalid_argument Invalid value for deserialization
     */
    static ClassMethodType deserialize(std::string &serializedForm);
};

#endif //ICP_PROJECT_CLASS_METHODTYPE_H
