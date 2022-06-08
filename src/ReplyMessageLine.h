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
    ReplyMessageLine();
    void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                    Message *msg, ClassReference classRef);
};

#endif // REPLYMESSAGELINE_H
