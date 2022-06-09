/**
 * @file MessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef MESSAGELINE_H
#define MESSAGELINE_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include "Message.h"
#include "ActivationGraphicsObjectBase.h"
#include "ClassReference.h"
#include "MethodReference.h"
#include "SequenceDiagram.h"
#include "SceneUpdateObservable.h"

class ActivationGraphicsObjectBase;

/**
 * Provides almost complete functionality, methods and variables for all messages.
 */
class MessageLine : public QGraphicsLineItem
{
public:
    /**
     * Class constructor
     *
     * @par Set ok and nok pen lines, arrow size and AcceptHoverEvents to true.
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param sequenceDiagram Pointer to edited sequence diagram
     */
    MessageLine(SceneUpdateObservable *sceneUpdateObservable, SequenceDiagram *sequenceDiagram);

    /**
     * Class destructor
     */
    ~MessageLine();
    /**
     * Initializes itself - store from and to object + store self in those objects.
     *
     * @return QString - error message. If ok, return empty string, else return error message.
     */
    virtual void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
            Message *newMessage, ClassReference &classReference);
    /**
     * Moves Line by dy (down if dy > 0, up if dy < 0). Move is done only if the move will be valid.
     *
     * @param dy difference position
     * @param moveIfNotValidBefore If true, object can be moved from invalid position to another invalid position.
     * If false, object will not be moved from invalid position to another invalid position.
     */
    void moveLine(qreal dy, bool moveIfNotValidBefore);

    /**
     * Getter for toObject.
     *
     * @return to object of message.
     */
    ActivationGraphicsObjectBase *getToObject()
    {
        return toObject;
    }

    /**
     * Update class reference
     */
    void updateClassReference(ClassReference newClassRef);
protected:
    /**
     * Pointer to observable for distributing information about scene change (dependency)
     */
    SceneUpdateObservable *sceneUpdateObservable;
    /**
     * Edited sequence diagram
     */
    SequenceDiagram *sequenceDiagram;
    /**
     * Class reference for message
     */
    ClassReference classRef;
    /**
     * If true, in edit dialog there will be cname line edit else there will NOT be any line edit.
     */
    bool editNameAllowed;
    /**
     * Tells if message creates object
     */
    bool createFlag;
    /**
     * Tells if message destroyes object
     */
    bool destroyFlag;
    /**
     * Widht of arrow
     */
    qreal arrowWidth;
    /**
     * Height of arrow
     */
    qreal arrowHeight;
    /**
     * Width of shape of line.
     */
    qreal lineShapeWidth = 10;

    /**
     * If true, line will go from first lifebox to second lifebox.
     * If false, line will go from first lifebox to second life line.
     */
    bool arrowToLifeLine;

    /**
     * Pen if message line is in good position (between both lifeboxes).
     */
    QPen linePenOk;

    /**
     * Pen if message line is NOT in good position (between both lifeboxes).
     */
    QPen linePenNok;

    /**
     * Pen used to draw if method is not valid. LinePenNok has higher priority it means
     * that if line is outside of lifeboxes, object will be drawn by linePenNok even if
     * it is unknown.
     */
    QPen unknownMethod;
    /**
     * message of this message line
     */
    Message *message;
    /**
     * sender object
     */
    ActivationGraphicsObjectBase *fromObject;
    /**
     * reciever object
     */
    ActivationGraphicsObjectBase *toObject;
    /**
     * Point that was pressed last time
     */
    QPointF lastPressed;

    /**
     * Draws line, arrow and
     *
     * @param painter to draw
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    /**
     * Returns bounding rectangle of line (line + arrow + text).
     *
     * @return bounding rectangle of line (line + arrow + text)
     */
    QRectF boundingRect() const;
    /**
     * Returns shape of line (line + arrow).
     *
     * @return shape of line (line + arrow)
     */
    QPainterPath shape() const;
    /**
     * Draws and arrow. Painter is rotated and translated, so the arrow is just drawen in this way ---|>
     *
     * @param painter
     */
    virtual void drawArrow(QPainter *painter) const;
    /**
     * Count lifebox position in scene coordinates
     *
     * @param object object from which will be rectangle counted
     * @return rectangle of lifebox in scene coordinates
     */
    QRectF getObjectLifeBox(ActivationGraphicsObjectBase *object) const;
    /**
     * To 'from' store a rect that is more left and to 'to' store a rect that is more right.
     *
     * @param from one of nodes
     * @param to one of nodes
     */
    void orderRects(QRectF *from, QRectF *to) const;
    /**
     * Returns bounding rect of text with current font.
     *
     * @param text - bounding rectangle around this text
     * @return bounding rectangle around parameter
     */
    QRectF getTextBoundingBox(QString text) const;
    /**
     * If cursor is in shape area, changes cursor to Qt::OpenHandCursor.
     *
     * @param event recieved event
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    /**
     * If mouse is in shape area, changes cursor to Qt::ClosedHandArea
     *
     * @param event recieved event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Event handler for mouse release event
     *
     * @par When mouse is released, moving stopped, so the state could be saved.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /**
     * If cursor is Qt::ClosedHandCursor, move line's y coord.
     *
     * @param event recieved event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Shows edit dialog and handles it's return value.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Checks if recieved pointer is within both boxes.
     *
     * @param lifeBoxPointer Pointer in interval <0,1> is position to check.
     * @return True if pointer is between start and end of both object pointers.
     * @return False if pointer is NOT between start and end of both object pointers .
     */
    bool isInObjectsLifeBox(qreal lifeBoxPointer);
    /**
     * Validates method reference with class reference. If method does not belong to class, return "fake" method reference.
     * Else, returns right reference.
     *
     * @param classRef reference to class
     * @param methodRef reference to method
     * @return Right method reference - true reference from fight class or "fake" reference
     */
    MethodReference validateNewReference(ClassReference classReference, MethodReference methodRef);
};

#endif // MESSAGELINE_H
