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

/**
 * Initializes new graphics object in sequence diagram.
 *
 * @param newObject object which is going to be used as new object (it keeps pointer destination)
 * @param height Total height of object.
 */
ObjectGraphicsItem::ObjectGraphicsItem(Object *newObject, qreal height)
{
    object = newObject;
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    ObjectGraphicsItem::height = height;
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
    painter->setPen(QPen{Qt::black, 2, Qt::DashLine});
    painter->drawLine(textWidth / 2, headerHeight, textWidth / 2, height + getSceneHeight());
    painter->setPen(penToUse);

    //drawing lifebox
    QRectF lifeBox = lifeBoxRect();
    painter->fillRect(lifeBox, Qt::white);
    painter->drawRect(lifeBox);

    //drawing end and start of life area
    painter->setPen(QPen{Qt::darkGreen, 1, Qt::DashLine});
    painter->drawLine(0, headerHeight + lifeSpaceStart, textWidth, headerHeight + lifeSpaceStart);
    painter->drawLine(0, height, textWidth, height);


    painter->setPen(QPen{Qt::green, 1, Qt::SolidLine});
    painter->drawRect(boundingRect());

    painter->setPen(QPen{Qt::blue, 1, Qt::SolidLine});
    painter->drawPath(shape());
}

/**
 * Returns a bounding rect of whole item.
 *
 * @return bounding rect of whole item
 */
QRectF ObjectGraphicsItem::boundingRect() const
{
    QRectF bounding{
            0,
            0,
            width(),
            height};
    bounding.adjust(-selectedPen.width(), -selectedPen.width(), selectedPen.width(), selectedPen.width());
    return bounding;
}

/**
 * Return bounding box that is as big as is indeed for given text
 *
 * @param text text around which is rectangle counted for.
 * @return bounding rect around text
 */
QRectF ObjectGraphicsItem::getTextBoundingBox(QString text) const
{
    text = (text.count() == 0)? "I":text;
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}

/**
 * Count nad return object width.
 *
 * @return Object width.
 */
qreal ObjectGraphicsItem::width() const
{
    std::string longer = std::max(object->getInstanceClass().getReferredClassName() + ":",
                                  object->getName(),
                                  [](std::string a, std::string b) {return a.size() < b.size();});
    return getTextBoundingBox(QString::fromStdString(longer)).width() + textPadding * 2.0;
}

/**
 * Informs object that height was updated and object has to be redrawe
 *
 * @param newHeight new height of object
 */
void ObjectGraphicsItem::heightUpdated(qreal newHeight)
{
    height = newHeight;
    update();
}

/**
 * Returns scene height.
 *
 * @return Height of first scene it appears to.
 */
int ObjectGraphicsItem::getSceneHeight()
{
    QList <QGraphicsView *> allViews = scene()->views();
    QGraphicsView *firstView = allViews[0];
    return firstView->height();
}

/**
 * Set selected to true, then saves mouse coordinates to variable pressedPos.
 * When is clicked into area to resize lifebox, setsCursor to Qt::SizeVerCursor.
 * If mouse coordinates are in lifebox area, sets cursor to Qt::ClosedHandCursor.
 *
 * @param event - recieved QGraphicsSceneMouseEvent
 */
void ObjectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
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
    if(this->cursor() == Qt::ClosedHandCursor)
    {
        QRectF lifebox = lifeBoxRect();
        qreal dy = event->pos().y() - pressedPos.y();

        //if new position of lifebox is in life area, then moves self by coordinates
        if((lifebox.y() + dy >= headerHeight + lifeSpaceStart) && (lifebox.y() + dy + lifebox.height() <= height))
        {
            qreal maxBoxHeight = height - lifeSpaceStart - headerHeight;
            object->setLifeStart((lifebox.y() + dy - lifeSpaceStart - headerHeight) / maxBoxHeight);
        }

    }
    else if(this->cursor() == Qt::SizeVerCursor)
    {
        QRectF lifebox = lifeBoxRect();
        qreal dy = event->pos().y() - pressedPos.y();
        qreal newLength = (lifebox.height() + dy) / (height - lifeSpaceStart - headerHeight);
        if (lifebox.y() + dy + lifebox.height() > height)
        {
            height += dy;
            update();
        }
        else if(newLength <= 0)
            return;
        else
            object->setLifeLength(newLength);
    }

    update();
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
    return QRectF{lifeBox.x() - 10, lifeBox.y() + lifeBox.height() - 10,
                           lifeBox.width() + 20, 20};
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
 *
 * @param event recieved event
 */
void ObjectGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF headerArea{0,0, width(), headerHeight};
    if(headerArea.contains(event->pos()))
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
        else if (result == QDialog::Rejected)
            delete this;
    }
}
