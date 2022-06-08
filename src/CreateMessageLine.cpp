/**
 * @file CreateMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "CreateMessageLine.h"

CreateMessageLine::CreateMessageLine()
{
    linePenOk = QPen{Qt::black, 2, Qt::DashLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::DashLine};
    editNameAllowed = false;
    createFlag = true;
}

/**
 * Initializes itself - store from and to object + store self in those objects.
 */
void CreateMessageLine::initialize(ActivationGraphicsObjectBase *from,
                             ActivationGraphicsObjectBase *to, Message *msg)
{
    fromObject = from;
    toObject = to;
    fromObject->addMessage(this);
    toObject->addMessage(this);
    leftToRight = from->x() < to->x();
    message = msg;
    message->setName(MethodReference{"<<create>>"});
}
