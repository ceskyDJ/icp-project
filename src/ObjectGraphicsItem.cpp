/**
 * @file ObjectGraphicsItem.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ObjectGraphicsItem.h"
#include "AssociationLine.h"
#include <QGraphicsView>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include "ObjectGraphicsItemEditDialog.h"
#include "DestroyMessageLine.h"

/**
 * Initializes new graphics object in sequence diagram if height is negative, keeps it value
 *
 * @param newObject object which is going to be used as new object (it keeps pointer destination)
 * @param height Total height of object.
 */
ObjectGraphicsItem::ObjectGraphicsItem(Object *newObject)
{
    object = newObject;
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    destroyed = false;
}

/**
 * Paints object's activation rectangle and his head (class + name).
 *
 * @param painter painter to draw everything
 */
void ObjectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    prepareGeometryChange();
    painter->fillRect(boundingRect(), Qt::white);
    QPen penToUse;
    if(option->state & QStyle::State_Selected)
        penToUse = selectedPen;
    else
        penToUse = regularPen;

    painter->setPen(penToUse);
    qreal textWidth = width();

    //drawing header
    painter->drawRect(0,0, textWidth, headerHeight);
    painter->drawText(0,0, textWidth, headerHeight, Qt::AlignCenter,
                      QString::fromStdString(":" + object->getInstanceClass().getReferredClassName() + "\n" + object->getName()));
    //drawing life line
    painter->setPen(lifeLinePen);
    painter->drawLine(textWidth / 2, headerHeight, textWidth / 2, height);
    painter->setPen(penToUse);

    //drawing lifebox
    QRectF lifeBox = lifeBoxRect();
    painter->fillRect(lifeBox, Qt::white);
    painter->drawRect(lifeBox);

    //drawing end and start of life area
    painter->setPen(lifeLineBorderPen);
    painter->drawLine(0, headerHeight + lifeSpaceStart, textWidth, headerHeight + lifeSpaceStart);
    painter->drawLine(0, height, textWidth, height);

    if(destroyed)//draw destroy cross
    {
        painter->setPen(QPen{Qt::black, 2, Qt::SolidLine});
        QRectF crossRect{-destroyCrossSize * 0.5, -destroyCrossSize * 0.5,
                          destroyCrossSize, destroyCrossSize};
        crossRect.translate(lifeBox.x() + lifeboxWidth * 0.5,
                            lifeBox.y() + lifeBox.height() + destroyCrossSize * 0.5);
        painter->drawLine(crossRect.x(), crossRect.y(),
                          crossRect.x() + crossRect.width(), crossRect.y() + crossRect.height());
        painter->drawLine(crossRect.x() + crossRect.width(), crossRect.y(),
                          crossRect.x(), crossRect.y() + crossRect.height());
    }

    painter->setPen(QPen{Qt::blue, 1, Qt::SolidLine});
    painter->drawRect(boundingRect());
}

/**
 * Count nad return object width.
 *
 * @return Object width.
 */
qreal ObjectGraphicsItem::width() const
{
    qreal longer = std::max(
                getTextBoundingBox(
                QString::fromStdString(object->getInstanceClass().getReferredClassName() + ":")).width(),
                getTextBoundingBox(QString::fromStdString(object->getName())).width());
    return longer + textPadding * 2.0;
}

/**
 * Saves mouse coordinates to variable pressedPos.
 * When is clicked into area to resize lifebox, setsCursor to Qt::SizeVerCursor.
 * If mouse coordinates are in lifebox area, sets cursor to Qt::ClosedHandCursor.
 *
 * @param event - recieved QGraphicsSceneMouseEvent
 */
void ObjectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressedPos = event->pos();
    if(resizeArea().contains(event->pos()))
        return;

    if(lifeBoxRect().contains(event->pos()))
    {
        this->setCursor(Qt::ClosedHandCursor);
    }
}

/**
 * When cursor is Qt::ClosedHandCursor, than moves lifebox by mouse coordinates.y() - pressedPos.y().
 * When cursor is Qt::SizeVerCursor, than resizes object by mouse coordinates.y() - pressedPos.y().
 * All counted values are normalized and saved into object.
 *
 * @param event recieved QGraphicsSceneMouseEvent
 */
void ObjectGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    if(this->cursor() == Qt::ClosedHandCursor)
    {
        QRectF lifebox = lifeBoxRect();
        qreal dy = event->pos().y() - pressedPos.y();

        //if new position of lifebox is in life area, then moves self by coordinates
        if((lifebox.y() + dy >= headerHeight + lifeSpaceStart) && (lifebox.y() + dy + lifebox.height() <= height))
        {
            qreal maxBoxHeight = height - lifeSpaceStart - headerHeight;
            object->setLifeStart((lifebox.y() + dy - lifeSpaceStart - headerHeight) / maxBoxHeight);
            moveAllMessages(dy);
        }

    }
    else if(this->cursor() == Qt::SizeVerCursor)//resizing mode
    {
        QRectF lifebox = lifeBoxRect();
        qreal dy = event->pos().y() - pressedPos.y();
        qreal newLength = (lifebox.height() + dy) / (height - lifeSpaceStart - headerHeight);
        if (lifebox.y() + dy + lifebox.height() > height)//lifebox could be outside of borders
        {
            pressedPos = event->pos();
            return;
        }
        else if(newLength <= 0) // length is too small
            return;
        if(destroyed) //destroyed flag on
            getDestroyMessage()->moveLine(dy, true);
        else //everything ok
            object->setLifeLength(newLength);
    }
    pressedPos = event->pos();
}

