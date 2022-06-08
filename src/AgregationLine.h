/**
 * @file AgregationLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef AGREGATIONLINE_H
#define AGREGATIONLINE_H

#include "LineWithArrow.h"
#include "Line.h"

/**
 * Represents agregation line in class diagram.
 */
class AgregationLine : public LineWithArrow
{
public:
    AgregationLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );
protected:
    /**
     * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
     * Painter has to be corectly placed and rotated.
     *
     * @param painter to paint arrow
     */
    void drawArrow(QPainter *painter) const;
};

#endif // AGREGATIONLINE_H
