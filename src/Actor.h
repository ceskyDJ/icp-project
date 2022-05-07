/**
 * @file Actor.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_ACTOR_H
#define ICP_PROJECT_ACTOR_H

#include <string>
#include "MessageNode.h"

/**
 * Entity for actor from sequence diagram
 */
class Actor: public MessageNode
{
  public:
    /**
     * Implicit class constructor
     */
    Actor(): MessageNode{} {};
    /**
     * Constructor for initializing with known name
     *
     * @param name Name of the actor
     */
    explicit Actor(std::string name): MessageNode{name} {};
};

#endif //ICP_PROJECT_ACTOR_H