/**
 * Count and return lifebox rectangle within item pos.
 *
 * @return lifebox rectangle within item pos
 */
QRectF ObjectGraphicsItem::lifeBoxRect()
{
    qreal maxBoxHeight = height - lifeSpaceStart - headerHeight;
    qreal myBoxHeight = maxBoxHeight * object->getLifeLength();
    return QRectF{ width() / 2 - lifeboxWidth * 0.5,
                lifeSpaceStart + headerHeight + maxBoxHeight * object->getLifeStart(),
                lifeboxWidth, myBoxHeight};
}

/**
 * If mouse is in resize are, then sets cursor to Qt::SizeVerCursor. If mouse is in
 * lifeboxArea then sets cursor to Qt::OpenHandCursor. If mouse is everywhere else,
 * sets cursor to Qt::ArrowCursor.
 *
 * @param event recieved event
 */
void ObjectGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(resizeArea().contains(event->pos()))
        this->setCursor(Qt::SizeVerCursor);
    else if (lifeBoxRect().contains(event->pos()))
        this->setCursor(Qt::OpenHandCursor);
    else
        this->setCursor(Qt::ArrowCursor);
}

/**
 * Returns area, where should be cursor changed into resize cursor.
 *
 * @return Area, where should be cursor changed into resize cursor.
 */
QRectF ObjectGraphicsItem::resizeArea()
{
    QRectF lifeBox = lifeBoxRect();
    static const qreal resizePadH = 10;
    return QRectF{lifeBox.x(), lifeBox.y() + lifeBox.height() - resizePadH,
                              lifeBox.width(), resizePadH * 2};
}

/**
 * Sets cursor to arrow when leaving with hover.
 */
void ObjectGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    this->setCursor(Qt::ArrowCursor);
}

/**
 * If cursor is in header area and double clicked, the dialog for edit object name and class will be shown
 * and handled.
 */
void ObjectGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    ObjectGraphicsItemEditDialog dialog{QString::fromStdString(object->getName()),
                QString::fromStdString(object->getInstanceClass().getReferredClassName())};
    int result = dialog.exec();
    if(result == QDialog::Accepted)
    {
        object->setName(dialog.getObjectName().toStdString());
        //TODO set class reference
        update();
    }
    else if (result == ObjectGraphicsItemEditDialog::remove)
        delete this;

}

/**
 * Getter for start of life line.
 *
 * @return start of life line from Object.
 */
qreal ObjectGraphicsItem::getStartOfLifeBox()
{
    return object->getLifeStart();
}

/**
 * Getter for start of life line.
 *
 * @return start of life line from Object.
 */
qreal ObjectGraphicsItem::getLifeLength()
{
    return object->getLifeLength();
}

/**
 * Move all lines by dy.
 *
 * @param dy - difference to move
 */
void ObjectGraphicsItem::moveAllMessages(qreal dy)
{
    for(MessageLine *msgLine:messages)
        msgLine->moveLine(dy, false);
}

/**
 * Set life start to position of lifeStart argument.
 *
 * @param lifeStart new start of life - it has to be in interval <0,1>.
 */
void ObjectGraphicsItem::setLifeStart(qreal lifeStart)
{
    object->setLifeStart(lifeStart);
    if(object->getLifeStart() + object->getLifeLength() > 1)
        object->setLifeLength(1 - object->getLifeStart());
}

/**
 * Set lifelength so it ends in moment of lifeEnd argument.
 *
 * @param lifeEnd time when life should end - it has to be in interval <0,1>.
 */
void ObjectGraphicsItem::setLifeEndDestroy(qreal lifeEnd)
{
    object->setLifeLength(lifeEnd - object->getLifeStart());
    if(object->getLifeStart() + object->getLifeLength() > 1)
        object->setLifeLength(1 - object->getLifeStart());
}

/**
 * Iterate throught messages and if find destroy message, return it.
 *
 * @return destroyMessage Destroy message if found, else return nullptr.
 */
MessageLine * ObjectGraphicsItem::getDestroyMessage()
{
    for(MessageLine *msg:messages)
    {
        DestroyMessageLine *temp = dynamic_cast<DestroyMessageLine *>(msg);
        if(temp)
            return temp;
    }
    return nullptr;
}
