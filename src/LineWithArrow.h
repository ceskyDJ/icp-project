/**
 * @class LineWithArrow
 * Represents line with arrow in class diagram. Allows to draw a line with arrow.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef LINEWITHARROW_H
#define LINEWITHARROW_H

#include "Line.h"

class LineWithArrow: public Line
{
public:
    using Line::Line;
protected:
    qreal selfPadding = 50;
    double arrowHeight = 5;
    double arrowWidth = 20;
    /**
     * Paints line and arrow. Inherited from QGraphicsItem
     *
     * @param painter object that allowes to paint
     * @param option options of graphics item
     * @param widget pointer to widget
     */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    /**
     * Paints self realtionship.
     *
     * @param painter Painter to paint relationship
     */
    void paintSelfRelationship(QPainter *painter);

    /**
     * Override method which returns bounding rect of line.
     *
     * @return QRectF A rectnagle around classNode.
     */
    QRectF boundingRect() const;

    /**
     * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
     * Painter has to be corectly placed and rotated.
     *
     * @param painter to paint arrow
     */
    virtual void drawArrow(QPainter *painter) const;

    /**
     * Shows dialog to edit relationship.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/);
    QRectF adjustSelfRect(QRectF rect, int multyply) const;
    QPainterPath shape() const;
};

#endif // LINEWITHARROW_H
