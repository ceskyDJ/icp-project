/**
 * @file ActivationGraphicsObjectBase.h
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
#include "MessageLine.h"
#include "ActivationObjectEmitter.h"

class MessageLine;

/**
 * Base functionality, variables and func declarations that are necessary for object in sequence diagram
 * which has life box.
*/
class ActivationGraphicsObjectBase : public QGraphicsItem
{
public:
    /**
     * Set Class refernce - if not redefined, does nothing.
     */
    virtual void setClassReference(ClassReference){}
    /**
     * Return message node. If not overriden, return new actor.
     *
     * @return new actor
     */
    virtual MessageNode* getMessageNode();
    /**
     * Emitter for signal emitting.
     */
    ActivationObjectEmitter emitter{nullptr, this};
    /**
     * Width of lifebox
     */
    static qreal lifeboxWidth;

    /**
     * Color to draw objects - it changes according to user events.
     */
    static QColor drawColor;

    static qreal objectPadding;
    /**
     * Size of destroy cross
     */
    static qreal destroyCrossSize;

    /**
     * Returns width of object with activation/life box
     */
    virtual qreal width() const;

    /**
     * Max height of object.
     */
    static qreal height;

    /**
     * Height of header (actor picture / box size)
     */
    static qreal headerHeight;

    /**
     * Space between header and life box.
     */
    static qreal lifeSpaceStart;

    /**
     * Add message into object messages
     *
     * @param message message to add
     */
    virtual void addMessage(MessageLine *message);

    /**
     * Remove message from messages
     *
     * @param message message to remove
     */
    void removeMesage(MessageLine *message);

    /**
     * Destructor - deletes all messages from self.
     */
    ~ActivationGraphicsObjectBase();

    /**
     * @brief lifeBoxRect Count and return area where lifebox is located.
     * @return area where lifebox is located
     */
    virtual QRectF lifeBoxRect();

    /**
     * Returns start of life box in interval <0,1>. If not overriden, return 0.
     *
     * @return start of life box in interval <0,1>, if not overriden return 0
     */
    virtual qreal getStartOfLifeBox();

    /**
     * Returns life length of object in interval <0,1>. If not overriden, return 1.
     *
     * @return life length of object in interval <0,1>, if not overriden, return 1 1.
     */
    virtual qreal getLifeLength();

    /**
     * Set life start to position of lifeStart argument. If not overriden, does nothign.
     *
     * @param lifeStart new start of life - it has to be in interval <0,1>.
     */
    virtual void setLifeStart(qreal lifeStart);

    /**
     * Set lifelength so it ends in moment of lifeEnd argument. If not overriden, does nothign.
     *
     * @param lifeEnd time when life should end - it has to be in interval <0,1>.
     */
    virtual void setLifeEndDestroy(qreal lifeEnd);

    /**
     * Getter for class referrence object.
     *
     * @return Unknown reference object.
     */
    virtual ClassReference getClassReference()
    {
        return ClassReference{"UNKNOWN"};
    }
    /**
     * Indicates if cross should be written after lifebox.
     */
    bool destroyed;

    /**
     * Set destroyed flag.
     *
     * @param destroyed true/false to set destroyed flag
     */
    void setDestroyed(bool destroyed);

    /**
     * Getter for object counter.
     *
     * @return object counter
     */
    int getObjectCounter()
    {
        return objectCounter;
    }

    /**
     * Increases object counter
     */
    void incObjectCounter()
    {
        ++objectCounter;
    }
    /**
     * Sets object and actor color to color argument.
     *
     * @param color new color
     */
    static void setColor(QColor color)
    {
        drawColor = color;
    }

    /**
     * Getter for draw color
     *
     * @return drawing color
     */
    static QColor getColor()
    {
        return drawColor;
    }
  protected:
    /**
     * Counts created objects.
     */
    static int objectCounter;

    /**
     * All messages that goes into and from this object.
     */
    QList<MessageLine *> messages;

    static const int minHeight = 100;

    /**
     * Position of cursor when pressed to an object.
     */
    QPointF pressedPos;

    /**
     * Pen used in regular drawing
     */
    QPen regularPen{Qt::black, 2, Qt::SolidLine};

    /**
     * Pen used when object is unknown.
     */
    QPen unknownObject{Qt::blue, 2, Qt::SolidLine};
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
