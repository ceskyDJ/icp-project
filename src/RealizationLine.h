/**
 * @file RealizationLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef REALIZATIONLINE_H
#define REALIZATIONLINE_H

#include "LineWithArrow.h"

/**
 * Allows to draw realization line in UML class diagram.
 */
class RealizationLine : public LineWithArrow
{
public:
    /**
     * Sets arrow width, height and line style to dash line
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
    RealizationLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );
protected:
    /**
     * Draws an arrow adequate to the realization line.
     *
     * @param painter to draw line
     */
    void drawArrow(QPainter *painter) const;

};

#endif // REALIZATIONLINE_H
