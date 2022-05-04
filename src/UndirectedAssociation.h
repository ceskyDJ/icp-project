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
     * @param firstClass First class in undirected association
     * @param secondClass Second class in undirected association
     * @param name Name of the undirected association (optional)
     * @param firstClassCardinality Cardinality near the first class
     * @param secondClassCardinality Cardinality near the second class
     */
    UndirectedAssociation(
        Class &firstClass,
        Class &secondClass,
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
};

#endif //ICP_PROJECT_UNDIRECTED_ASSOCIATION_H
