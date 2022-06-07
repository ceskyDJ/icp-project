/**
 * @class DestroyMessageLine
 * Represents destroy message in sequence diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef DESTROYMESSAGELINE_H
#define DESTROYMESSAGELINE_H

#include "MessageLine.h"

class DestroyMessageLine : public MessageLine
{
public:
    DestroyMessageLine();
    void initialize(ActivationGraphicsObjectBase *from,
                        ActivationGraphicsObjectBase *to, Message *msg);
};

#endif // DESTROYMESSAGELINE_H
