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

// There is a circular dependency between ClassNodeEmitter and ClassNode
// Warning: #include can't be used for ClassNode's header!
class ClassNode;

/**
 * Provides slots and signals object for QGraphicsItem (ClassNode)
 */
class ClassNodeEmitter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Class Node Emitter:: Class Node Emitter object
     * 
     * @param parent parent object
     * @param node classnode which will be sent in singlas
     */
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
    /**
     * Node that will be sent in signals
     */
    ClassNode *node;
};

#endif // CLASSNODEEMITTER_H
