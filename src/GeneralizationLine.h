/**
 * @class GeneralizationLine
 * Generalization line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef GENERALIZATIONLINE_H
#define GENERALIZATIONLINE_H

#include "Line.h"

class GeneralizationLine : public Line
{
public:
    using Line::Line;
private:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // GENERALIZATIONLINE_H
