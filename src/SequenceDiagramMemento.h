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
    /**
     * Used actors
     *
     * @warning For access this class attribute use getter getActors()
     */
    std::vector<Actor> actors;
    /**
     * Used objects
     *
     * @warning For access this class attribute use getter getObjects()
     */
    std::vector<Object> objects;
    /**
     * Contained messages
     *
     * @warning For access this class attribute use getter getMessages()
     */
    std::vector<Message> messages;

  public:
    /**
     * Implicit non-parametric constructor
     *
     * @par Creates memento with states of empty sequence diagram
     */
    SequenceDiagramMemento(): actors{}, objects{}, messages{} {};

  private:
    friend class SequenceDiagram;
    /**
     * Constructor for defining memento's state
     *
     * @param actors Current actors
     * @param objects Current objects
     * @param messages Current messages
     */
    SequenceDiagramMemento(
        std::vector<Actor> actors,
        std::vector<Object> objects,
        std::vector<Message> messages
    ): actors{actors}, objects{objects}, messages{messages} {};

    /**
     * Getter for actors
     *
     * @return Remembered state of actors
     */
    std::vector<Actor> getActors() {
        return actors;
    }

    /**
     * Getter for objects
     *
     * @return Remembered state of objects
     */
    std::vector<Object> getObjects() {
        return objects;
    }

    /**
     * Getter for messages
     *
     * @return Remembered state of messages
     */
    std::vector<Message> getMessages() {
        return messages;
    }
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_MEMENTO_H
