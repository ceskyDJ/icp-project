/**
 * @file MessageLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "MessageLine.h"
#include <QPainterPath>
#include <QApplication>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include "MessageLineEditDialog.h"

/**
 * Set ok and nok pen lines, arrow size and AcceptHoverEvents to true.
 */
MessageLine::MessageLine()
{
    linePenOk = QPen{Qt::black, 2, Qt::SolidLine};
    linePenNok = QPen{Qt::magenta, 2, Qt::SolidLine};
    unknownMethod = QPen{Qt::blue, 2, Qt::SolidLine};
    arrowWidth = 20;
    arrowHeight = 20;
    setAcceptHoverEvents(true);
    arrowToLifeLine = false;
    leftToRight = true;
    editNameAllowed = true;
    createFlag = false;
    destroyFlag = false;
    fromObject = nullptr;
    toObject = nullptr;
}

/**
 * Destructor - removes self from list of messages.
 */
MessageLine::~MessageLine()
{
    if(fromObject != nullptr)
    {
        fromObject->removeMesage(this);
        if(destroyFlag)
            toObject->setDestroyed(false);
    }
    if(toObject != nullptr)
        toObject->removeMesage(this);
}

/**
 * Initializes itself - store from and to object + store self in those objects.
 */
void MessageLine::initialize(ActivationGraphicsObjectBase *from,
                             ActivationGraphicsObjectBase *to, Message *newMessage)
{
    fromObject = from;
    toObject = to;
    fromObject->addMesage(this);
    toObject->addMesage(this);
    message = newMessage;
    leftToRight = from->x() < to->x();
}

/**
 * Draws line, arrow and
 *
 * @param painter to draw
 */
void MessageLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    //get necessary innformation
    QPen usedPen = (isInObjectsLifeBox(message->getSendingTime()))? linePenOk:linePenNok;
    painter->setPen(usedPen);
    QRectF bound = boundingRect();
    QLineF line = QLineF{bound.x(), bound.y() + bound.height() - arrowHeight,
            bound.x() + bound.width(), bound.y() + bound.height() - arrowHeight};

    //move text rectangle and draw text in it.
    QRectF textRect = getTextBoundingBox(QString::fromStdString(message->getMethod().getReferredMethodName()));
    textRect.moveTop(- textRect.height() * 1.5);// move rect so it will be up on the line
    textRect.moveLeft(- textRect.width() * 0.5);// point 0,0 is in the middle of rectangle
    textRect.translate(line.x1() + line.length() * 0.5, line.y1()); //move the point into center of line
    if(usedPen != linePenNok && !message->getMethod().isValid()
            && message->getMethod().getReferredMethodName() != "<<create>>"
            && message->getMethod().getReferredMethodName() != "<<destroy>>")
        painter->setPen(unknownMethod);
    painter->drawText(textRect, QString::fromStdString(message->getMethod().getReferredMethodName()));
    painter->setPen(usedPen);

    if(!leftToRight) //arrow goes from right to left
        line.setLine(line.x2(), line.y2(), line.x1(), line.y2());

    line.setLength(line.length() - arrowWidth); //make space for arrow
    painter->drawLine(line);

    //set painter for drawing arrow - translate, rotate and set pen
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(line.p2().x(), line.y2());
    QPen temp = painter->pen();
    temp.setStyle(Qt::SolidLine);
    painter->setPen(temp);
    if(!leftToRight)
        painter->rotate(180);
    drawArrow(painter);
}

/**
 * Returns bounding rectangle of line (line + arrow + text).
 *
 * @return bounding rectangle of line (line + arrow + text)
 */
QRectF MessageLine::boundingRect() const
{
    static qreal textHeight = getTextBoundingBox("").height();
    QRectF fromLifebox = getObjectLifeBox(fromObject);
    QRectF toLifebox = getObjectLifeBox(toObject);

    qreal yPadding = ActivationGraphicsObjectBase::lifeSpaceStart +
            ActivationGraphicsObjectBase::headerHeight;
    qreal maxLifeboxHeight = ActivationGraphicsObjectBase::height - yPadding;

    orderRects(&fromLifebox, &toLifebox);
    QRectF toRet = QRectF{
            fromLifebox.x() + ActivationGraphicsObjectBase::lifeboxWidth,
            yPadding + maxLifeboxHeight * message->getSendingTime(),
            toLifebox.x() - fromLifebox.x() - ActivationGraphicsObjectBase::lifeboxWidth,
            arrowHeight + textHeight * 1.5 //padded because text should be up on the line
    };

   //move rectangle up so the line will lie on bottom edge of this rectangle + arrowHeight
   toRet.translate(0, - toRet.height() + arrowHeight);
   return toRet;
}

/**
 * Returns shape of line (line + arrow).
 *
 * @return shape of line (line + arrow)
 */
QPainterPath MessageLine::shape() const
{
    QPainterPath shapePath;
    QRectF boundRect = boundingRect();
    QRectF shapeRect{boundRect.x(), boundRect.y() + boundRect.height() - arrowHeight - lineShapeWidth,
                    boundRect.width(), arrowHeight  + lineShapeWidth};
    shapePath.addRect(shapeRect);
    return shapePath;
}

/**
 * Draws and arrow. Painter is rotated and translated, so the arrow is just drawen in this way ---|>
 *
 * @param painter
 */
void MessageLine::drawArrow(QPainter *painter) const
{
    painter->drawLine(QLineF{0, arrowHeight * 0.5, arrowWidth, 0});
    painter->drawLine(QLineF {0, -arrowHeight * 0.5, arrowWidth, 0});
    painter->drawLine(QLineF {0, 0, arrowWidth, 0});
}

