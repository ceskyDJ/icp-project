/**
 * @class Realization
 * Allows to draw realization line in UML class diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef REALIZATIONLINE_H
#define REALIZATIONLINE_H

#include "LineWithArrow.h"

class RealizationLine : public LineWithArrow
{
public:
    RealizationLine(std::unordered_map<Line *, Relationship *> *existingRelationships, ClassDiagram *classDiagram);
protected:
    void drawArrow(QPainter *painter) const;

};

#endif // REALIZATIONLINE_H
