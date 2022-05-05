/**
 * @file Composition.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_COMPOSITION_H
#define ICP_PROJECT_COMPOSITION_H

#include "Relationship.h"

/**
 * Entity for composition (special type of relationship)
 */
class Composition: public Relationship
{
  public:
    /**
     * Constructor for initializing with known first and second class in composition
     *
     * @param firstClass Pointer to the first class in composition
     * @param secondClass Pointer to the second class in composition
     * @param name Name of the composition (optional)
     */
    Composition(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): Relationship{firstClass, secondClass, name} {};
};

#endif //ICP_PROJECT_COMPOSITION_H
