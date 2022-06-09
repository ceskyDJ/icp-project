/**
 * @file ClassNodeEmitter.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ClassNodeEmitter.h"

/**
 * @brief Construct a new Class Node Emitter:: Class Node Emitter object
 * 
 * @param parent parent object
 * @param node classnode which will be sent in singlas
 */
ClassNodeEmitter::ClassNodeEmitter(QObject *parent, ClassNode *node): QObject{parent}
{
    this->node = node;
}

/**
 * Emits signal nodePressed
 */
void ClassNodeEmitter::emitNodePresed()
{
    emit nodePressed(node);
}
