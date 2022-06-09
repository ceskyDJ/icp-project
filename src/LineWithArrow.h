/**
 * @file LineWithArrow.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef LINEWITHARROW_H
#define LINEWITHARROW_H

#include "Line.h"

/**
 * Represents line with arrow in class diagram. Allows to draw a line with arrow.
 */
class LineWithArrow: public Line
{
public:
    using Line::Line;
protected:
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
     * Override Adjusts bounding rectangle
     *
     * @return QRectF A rectnagle around classNode.
     */
    void adjustBounding(QRectF *rect) const;

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
    QRectF adjustSelfRect(QRectF rect, int multiply) const;
    virtual void drawTexts(QPainter *painter, QLineF line) const;
};

#endif // LINEWITHARROW_H
