/**
 * @file CompositionLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "CompositionLine.h"
#include <QVector>
#include <QPolygonF>
#include <QPainterPath>
#include <QLinearGradient>

/**
 * Sets arrow width and height.
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 * @param sceneUpdateObservable Observable for distributing information about scene changes
 */
CompositionLine::CompositionLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram,
    SceneUpdateObservable *sceneUpdateObservable
): LineWithArrow{existingRelationships, classDiagram, sceneUpdateObservable}
{
    arrowWidth = 20;
    arrowHeight = 5;
}

/**
 * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
 * Painter has to be corectly placed and rotated.
 *
 * @param painter to paint arrow
 */
void CompositionLine::drawArrow(QPainter *painter) const
{
    QVector<QPointF> arrowPoints = {
        QPointF{- arrowWidth / 2,0},
        QPointF{0, arrowHeight},
        QPointF{arrowWidth / 2, 0},
        QPointF{0, -arrowHeight},
        QPointF{- arrowWidth / 2,0}
    };
    QPolygonF arrowPolygon{arrowPoints};
    QPainterPath arrowPath{};
    QLinearGradient arrowGradient{};
    arrowGradient.setColorAt(0,Qt::black);
    arrowGradient.setColorAt(1,Qt::black);
    arrowPath.addPolygon(arrowPolygon);
    painter->setBrush(arrowGradient);
    painter->drawPath(arrowPath);
}
