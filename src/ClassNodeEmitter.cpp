/**
 * @file ClassNodeEmitter.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ClassNodeEmitter.h"

ClassNodeEmitter::ClassNodeEmitter(QObject *parent, ClassNode *node): QObject{parent}
{
    this->node = node;
}

void ClassNodeEmitter::emitNodePresed()
{
    emit nodePressed(node);
}
