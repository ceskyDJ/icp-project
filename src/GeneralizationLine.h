/**
 * @file GeneralizationLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef GENERALIZATIONLINE_H
#define GENERALIZATIONLINE_H

#include "Line.h"
#include "LineWithArrow.h"
#include <QPainter>

/**
 * Representation of generalisation line in class diagram.
 */
class GeneralizationLine : public LineWithArrow
{
public:
    /**
     * Sets arrow width and height
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
    GeneralizationLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );
protected:
    /**
     * Draws and arrow - rectangle
     *
     * @param painter to draw
     */
    void drawArrow(QPainter *painter) const;
};

#endif // GENERALIZATIONLINE_H
