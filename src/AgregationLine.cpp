/**
 * @class AgregationLine
 * Represents agregation line in class diagram. Allows to paint a line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "AgregationLine.h"

#include <QPainter>

/**
     * Paints line and arrow. Inherited from QGraphicsItem
     *
     * @param painter object that allowes to paint
     * @param option options of graphics item
     * @param widget pointer to widget
     */
void AgregationLine::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    int size = 20;
    painter->setPen(QPen{Qt::black, 2, Qt::SolidLine});

    QLineF line = getShortestLine(fromClassNode, toClassNode);
    line.setLength(line.length() - size);
    QPointF arrow = line.p2();

    QList<QPoint> rectangle;
    rectangle.append(QPoint(arrow.x(), arrow.y()));
    rectangle.append(QPoint(arrow.x() + size/2, arrow.y() + size/2));

    rectangle.append(QPoint(arrow.x() + size/2, arrow.y() + size/2));
    rectangle.append(QPoint(arrow.x() + size, arrow.y()));

    rectangle.append(QPoint(arrow.x() + size, arrow.y()));
    rectangle.append(QPoint(arrow.x() + size/2, arrow.y() - size/2));

    rectangle.append(QPoint(arrow.x() + size/2, arrow.y() - size/2));
    rectangle.append(QPoint(arrow.x(), arrow.y()));

    for (int i = 0; i < rectangle.count(); i+=2)
        painter->drawLine(rectangle[i], rectangle[i+1]);
    painter->drawLine(line);
}
