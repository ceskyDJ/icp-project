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
 * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
 * @param sequenceDiagram Pointer to edited sequence diagram
 */
CreateMessageLine::CreateMessageLine(
    SceneUpdateObservable *sceneUpdateObservable,
    SequenceDiagram *sequenceDiagram
): MessageLine{sceneUpdateObservable, sequenceDiagram}
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
