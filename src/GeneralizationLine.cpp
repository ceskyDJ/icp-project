/**
 * @file GeneralizationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "GeneralizationLine.h"

/**
 * Sets arrow height and Width
 */
GeneralizationLine::GeneralizationLine()
{
    arrowHeight = 20;
    arrowWidth = 20;
}

void GeneralizationLine::drawArrow(QPainter *painter) const
{
    QVector<QPointF> points = {
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2},
        QPointF{arrowWidth / 2, 0},
        QPointF{-arrowWidth / 2 + 1, -arrowHeight / 2},
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2}
    };
    for(int i = 0; i < points.size() - 1; i++)
        painter->drawLine(points[i], points[i + 1]);
}
