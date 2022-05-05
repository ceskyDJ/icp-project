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
    /**
     * Name of the actor
     */
    std::string name;

  public:
    /**
     * Implicit class constructor
     */
    Actor(): name{} {};
    /**
     * Constructor for initializing with known name
     *
     * @param name Name of the actor
     */
    explicit Actor(std::string name): name{name} {};

    /**
     * Getter for actor's name
     *
     * @return Actor's name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for actor's name
     *
     * @param newName New name for the actor
     */
    void setName(const std::string &newName)
    {
        name = newName;
    }
};

#endif //ICP_PROJECT_ACTOR_H
