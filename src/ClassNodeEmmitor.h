/**
 * @class classNodeEmmitor
 * Provides slots and singnals object for QGraphicsItem (ClassNode)
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CLASSNODEEMMITOR_H
#define CLASSNODEEMMITOR_H

#include <QObject>
#include "classNode.h"

class ClassNode;

class ClassNodeEmmitor : public QObject
{
    Q_OBJECT
public:
    explicit ClassNodeEmmitor(QObject *parent = nullptr, ClassNode *node = nullptr);

    /**
     * Emits signal nodePressed
     */
    void emitNodePresed();
signals:
    /**
     * Emits when class node is pressed.
     *
     * @param node - this
     */
    void nodePressed(ClassNode *node);
private:
    ClassNode *node;
};

#endif // CLASSNODEEMMITOR_H
