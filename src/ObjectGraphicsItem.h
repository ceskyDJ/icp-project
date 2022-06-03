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

class ObjectGraphicsItem : public QGraphicsItem, public ActivationGraphicsObjectBase
{
public:
    Object *object;

    ObjectGraphicsItem(Object *newObject, qreal height);
    qreal width() const;
protected:
    /**
     * Padding int object header |[padding]><NAME>[Padding]|
     */
    qreal textPadding = 10.0;
    QPen regularPen{Qt::black, 2, Qt::SolidLine};
    QPen selectedPen{Qt::red, 3, Qt::DashLine};
    QPointF pressedPos;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QRectF getTextBoundingBox(QString text) const;
    void heightUpdated(qreal newHeight);
    int getSceneHeight();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QRectF lifeBoxRect();
    QRectF resizeArea();
};

#endif // OBJECTGRAPHICSITEM_H
