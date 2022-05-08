/**
 * @class AgregationLine
 * Represents agregation line in class diagram. Allows to paint a line.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef AGREGATIONLINE_H
#define AGREGATIONLINE_H

#include "Line.h"

class AgregationLine: public Line
{
public:
    using Line::Line;
private:
    /**
     * Paints line and arrow. Inherited from QGraphicsItem
     *
     * @param painter object that allowes to paint
     * @param option options of graphics item
     * @param widget pointer to widget
     */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // AGREGATIONLINE_H
