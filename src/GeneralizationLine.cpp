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
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 * @param sceneUpdateObservable Observable for distributing information about scene changes
 */
GeneralizationLine::GeneralizationLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram,
    SceneUpdateObservable *sceneUpdateObservable
): LineWithArrow{existingRelationships, classDiagram, sceneUpdateObservable}
{
    arrowHeight = 20;
    arrowWidth = 20;
}

/**
     * Draws and arrow - rectangle
     *
     * @param painter to draw
     */
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
