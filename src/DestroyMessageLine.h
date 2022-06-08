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
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    explicit DestroyMessageLine(SequenceDiagram *sequenceDiagram);
    void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                    Message *msg, ClassReference classRef);
};

#endif // DESTROYMESSAGELINE_H