/**
 * Count lifebox position in scene coordinates
 *
 * @param object object from which will be rectangle counted
 * @return rectangle of lifebox in scene coordinates
 */
QRectF MessageLine::getObjectLifeBox(ActivationGraphicsObjectBase *object) const
{
    QRectF rect = object->lifeBoxRect();
    rect.translate(
    object->pos().x(),
    0);

    return rect;
}

/**
 * To 'from' store a rect that is more left and to 'to' store a rect that is more right.
 *
 * @param from one of nodes
 * @param to one of nodes
 */
void MessageLine::orderRects(QRectF *from, QRectF *to) const
{
    if(from->x() > to->x())
    {
        QRectF temp = *from;
        *from = *to;
        *to = temp;
    }
}

/**
 * Returns bounding rect of text with current font.
 *
 * @param text - bounding rectangle around this text
 * @return bounding rectangle around parameter
 */
QRectF MessageLine::getTextBoundingBox(QString text) const
{
    text = (text.count() == 0)? "I":text;
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}

/**
 * If cursor is in shape area, changes cursor to Qt::OpenHandCursor.
 *
 * @param event recieved event
 */
void MessageLine::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(shape().contains(event->pos()))
        this->setCursor(Qt::OpenHandCursor);
    else
        this->setCursor(Qt::ArrowCursor);
}

/**
 * If mouse is in shape area, changes cursor to Qt::ClosedHandArea
 *
 * @param event recieved event
 */
void MessageLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(shape().contains(event->pos()))
    {
        lastPressed = event->pos();
        this->setCursor(Qt::ClosedHandCursor);
    }
}

/**
 * If cursor is Qt::ClosedHandCursor, move line's y coord.
 *
 * @param event recieved event
 */
void MessageLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->cursor() == Qt::ClosedHandCursor)
    {
        moveLine(event->pos().y() - lastPressed.y(), true);
        lastPressed = event->pos();
    }
}

/**
 * Checks if recieved pointer is within both boxes.
 *
 * @param lifeBoxPointer Pointer in interval <0,1> is position to check.
 * @return True if pointer is between start and end of both object pointers.
 * @return False if pointer is NOT between start and end of both object pointers .
 */
bool MessageLine::isInObjectsLifeBox(qreal lifeBoxPointer)
{
    qreal fromStart = fromObject->getStartOfLifeBox();
    qreal fromLifeLength = fromObject->getLifeLength();
    qreal toStart = toObject->getStartOfLifeBox();
    qreal toLifeLength = toObject->getLifeLength();

    if(fromStart > lifeBoxPointer || fromStart + fromLifeLength < lifeBoxPointer)
        return false;

    if(toStart > lifeBoxPointer || toStart + toLifeLength < lifeBoxPointer)
        return false;
    return true;
}

/**
 * Moves Line by dy (down if dy > 0, up if dy < 0). Move is done only if the move will be valid.
 *
 * @param dy difference position
 * @param moveIfNotValidBefore If true, object can be moved from invalid position to another invalid position.
 * If false, object will not be moved from invalid position to another invalid position.
 */
void MessageLine::moveLine(qreal dy, bool moveIfNotValidBefore)
{
    QRectF rect = boundingRect();

    qreal yPadding = ActivationGraphicsObjectBase::lifeSpaceStart + ActivationGraphicsObjectBase::headerHeight;
    qreal maxBoxHeight = ActivationGraphicsObjectBase::height - yPadding;

    qreal newSendingTime = (rect.y() + rect.height() - arrowHeight + dy - yPadding) / maxBoxHeight;

    // arrow is not too up or too down
    bool inAllowedHeight = (newSendingTime >= 0 && newSendingTime <= 1);
    //if object was not in valid position (between both lifeboxes), can this move? - It according to an argument
    bool moveIfNotValidBeforeAllowed = (!isInObjectsLifeBox(message->getSendingTime()) && moveIfNotValidBefore);
    //If the line wil bee moved and then object will be beteween lifeboxes, then true, else false
    bool willBeInLifeboxes = isInObjectsLifeBox(newSendingTime);
    if(inAllowedHeight && (willBeInLifeboxes || moveIfNotValidBeforeAllowed || createFlag || destroyFlag))
    {
        // If destroyFlag is true and object is under the life start, changes end of life of object
        if(destroyFlag && toObject->getStartOfLifeBox() < newSendingTime)
        {
            toObject->setLifeEndDestroy(newSendingTime);

            //if after move, object will not be in
            if(!isInObjectsLifeBox(newSendingTime))
                toObject->setLifeEndDestroy((rect.y() + rect.height() - arrowHeight + dy + 1 - yPadding) / maxBoxHeight);

        }
        if (createFlag) // means that method is not called externally
            toObject->setLifeStart(newSendingTime);

        message->setSendingTime(newSendingTime);
    }
}

/**
 * Shows edit dialog and handles it's return value.
 */
void MessageLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    MessageLineEditDialog dialog{editNameAllowed};
    int result = dialog.exec();
    if(result == QDialog::Accepted)
    {
        //TODO
    }
    else if(result == EditDialogBase::switchArrows)
    {
        ActivationGraphicsObjectBase *temp = fromObject;
        fromObject = toObject;
        toObject = temp;
        leftToRight = !leftToRight;
    }
    else if(result == EditDialogBase::remove)
        delete this;
}
