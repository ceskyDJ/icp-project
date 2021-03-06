/**
 * @file ReplyMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ReplyMessageLine.h"

/**
 * Class constructor
 *
 * @par Set pens for line drawing
 *
 * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
 * @param sequenceDiagram Pointer to edited sequence diagram
 */
ReplyMessageLine::ReplyMessageLine(
    SceneUpdateObservable *sceneUpdateObservable,
    SequenceDiagram *sequenceDiagram
): MessageLine{sceneUpdateObservable, sequenceDiagram}
{
    linePenOk = QPen{Qt::black, 2, Qt::DashLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::DashLine};
    editNameAllowed = false;
}

/**
     * @brief Initializes itself - store from and to object + store self in those objects.
     * 
     * @param from sender
     * @param to reciever
     * @param msg new message
     * @param classRef reference to class
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
    message = msg;
    message->setName(MethodReference{""});
    this->classRef = ClassReference{""};
    moveLine(0, true);
}
