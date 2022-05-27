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
#include "LineWithArrow.h"
#include <QPainter>
class GeneralizationLine : public LineWithArrow
{
public:
    /**
     * Sets arrow width and height
     */
    GeneralizationLine();
protected:
    /**
     * Draws and arrow - rectangle
     *
     * @param painter to draw
     */
    void drawArrow(QPainter *painter) const;
};

#endif // GENERALIZATIONLINE_H
