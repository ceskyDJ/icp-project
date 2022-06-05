/**
 * @class ActorGraphicsItem
 * Representation of actor in sequence diagram as graphics item.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTORGRAPHICSITEM_H
#define ACTORGRAPHICSITEM_H

#include <QGraphicsItem>
#include "ActivationGraphicsObjectBase.h"
#include "Actor.h"
#include <QGraphicsSceneMouseEvent>

class ActorGraphicsItem : public ActivationGraphicsObjectBase
{
public:
    ActorGraphicsItem(Actor *actor);
private:
    qreal personWidth = 50;
    Actor *actor;


    qreal width() const;
    void heightUpdated(qreal newHeight);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QRectF lifeBoxRect();
    QRectF resizeArea();
};

#endif // ACTORGRAPHICSITEM_H
