/**
 * @file Relationship.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_RELATIONSHIP_H
#define ICP_PROJECT_RELATIONSHIP_H

#include "Class.h"

/**
 * General entity for class relationships
 */
class Relationship
{
    /**
     * Pointer to the first class added to relationship
     */
    Class *firstClass;
    /**
     * Pointer to the second class added to relationship
     */
    Class *secondClass;
    /**
     * Name of the relationship
     */
    std::string name;

  protected:
    /**
     * Constructor for initializing with known first and second class in relationship
     *
     * @param firstClass Pointer to the first class in relationship
     * @param secondClass Pointer to the second class in relationship
     * @param name Name of the relationship (optional)
     */
    Relationship(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): firstClass{firstClass}, secondClass{secondClass}, name{name} {};

  public:
    /**
     * Swaps first and second class of relationship (turns over the arrow)
     */
    void swapClasses()
    {
        std::swap(firstClass, secondClass);
    }

    /**
     * Getter for the first class of relationship
     *
     * @return Pointer to the first class
     */
    Class *getFirstClass() const
    {
        return firstClass;
    }

    /**
     * Getter for the second class of relationship
     *
     * @return Pointer to the second class
     */
    Class *getSecondClass() const
    {
        return secondClass;
    }

    /**
     * Getter for relationship name
     *
     * @return Name of the relationship
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for relationship name
     *
     * @param newName New name for relationship
     */
    void setName(const std::string &newName)
    {
        name = newName;
    }

    /**
     * Equals operator
     *
     * @param other Relationship to compare with
     * @return Are relationships equal?
     */
    virtual bool operator==(Relationship &other)
    {
        if (typeid(other) == typeid(*this)) {
            return firstClass == other.firstClass && secondClass == other.secondClass && name == other.name;
        }

        return false;
    }

    /**
     * Not equals operator
     *
     * @param other Relationship to compare with
     * @return Are relationships not equal?
     */
    virtual bool operator!=(Relationship &other)
    {
        return !operator==(other);
    }

    /**
     * Default virtual destructor for converting class to polymorphic one
     */
    virtual ~Relationship() = default;
};

#endif //ICP_PROJECT_RELATIONSHIP_H
