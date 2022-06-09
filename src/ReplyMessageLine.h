/**
 * @file ReplyMessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef REPLYMESSAGELINE_H
#define REPLYMESSAGELINE_H

#include "MessageLine.h"

/**
 * Represents reply message in sequence diagram.
 */
class ReplyMessageLine : public MessageLine
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    ReplyMessageLine(SceneUpdateObservable *sceneUpdateObservable, SequenceDiagram *sequenceDiagram);

    void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                    Message *msg, ClassReference classRef);
};

#endif // REPLYMESSAGELINE_H
