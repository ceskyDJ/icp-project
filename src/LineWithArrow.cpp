/**
 * @file LineWithArrow.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "LineWithArrow.h"
#include <cmath>
#include <QPainter>
#include "LineWithArrowEditDialog.h"

/**
     * Paints line and arrow. Inherited from QGraphicsItem
     *
     * @param painter object that allowes to paint
     * @param option options of graphics item
     * @param widget pointer to widget
     */
void LineWithArrow::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QLineF line = getShortestLine(fromClassNode, toClassNode);
    line.setLength(line.length() - arrowWidth / 2);
    qreal centerX = line.p2().x();
    qreal centerY = line.p2().y();
    painter->drawLine(line);

    painter->translate(centerX, centerY);
    painter->rotate(-line.angle());
    double side = sqrt((arrowWidth * arrowWidth)/2);
    QRect arrow = QRect(-side/2, -side/2, side, side);
    painter->fillRect(arrow,QBrush(Qt::white));

    drawArrow(painter);
}

/**
 * Override method which returns bounding rect of line.
 *
 * @return QRectF A rectnagle around classNode.
 */
QRectF LineWithArrow::boundingRect() const
{
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    QPointF leftTop = QPointF{ fmin(line.p1().x(), line.p2().x()), fmin(line.p1().y(), line.p2().y())};
    QPointF rightBot = QPointF{ fmax(line.p1().x(), line.p2().x()), fmax(line.p1().y(), line.p2().y())};
    QRectF bounding = QRectF{leftTop,rightBot};
    bounding.adjust(-arrowWidth, -arrowHeight, arrowWidth, arrowHeight);
    return bounding;
}

/**
 * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
 * Painter has to be corectly placed and rotated.
 *
 * @param painter to paint arrow
 */
void LineWithArrow::drawArrow(QPainter */*painter*/) const
{
}


/**
 * Shows dialog to edit relationship.
 */
void LineWithArrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    LineWithArrowEditDialog *edit = new LineWithArrowEditDialog(this);
    edit->exec();
}
