#ifndef ACTIVATIONGRAPHICSOBJECTBASE_H
#define ACTIVATIONGRAPHICSOBJECTBASE_H

#include <QRectF>

class ActivationGraphicsObjectBase
{
  public:

    /**
     * Height of header (actor picture / box size)
     */
    qreal headerHeight = 50;

    /**
     * Space between header and life box.
     */
    qreal lifeSpaceStart = 10;

    /**
     * Max height of object.
     */
    qreal height;

    /**
     * Width of lifebox
     */
    qreal lifeboxWidth = 20;


    /**
     * Returns width of object with activation/life box
     */
    virtual qreal width() const = 0;


    /**
     * Informs object that height was updated and object has to be redrawe
     *
     * @param newHeight new height of object
     */
    virtual void heightUpdated(qreal newHeight) = 0;
};

#endif // ACTIVATIONGRAPHICSOBJECTBASE_H
