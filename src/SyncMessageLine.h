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
    SyncMessageLine();
protected:
    void drawArrow(QPainter *painter) const;
};

#endif // SYNCMESSAGELINE_H
