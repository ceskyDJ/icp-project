/**
 * @class ReplyMessageLine
 * Represents reply message in sequence diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef REPLYMESSAGELINE_H
#define REPLYMESSAGELINE_H

#include "MessageLine.h"

class ReplyMessageLine : public MessageLine
{
public:
    ReplyMessageLine();
    void initialize(ActivationGraphicsObjectBase *from,
                                 ActivationGraphicsObjectBase *to, Message *msg);
};

#endif // REPLYMESSAGELINE_H
