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
    qreal width() const override;
    QRectF lifeBoxRect() override;
    qreal getStartOfLifeBox() override;
    qreal getLifeLength() override;
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
    MessageNode* getMessageNode() override
    {
        return object;
    }

    /**
     * Getter for class referrence object.
     *
     * @return object class reference.
     */
    virtual ClassReference getClassReference() override
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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    QRectF resizeArea();
    void moveAllMessages(qreal dy);
    void setLifeStart(qreal lifeStart) override;
    void setLifeEndDestroy(qreal lifeEnd) override;
    void setDestroyed(bool destroyed);
    void updateMessagesClassReference(ClassReference newClassRef);
};

#endif // OBJECTGRAPHICSITEM_H
