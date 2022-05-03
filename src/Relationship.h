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

  public:
    /**
     * Constructor for initializing with known first and second class in relationship
     *
     * @param firstClass First class in relationship
     * @param secondClass Second class in relationship
     * @param name Name of the relationship (optional)
     */
    Relationship(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): firstClass{firstClass}, secondClass{secondClass}, name{name} {};

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
};

#endif //ICP_PROJECT_RELATIONSHIP_H
