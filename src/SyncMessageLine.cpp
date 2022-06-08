/**
 * @file SyncMessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "SyncMessageLine.h"
#include <QPainterPath>

/**
 * Class constructor
 *
 * @par Sets arrow height and width.
 *
 * @param sequenceDiagram Pointer to edited sequence diagram
 */
SyncMessageLine::SyncMessageLine(SequenceDiagram *sequenceDiagram): MessageLine{sequenceDiagram}
{
    arrowHeight = 10;
    arrowWidth = 20;
}

/**
 * Overrided method to draw an arrow at the end of the line.
 *
 * @param painter Recieved painter. Painter has to be rotated and translated to end of the line.
 */
void SyncMessageLine::drawArrow(QPainter *painter) const
{
    QVector<QPointF> arrowPoints = {
        QPointF{0, arrowHeight * 0.5},
        QPointF{arrowWidth, 0},
        QPointF{0, -arrowHeight * 0.5},
        QPointF{0, arrowHeight * 0.5}
    };
    QPolygonF arrowPolygon{arrowPoints};
    QPainterPath arrowPath;
    arrowPath.addPolygon(arrowPolygon);
    painter->fillPath(arrowPath, painter->pen().brush());
}


