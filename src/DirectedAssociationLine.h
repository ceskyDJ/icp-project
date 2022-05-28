/**
 * @class DirectedAssociationLine
 * Allows to draw a directed association line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef DIRECTEDASSOCIATIONLINE_H
#define DIRECTEDASSOCIATIONLINE_H
#include "LineWithArrow.h"

class DirectedAssociationLine : public LineWithArrow
{
public:
    DirectedAssociationLine();
protected:
    void drawArrow(QPainter *painter) const;
};

#endif // DIRECTEDASSOCIATIONLINE_H
