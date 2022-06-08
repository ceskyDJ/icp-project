/**
 * @file ActorGraphicsItem.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ActorGraphicsItem.h"
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>
#include "ActorGraphicsItemEditDialog.h"

/**
 * Class constructor
 */
ActorGraphicsItem::ActorGraphicsItem()
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges);
    destroyed = false;
    actor = new Actor("Actor " + std::to_string(objectCounter));
    order = getObjectCounter();
    incObjectCounter();
    setZValue(-1);
}

/**
 * Class constructor
 *
 * @param actor Pointer to actor to use
 */
ActorGraphicsItem::ActorGraphicsItem(Actor *actor): ActorGraphicsItem()
{
    this->actor = actor;
}

/**
 * Return width of object
 *
 * @return
 */
qreal ActorGraphicsItem::width() const
{
    return std::max(personWidth, getTextBoundingBox(QString::fromStdString(actor->getName())).width());
}

/**
 * Draws actor object.
 *
 * @param painter to draw
 * @param option recieved option
 */
void ActorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    prepareGeometryChange();
    painter->fillRect(boundingRect(), Qt::white);
    QPen penToUse;
    QImage actorImage;
    if(option->state & QStyle::State_Selected)
    {
        penToUse = selectedPen;
        actorImage = QImage{":/selActorMin.png"};
    }
    else
    {
        penToUse = regularPen;
        penToUse.setColor(drawColor);
        actorImage = QImage{":/actorMin.png"};
    }
    qreal textHeight = getTextBoundingBox("").height();

    painter->setPen(penToUse);
    painter->fillRect(boundingRect(), Qt::white);//fill object because of non-transparency
    //draws actor image + text
    qreal textPad = 5;

    painter->drawImage(QRectF{0, 0, width(), headerHeight - textHeight - 5}, actorImage);
    painter->drawText(QRectF{0, headerHeight - textHeight - 5, width(), textPad + textHeight},
                      Qt::AlignCenter,
                      QString::fromStdString(actor->getName()));


    //draw lifebox
    painter->drawRect(width() *0.5 - lifeboxWidth * 0.5, lifeSpaceStart + headerHeight, lifeboxWidth,
                      height - lifeSpaceStart - headerHeight);

    //draw lifebox boreder
    painter->setPen(lifeLineBorderPen);
    painter->drawLine(0, lifeSpaceStart + headerHeight, width(), lifeSpaceStart + headerHeight);
    painter->drawLine(0, height, width(), height);
}

/**
 * Set pressed coordinates on cursor position
 *
 * @param event recieved event
 */
void ActorGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressedPos = event->pos();
    emitter.emitPressedSignal();
}

/**
 * If cursor is Qt::SizeVerCursor then changes height. If cursor is Qt::sizeAllCursor,
 * there is possible change to move whole object
 *
 * @param event recieved event
 */
void ActorGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal dy = event->pos().y() - pressedPos.y();
    if (this->cursor() == Qt::SizeVerCursor && dy + height >= minHeight)
        height += dy;
    else if (this->cursor() == Qt::SizeAllCursor)
    {
        qreal sx =event->scenePos().x();
        qreal sp = this->scenePos().x();
        (void)sx;
        (void)sp;
        int dx = (int)((event->scenePos().x() - this->scenePos().x()) / (objectPadding - moveTollerance));
        if(dx == -1)
            emitter.emitMoveLeft();
        else if (dx == 1)
            emitter.emitMoveRight();
    }
    pressedPos = event->pos();
}

/**
 * When cursor is in reize area, changes cursor to Qt::SizeVerCursor.
 * If is in wholeObjectMoveRect, set cursor to Qt::sizeAllCursor.
 *
 * @param event recieved event
 */
void ActorGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (resizeArea().contains(event->pos()))
        this->setCursor(Qt::SizeVerCursor);
    else if (getWholeObjectMoveRect().contains(event->pos()))
        this->setCursor(Qt::SizeAllCursor);
    else
        this->setCursor(Qt::ArrowCursor);

}

/**
 * Returns resize area - arean when it is possible to change height
 *
 * @return Rectangle (area) where cursor should be
 */
QRectF ActorGraphicsItem::resizeArea()
{
    return QRectF{
        0
        ,height - 10
        ,width()
        ,height + 10
    };
}

/**
 * Shows edit dialog and hanldes return code.
 */
void ActorGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    ActorGraphicsItemEditDialog dialog{QString::fromStdString(actor->getName())};
    int result = dialog.exec();

    if(result == QDialog::Accepted)
        actor->setName(dialog.getActorName().toStdString());
    else if (result == ActorGraphicsItemEditDialog::remove)
        emitter.emitRemoveObjectSignal(true);
}
