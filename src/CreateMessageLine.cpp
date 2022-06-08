/**
 * @file CreateMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "CreateMessageLine.h"

/**
 * Class constructor
 *
 * @param sequenceDiagram Pointer to edited sequence diagram
 */
CreateMessageLine::CreateMessageLine(SequenceDiagram *sequenceDiagram): MessageLine{sequenceDiagram}
{
    linePenOk = QPen{Qt::black, 2, Qt::DashLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::DashLine};
    editNameAllowed = false;
    createFlag = true;
}

/**
 * Initializes itself - store from and to object + store self in those objects.
 */
void CreateMessageLine::initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
                                   Message *msg, ClassReference classRef)
{
    fromObject = from;
    toObject = to;
    fromObject->addMessage(this);
    toObject->addMessage(this);
    message = msg;
    message->setName(MethodReference{"<<create>>"});
    this->classRef = classRef;
    moveLine(0,true);
}
