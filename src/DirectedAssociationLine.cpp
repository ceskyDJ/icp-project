/**
 * @file DirectedAssociationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "DirectedAssociationLine.h"
#include <QPolygonF>
#include <QLinearGradient>
#include <QPainterPath>

/**
 * Set arrow height and width.
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 */
DirectedAssociationLine::DirectedAssociationLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram
): LineWithArrow{existingRelationships, classDiagram}
{
    arrowHeight = 20;
    arrowWidth = 20;
}

/**
 * Draws an arrow adequate to the directed association line.
 *
 * @param painter to draw line
 */
void DirectedAssociationLine::drawArrow(QPainter *painter) const
{
    QVector<QPointF> points = {
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2},
        QPointF{arrowWidth / 2, 0},
        QPointF{-arrowWidth / 2 + 1, -arrowHeight / 2},
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2}
    };

    QPolygonF arrowPolygon{points};
    QPainterPath arrowPath;
    QLinearGradient arrowGradient{};
    arrowGradient.setColorAt(0,Qt::black);
    arrowGradient.setColorAt(1,Qt::black);
    arrowPath.addPolygon(arrowPolygon);
    painter->setBrush(arrowGradient);
    painter->drawPath(arrowPath);
}
