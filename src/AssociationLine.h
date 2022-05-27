/**
 * @class AssociationLine.h
 * Represents association line in class diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ASSOCIATIONLINE_H
#define ASSOCIATIONLINE_H

#include "Line.h"

class AssociationLine : public Line
{
public:
    using Line::Line;

protected:
    QString associationName = "association name";
    QString firstCardinality = "*f";
    QString secondCardinality = "*s";
    qreal padding = 20;


    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    QRectF getTextBoundingBox(QString text) const;
    QRectF boundingRect() const;
    QRectF prepareBoundingBox(QRectF rect);
    QRectF locateCardinality(QRectF rect, int modifier, QLineF line);
};

#endif // ASSOCIATIONLINE_H
