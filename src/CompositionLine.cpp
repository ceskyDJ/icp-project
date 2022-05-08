/**
 * @class CompositionLine
 * Composition line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "CompositionLine.h"

#include <QPainter>

/**
 * @brief CompositionLine::paint paints a composition line with right arrow
 * @param painter painter that allows to paint
 */
void CompositionLine::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    int size = 20;
    painter->setPen(QPen{Qt::black, 2, Qt::SolidLine});

    QLineF line = getShortestLine(fromClassNode, toClassNode);
    line.setLength(line.length() - size);
    QPointF arrow = line.p2();

    for(int i = 0; i < size/2; ++i)
    {
        QPoint one = QPoint(arrow.x() + i, arrow.y() - i);
        QPoint two = QPoint(arrow.x() + size/2 + i, arrow.y() + size/2 - i);
        painter->drawLine(one, two);
    }

    painter->drawLine(line);
}
