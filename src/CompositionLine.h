/**
 * @class CompositionLine
 * Composition line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef COMPOSITIONLINE_H
#define COMPOSITIONLINE_H

#include "Line.h"

class CompositionLine: public Line
{
public:
    using Line::Line;
private:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};


#endif // COMPOSITIONLINE_H
