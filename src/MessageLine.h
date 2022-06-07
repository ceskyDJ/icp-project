/**
 * @class MessageLine
 * Base functionality, methods and variables for messages.
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

class ActivationGraphicsObjectBase;

class MessageLine : public QGraphicsLineItem
{
public:
    MessageLine();
    ~MessageLine();
    virtual void initialize(ActivationGraphicsObjectBase *from,
                    ActivationGraphicsObjectBase *to, Message *newMessage);
    void moveLine(qreal dy, bool moveIfNotValidBefore);

protected:
    bool leftToRight;
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


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void drawArrow(QPainter *painter) const;
    QRectF getObjectLifeBox(ActivationGraphicsObjectBase *object) const;
    void orderRects(QRectF *from, QRectF *to) const;
    QRectF getTextBoundingBox(QString text) const;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    bool isInObjectsLifeBox(qreal lifeBoxPointer);
};

#endif // MESSAGELINE_H
