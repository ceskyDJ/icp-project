/**
 * @file Generalization.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_GENERALIZATION_H
#define ICP_PROJECT_GENERALIZATION_H

#include "Relationship.h"

/**
 * Entity for generalization (special type of relationship)
 */
class Generalization: public Relationship
{
  public:
    /**
     * Constructor for initializing with known first and second class in generalization
     *
     * @param firstClass Pointer to the first class in generalization
     * @param secondClass Pointer to the second class in generalization
     * @param name Name of the generalization (optional)
     */
    Generalization(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): Relationship{firstClass, secondClass, name} {};
};

#endif //ICP_PROJECT_GENERALIZATION_H
