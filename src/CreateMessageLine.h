/**
 * @file CreateMessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CREATEMESSAGELINE_H
#define CREATEMESSAGELINE_H

#include "MessageLine.h"

/**
 * Represents create message in sequence diagram.
 */
class CreateMessageLine : public MessageLine
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    CreateMessageLine(SceneUpdateObservable *sceneUpdateObservable, SequenceDiagram *sequenceDiagram);
    /**
     * Initializes itself - store from and to object + store self in those objects.
     */
    void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                    Message *msg, ClassReference classRef);
};

#endif // CREATEMESSAGELINE_H
