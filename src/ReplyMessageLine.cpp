/**
 * @file ReplyMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ReplyMessageLine.h"

/**
 * Set pens for line drawing
 */
ReplyMessageLine::ReplyMessageLine()
{
    linePenOk = QPen{Qt::black, 2, Qt::DashLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::DashLine};
    editNameAllowed = false;
}

/**
 * Initializes itself - store from and to object + store self in those objects.
 */
void ReplyMessageLine::initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                                  Message *msg, ClassReference classRef)
{
    (void)classRef;
    fromObject = from;
    toObject = to;
    fromObject->addMessage(this);
    toObject->addMessage(this);
    toObject->setDestroyed(true);
    leftToRight = from->x() < to->x();
    message = msg;
    message->setName(MethodReference{""});
    this->classRef = ClassReference{""};
}
