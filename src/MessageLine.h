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

    virtual void initialize(ActivationGraphicsObjectBase *from, ActivationGraphicsObjectBase *to,
            Message *newMessage, ClassReference &classReference);
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
    ClassReference classRef;
    bool editNameAllowed;
    bool createFlag;
    bool destroyFlag;
    qreal arrowWidth;
    qreal arrowHeight;
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
    Message *message;
    ActivationGraphicsObjectBase *fromObject;
    ActivationGraphicsObjectBase *toObject;
    QPointF lastPressed;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void drawArrow(QPainter *painter) const;
    QRectF getObjectLifeBox(ActivationGraphicsObjectBase *object) const;
    void orderRects(QRectF *from, QRectF *to) const;
    QRectF getTextBoundingBox(QString text) const;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    bool isInObjectsLifeBox(qreal lifeBoxPointer);
    MethodReference validateNewReference(ClassReference classReference, MethodReference methodRef);
};

#endif // MESSAGELINE_H
