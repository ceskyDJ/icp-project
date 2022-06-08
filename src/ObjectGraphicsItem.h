/**
 * @file ObjectGraphicsItem.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef OBJECTGRAPHICSITEM_H
#define OBJECTGRAPHICSITEM_H

#include <QGraphicsItem>
#include "Object.h"
#include <QPen>
#include "ActivationGraphicsObjectBase.h"
#include <QPainterPath>
#include "ClassDiagram.h"

/**
 * Representation of object in sequence diagram as graphics item.
 */
class ObjectGraphicsItem : public ActivationGraphicsObjectBase
{
public:
    ObjectGraphicsItem(Object *newObject, ClassDiagram *classDiagram);
    qreal width() const;
    QRectF lifeBoxRect();
    qreal getStartOfLifeBox();
    qreal getLifeLength();
    void showEditDialog(bool logChange);

    /**
     * Getter for object property
     *
     * @return object in this
     */
    Object *getObject()
    {
        return object;
    }

    /**
     * Getter for object.
     *
     * @return new object
     */
    MessageNode* getMessageNode()
    {
        return object;
    }

    /**
     * Getter for class referrence object.
     *
     * @return object class reference.
     */
    virtual ClassReference getClassReference()
    {
        return object->getInstanceClass();
    }
    MessageLine *getDestroyMessage();
    MessageLine *getCreateMessage();

    /**
     * Setter fo class reference.
     *
     * @param newClassRef new class reference to be set.
     */
    void setClassReference(ClassReference newClassRef)
    {
        object->setInstanceClass(newClassRef);
    }
protected:
    /**
     * Data source for combobox item.
     */
    ClassDiagram *classDiagram;
    /**
     * Padding int object header |[padding]<NAME>[Padding]|
     */
    qreal textPadding = 10.0;
    Object *object;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QRectF resizeArea();
    void moveAllMessages(qreal dy);
    void setLifeStart(qreal lifeStart);
    void setLifeEndDestroy(qreal lifeEnd);
    void setDestroyed(bool destroyed);
    void updateMessagesClassReference(ClassReference newClassRef);
};

#endif // OBJECTGRAPHICSITEM_H
