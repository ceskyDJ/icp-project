/**
 * @class GeneralizationLine
 * Generalization line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "GeneralizationLine.h"
#include <QPainter>

/**
 * @brief GeneralizationLine::paint paints line with right arrow
 * @param painter painter allowing to paint line and arrow
 */
void GeneralizationLine::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    int size = 20;
    painter->setPen(QPen{Qt::black, 2, Qt::SolidLine});

    QLineF line = getShortestLine(fromClassNode, toClassNode);
    line.setLength(line.length() - size);
    QPointF arrow = line.p2();

    QList<QPoint> rectangle;
    rectangle.append(QPoint(arrow.x(), arrow.y() - size/2));
    rectangle.append(QPoint(arrow.x(), arrow.y() + size/2));
    rectangle.append(QPoint(arrow.x(), arrow.y() + size/2));
    rectangle.append(QPoint(arrow.x() + size, arrow.y()));
    rectangle.append(QPoint(arrow.x() + size, arrow.y()));
    rectangle.append(QPoint(arrow.x(), arrow.y() - size/2));


    painter->drawLines(rectangle);

    painter->drawLine(line);
}
