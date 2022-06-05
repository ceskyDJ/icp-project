/**
 * @class ActivationGraphicsObjectBase
 * Base functionality, variables and func declarations that are necessary for object in sequence diagram
 * which has life box.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTIVATIONGRAPHICSOBJECTBASE_H
#define ACTIVATIONGRAPHICSOBJECTBASE_H

#include <QRectF>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class ActivationGraphicsObjectBase : public QGraphicsItem
{
public:

  protected:
    /**
     * Max height of object.
     */
    static qreal height;

    static const int minHeight = 100;
    /**
     * Height of header (actor picture / box size)
     */
    static qreal headerHeight;

    /**
     * Space between header and life box.
     */
    qreal lifeSpaceStart = 10;

    /**
     * Width of lifebox
     */
    qreal lifeboxWidth = 20;

    /**
     * Position of cursor when pressed to an object.
     */
    QPointF pressedPos;

    /**
     * Pen used in regular drawing
     */
    QPen regularPen{Qt::black, 2, Qt::SolidLine};

    /**
     * Pen used in drawing object when object is selected
     */
    QPen selectedPen{Qt::red, 3, Qt::DashLine};

    /**
     * Pen used to draw life line.
     */
    QPen lifeLinePen{Qt::black, 2, Qt::DashLine};

    /**
     * Pen used for drawing lifeline border
     */
    QPen lifeLineBorderPen{Qt::darkGreen, 1, Qt::DashLine};

    /**
     * Returns width of object with activation/life box
     */
    virtual qreal width() const = 0;

    /**
     * Returns bounding rect of actor.
     *
     * @return bounding rect of actor
     */
    QRectF boundingRect() const override;

    /**
     * Return bounding box that is as big as is indeed for given text
     *
     * @param text text around which is rectangle counted for.
     * @return bounding rect around text
     */
    QRectF getTextBoundingBox(QString text) const;
};
#endif // ACTIVATIONGRAPHICSOBJECTBASE_H
