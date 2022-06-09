/**
 * @file DestroyMessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef DESTROYMESSAGELINE_H
#define DESTROYMESSAGELINE_H

#include "MessageLine.h"

/**
 * Represents destroy message in sequence diagram.
 */
class DestroyMessageLine : public MessageLine
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    DestroyMessageLine(SceneUpdateObservable *sceneUpdateObservable, SequenceDiagram *sequenceDiagram);
    void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                    Message *msg, ClassReference classRef);
};

#endif // DESTROYMESSAGELINE_H
