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
    RealizationLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );
protected:
    void drawArrow(QPainter *painter) const;

};

#endif // REALIZATIONLINE_H
