/**
 * @file Aggregation.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_AGGREGATION_H
#define ICP_PROJECT_AGGREGATION_H

#include "Relationship.h"

/**
 * Entity for aggregation (special type of relationship)
 */
class Aggregation: public Relationship
{
  public:
    /**
     * Constructor for initializing with known first and second class in aggregation
     *
     * @param firstClass Pointer to the first class in aggregation
     * @param secondClass Pointer to the second class in aggregation
     * @param name Name of the aggregation (optional)
     */
    Aggregation(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): Relationship{firstClass, secondClass, name} {};
};

#endif //ICP_PROJECT_AGGREGATION_H
