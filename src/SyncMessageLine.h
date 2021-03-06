/**
 * @file SyncMessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef SYNCMESSAGELINE_H
#define SYNCMESSAGELINE_H

#include "MessageLine.h"

/**
 * Represents synchronous message in sequence diagram.
 */
class SyncMessageLine : public MessageLine
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    SyncMessageLine(SceneUpdateObservable *sceneUpdateObservable, SequenceDiagram *sequenceDiagram);

protected:
    /**
     * Overrided method to draw an arrow at the end of the line.
     *
     * @param painter Recieved painter. Painter has to be rotated and translated to end of the line.
     */
    void drawArrow(QPainter *painter) const;
};

#endif // SYNCMESSAGELINE_H
