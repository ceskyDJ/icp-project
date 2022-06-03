/**
 * @file SequenceDiagramMemento.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_SEQUENCE_DIAGRAM_MEMENTO_H
#define ICP_PROJECT_SEQUENCE_DIAGRAM_MEMENTO_H

#include <vector>
#include "Actor.h"
#include "Object.h"
#include "Message.h"

/**
 * Memento class for sequence diagram
 */
class SequenceDiagramMemento
{
    friend class SequenceDiagram;

    /**
     * Pointers to used actors
     */
    const std::vector<Actor *> actors;
    /**
     * Pointers to used objects
     */
    const std::vector<Object *> objects;
    /**
     * Pointers to contained messages
     */
    const std::vector<Message *> messages;

    /**
     * Private constructor for defining memento's state
     *
     * @param actors Current pointers to actors
     * @param objects Current pointers to objects
     * @param messages Current pointers to messages
     */
    SequenceDiagramMemento(
        std::vector<Actor *> actors,
        std::vector<Object *> objects,
        std::vector<Message *> messages
    ): actors{actors}, objects{objects}, messages{messages} {};

  public:
    /**
     * Implicit non-parametric constructor
     *
     * @par Creates memento with states of empty sequence diagram
     */
    SequenceDiagramMemento(): actors{}, objects{}, messages{} {};
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_MEMENTO_H
