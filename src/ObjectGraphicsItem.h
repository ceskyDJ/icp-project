/**
 * @class ObjectGraphicsItem
 * Representation of object in sequence diagram as graphics item.
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

class ObjectGraphicsItem : public ActivationGraphicsObjectBase
{
public:
    Object *object;

    ObjectGraphicsItem(Object *newObject);
    qreal width() const;
protected:
    /**
     * Padding int object header |[padding]<NAME>[Padding]|
     */
    qreal textPadding = 10.0;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QRectF lifeBoxRect();
    QRectF resizeArea();
};

#endif // OBJECTGRAPHICSITEM_H
