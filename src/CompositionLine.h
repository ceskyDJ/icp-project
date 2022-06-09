/**
 * @file CompositionLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef COMPOSITIONLINE_H
#define COMPOSITIONLINE_H

#include "Line.h"
#include "LineWithArrow.h"

/**
 * Represenatation of composition relationship in class diagram.
 */
class CompositionLine: public LineWithArrow
{
public:
    /**
     * Sets arrow width and height.
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
    CompositionLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );
private:
    /**
     * Draws an arrow to position (0,0) in the end of the line in the middle of boundingbox.
     * Painter has to be corectly placed and rotated.
     *
     * @param painter to paint arrow
     */
    void drawArrow(QPainter *painter) const;
};


#endif // COMPOSITIONLINE_H
