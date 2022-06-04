/**
 * @file ClassDiagramWindow.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ClassNodeEmmitor.h"

ClassNodeEmmitor::ClassNodeEmmitor(QObject *parent, ClassNode *node)
    : QObject{parent}
{
    this->node = node;
}

void ClassNodeEmmitor::emitNodePresed()
{
    emit nodePressed(node);
}
