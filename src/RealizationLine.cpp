/**
 * @file RealizationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "RealizationLine.h"

/**
 * Sets arrow width, height and line style to dash line
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 */
RealizationLine::RealizationLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram
): LineWithArrow{existingRelationships, classDiagram}
{
    arrowHeight = 20;
    arrowWidth = 20;
    pen.setStyle(Qt::DashLine);
}

/**
 * Draws an arrow adequate to the realization line.
 *
 * @param painter to draw line
 */
void RealizationLine::drawArrow(QPainter *painter) const
{
    QPen newPen = pen;
    newPen.setStyle(Qt::SolidLine);
    painter->setPen(newPen);
    QVector<QPointF> points = {
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2},
        QPointF{arrowWidth / 2, 0},
        QPointF{-arrowWidth / 2 + 1, -arrowHeight / 2},
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2}
    };

    for(int i = 0; i < points.size() - 1; i++)
        painter->drawLine(points[i], points[i + 1]);
}
