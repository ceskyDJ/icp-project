/**
 * @file classNodeEmitter.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CLASSNODEEMITTER_H
#define CLASSNODEEMITTER_H

#include <QObject>

// There is a circular dependency between ClassNodeEmmitor and ClassNode
// Warning: #include can't be used for ClassNode's header!
class ClassNode;

/**
 * Provides slots and signals object for QGraphicsItem (ClassNode)
 */
class ClassNodeEmitter : public QObject
{
    Q_OBJECT
public:
    explicit ClassNodeEmitter(QObject *parent = nullptr, ClassNode *node = nullptr);

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

#endif // CLASSNODEEMITTER_H
