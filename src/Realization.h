/**
 * @file Realization.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_REALIZATION_H
#define ICP_PROJECT_REALIZATION_H

#include "Relationship.h"

/**
 * Entity for realization (special type of relationship)
 */
class Realization: public Relationship
{
  public:
    /**
     * Constructor for initializing with known first and second class in realization
     *
     * @param firstClass Pointer to the first class in realization
     * @param secondClass Pointer to the second class in realization
     * @param name Name of the realization (optional)
     */
    Realization(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): Relationship{firstClass, secondClass, name} {};
};

#endif //ICP_PROJECT_REALIZATION_H
