/**
 * @file AccessModifier.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_ACCESS_MODIFIER_H
#define ICP_PROJECT_ACCESS_MODIFIER_H

#include <cstdint>
#include <string>
#include <stdexcept>

/**
 * Enumeration for access modifier for methods and class attributes (used in class diagram)
 *
 * @par Inspired by: https://stackoverflow.com/a/53284026
 */
class AccessModifier
{
  public:
    /**
     * Enumeration type for items of this class
     *
     * @par AccessModifier class needs to have implicit conversions and (de)serialization
     * method which are the thing classic C++ doesn't know
     */
    enum Value: uint8_t {
        /**
         * Completely public, everyone see it
         */
        PUBLIC,
        /**
         * Completely private, only owning class see it
         */
        PRIVATE,
        /**
         * Private for owning class and its children
         */
        PROTECTED,
        /**
         * Public in the same package/module
         */
        PACKAGE_PRIVATE
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
    AccessModifier() = default;
    /**
     * Classic constructor for creating object from enumeration
     *
     * @param value Selected enumerated value
     */
    constexpr AccessModifier(Value value): storedValue{value} {}; // NOLINT(google-explicit-constructor)
    /**
     * Conversion constructor from string
     *
     * @param stringValue Valid string one-character UML representation of access modifier
     * @throw std::invalid_argument Invalid value for conversion
     */
    explicit AccessModifier(std::string &stringValue): storedValue{}
    {
        if (stringValue == "+") {
            storedValue = Value::PUBLIC;
        } else if (stringValue == "-") {
            storedValue = Value::PRIVATE;
        } else if (stringValue == "#") {
            storedValue = Value::PROTECTED;
        } else if (stringValue == "~") {
            storedValue = Value::PACKAGE_PRIVATE;
        } else {
            throw std::invalid_argument("Cannot convert invalid string \""+ stringValue + "\" to AccessModifier");
        }
    }

    /**
     * Conversion operator to string
     *
     * @return One-character string UML representation of access modifier
     */
    explicit operator std::string() // NOLINT(google-explicit-constructor)
    {
        switch (storedValue) {
            case PUBLIC:
                return "+";
            case PRIVATE:
                return "-";
            case PROTECTED:
                return "#";
            case PACKAGE_PRIVATE:
                return "~";
        }
    }

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
    constexpr bool operator==(AccessModifier other) const
    {
        return storedValue == other.storedValue;
    }

    /**
     * Not equals operator
     *
     * @param other Access modifier to compare with
     * @return Are access modifier not equal?
     */
    constexpr bool operator!=(AccessModifier other) const
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
     * @return Instance of AccessModifier
     * @throw std::invalid_argument Invalid value for deserialization
     */
    static AccessModifier deserialize(std::string serializedForm);
};

#endif //ICP_PROJECT_ACCESS_MODIFIER_H
