/**
 * @file DirectedAssociation.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_DIRECTED_ASSOCIATION_H
#define ICP_PROJECT_DIRECTED_ASSOCIATION_H

#include "Relationship.h"

/**
 * Entity for directed association (special type of relationship)
 */
class DirectedAssociation: public Relationship
{
  public:
    /**
     * Constructor for initializing with known first and second class in directed association
     *
     * @param firstClass Pointer to the first class in directed association
     * @param secondClass Pointer to the second class in directed association
     * @param name Name of the directed association (optional)
     */
    DirectedAssociation(
        Class *firstClass,
        Class *secondClass,
        std::string name = ""
    ): Relationship{firstClass, secondClass, name} {};
};

#endif //ICP_PROJECT_DIRECTED_ASSOCIATION_H
