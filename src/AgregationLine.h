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
    /**
     * Sets arrow height and width.
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
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
