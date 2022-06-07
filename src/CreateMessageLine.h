/**
 * @class CreateMessageLine
 * Represents create message in sequence diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CREATEMESSAGELINE_H
#define CREATEMESSAGELINE_H

#include "MessageLine.h"

class CreateMessageLine : public MessageLine
{
public:
    CreateMessageLine();
    void initialize(ActivationGraphicsObjectBase *from,
                    ActivationGraphicsObjectBase *to, Message *msg);
};

#endif // CREATEMESSAGELINE_H
