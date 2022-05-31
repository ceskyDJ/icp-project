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
    prepareGeometryChange();
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    if(selfRealtionshipFlag)
    {
        paintSelfRelationship(painter);
        return;
    }
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
 * Paints self realtionship.
 *
 * @param painter Painter to paint relationship
 */
void LineWithArrow::paintSelfRelationship(QPainter *painter)
{
    QRectF bounding = boundingRect();
    bounding = adjustSelfRect(bounding, -1);
    qreal leftPadding = bounding.x() + bounding.width() - selfPadding;
    qreal botPadding = bounding.y() + bounding.height() - selfPadding;

    QVector<QPointF> linePoints = {
        QPointF{leftPadding, bounding.y()},
        QPointF{bounding.x() + bounding.width(), bounding.y()},
        QPointF{bounding.x() + bounding.width(), bounding.y() + bounding.height()},
        QPointF{bounding.x(), bounding.y() + bounding.height()},
        QPointF{bounding.x(), botPadding + arrowHeight / 2}
    };
    for (int i = 0; i < linePoints.size() - 1; i++)
        painter->drawLine(linePoints[i], linePoints[i + 1]);

    painter->translate(QPointF{bounding.x(), botPadding + arrowWidth / 2});
    painter->rotate(270);
    QRect arrow = QRect(-arrowWidth / 2, -arrowHeight / 2, arrowWidth, arrowHeight);
    painter->fillRect(arrow,QBrush(Qt::white));
    drawArrow(painter);
}

/**
 * Adjusts regular boundingbox
 *
 * @param rect that should be adjusted
 */
void LineWithArrow::adjustBounding(QRectF *rect) const
{
    rect->adjust(-arrowWidth, -arrowHeight, arrowWidth, arrowHeight);
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
    update();
}

/**
 * Adjusts bounding rect for self relationship
 *
 * @param rect rect to adjust
 * @param multyply 1 for bounding rect, -1 for drawing
 */
QRectF LineWithArrow::adjustSelfRect(QRectF rect, int multyply) const
{
    rect.adjust((arrowWidth + lineBoundingWidth * 2) * -multyply, lineBoundingWidth * 2 * -multyply,
                (arrowWidth + lineBoundingWidth * 2) * multyply, lineBoundingWidth * 2 * multyply);
    return rect;
}
