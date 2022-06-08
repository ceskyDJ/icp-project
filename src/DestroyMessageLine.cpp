/**
 * @file DestroyMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "DestroyMessageLine.h"

DestroyMessageLine::DestroyMessageLine()
{
    linePenOk = QPen{Qt::black, 2, Qt::DashLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::DashLine};
    editNameAllowed = false;
    destroyFlag = true;
}

/**
 * Initializes itself - store from and to object + store self in those objects.
 */
void DestroyMessageLine::initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                                    Message *msg, ClassReference classRef)
{
    (void)classRef;
    fromObject = from;
    toObject = to;
    fromObject->addMessage(this);
    toObject->addMessage(this);
    toObject->setDestroyed(true);
    message = msg;
    message->setName(MethodReference{"<<destroy>>"});
    this->classRef = ClassReference{""};
}
