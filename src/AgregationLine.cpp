/**
 * @file AgregationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */

#include "AgregationLine.h"

/**
 * Sets arrow height and width.
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 */
AgregationLine::AgregationLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram
): LineWithArrow{existingRelationships, classDiagram}
{
    arrowHeight = 5;
    arrowWidth = 20;
}

/**
 * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
 * Painter has to be corectly placed and rotated.
 *
 * @param painter to paint arrow
 */
void AgregationLine::drawArrow(QPainter *painter) const
{
    std::vector<QPointF> arrowPoints = {
        QPointF{- arrowWidth / 2,0},
        QPointF{0, arrowHeight},
        QPointF{arrowWidth / 2, 0},
        QPointF{0, -arrowHeight},
        QPointF{- arrowWidth / 2,0}
    };
    for(int i = 0; (size_t)i < arrowPoints.size() - 1; i++)
        painter->drawLine(arrowPoints[i], arrowPoints[i+1]);
}
