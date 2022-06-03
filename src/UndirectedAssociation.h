/**
 * @file UndirectedAssociation.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_UNDIRECTED_ASSOCIATION_H
#define ICP_PROJECT_UNDIRECTED_ASSOCIATION_H

#include <limits>
#include "Relationship.h"
#include "Composition.h"

/**
 * Entity for undirected association (without direction arrow) - special type of relationship
 */
class UndirectedAssociation: public Relationship
{
    /**
     * Cardinality at the end, where is the first class of the relationship
     */
    std::string firstClassCardinality;
    /**
     * Cardinality at the end, where is the second class of the relation
     */
    std::string secondClassCardinality;

  public:
    /**
     * Constructor for initializing for known classes in relationship, name and cardinalities
     *
     * @param firstClass Pointer to the first class in undirected association
     * @param secondClass Pointer to the second class in undirected association
     * @param name Name of the undirected association (optional)
     * @param firstClassCardinality Cardinality near the first class
     * @param secondClassCardinality Cardinality near the second class
     */
    UndirectedAssociation(
        Class *firstClass,
        Class *secondClass,
        std::string name = "",
        std::string firstClassCardinality = "",
        std::string secondClassCardinality = ""
    ): Relationship(firstClass, secondClass, name), firstClassCardinality{firstClassCardinality},
        secondClassCardinality{secondClassCardinality} {};

    /**
     * Getter for cardinality near the first class in relationship
     *
     * @return Cardinality near the first class
     */
    std::string getFirstClassCardinality() const
    {
        return firstClassCardinality;
    }

    /**
     * Setter for cardinality near the second class in relationship
     *
     * @param newFirstClassCardinality New cardinality near the second class
     */
    void setFirstClassCardinality(const std::string &newFirstClassCardinality)
    {
        firstClassCardinality = newFirstClassCardinality;
    }

    /**
     * Getter for cardinality near the second class in relationship
     *
     * @return Cardinality near the second class
     */
    std::string getSecondClassCardinality() const
    {
        return secondClassCardinality;
    }

    /**
     * Setter for cardinality near the second class in relationship
     *
     * @param newSecondClassCardinality New cardinality near the second class
     */
    void setSecondClassCardinality(const std::string &newSecondClassCardinality)
    {
        secondClassCardinality = newSecondClassCardinality;
    }

    /**
     * Equals operator for two undirected associations
     *
     * @param other Undirected association to compare with
     * @return Are undirected associations equal?
     */
    bool operator==(UndirectedAssociation &other)
    {
        return Relationship::operator==(other) && firstClassCardinality == other.firstClassCardinality
            && secondClassCardinality == other.secondClassCardinality;
    }

    /**
     * Equals operator for undirected association and some other relationship
     *
     * @return They are relationships of different types, so every time false is returned
     */
    bool operator==(const Relationship &) const override
    {
        return false;
    }

    /**
     * Not equals operator for two undirected associations
     *
     * @param other Undirected association to compare with
     * @return Are undirected associations not equal?
     */
    bool operator!=(const UndirectedAssociation &other) const
    {
        return !operator==(other);
    }

    /**
     * Not equals operator for undirected association and some other relationship
     *
     * @return They are relationships of different types, so every time true is returned
     */
    bool operator!=(const Relationship &) const override
    {
        return true;
    }
};

#endif //ICP_PROJECT_UNDIRECTED_ASSOCIATION_H
