/**
 * @file ObjectGraphicsItem.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef OBJECTGRAPHICSITEM_H
#define OBJECTGRAPHICSITEM_H

#include <QGraphicsItem>
#include "Object.h"
#include <QPen>
#include "ActivationGraphicsObjectBase.h"
#include <QPainterPath>
#include "ClassDiagram.h"

/**
 * Representation of object in sequence diagram as graphics item.
 */
class ObjectGraphicsItem : public ActivationGraphicsObjectBase
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param newObject Pointer to object represented by this graphics item
     * @param classDiagram Pointer to class diagram
     */
    ObjectGraphicsItem(SceneUpdateObservable *sceneUpdateObservable, Object *newObject, ClassDiagram *classDiagram);
    /**
    * Count nad return object width.
    *
    * @return Object width.
    */
    qreal width() const override;
    /**
     * Count and return lifebox rectangle within item pos.
     *
     * @return lifebox rectangle within item pos
     */
    QRectF lifeBoxRect() override;
    /**
     * Getter for start of life line.
     *
     * @return start of life line from Object.
     */
    qreal getStartOfLifeBox() override;
    /**
     * Getter for start of life line.
     *
     * @return start of life line from Object.
     */
    qreal getLifeLength() override;
    /**
    * Dialog for edit object name and class will be shown and handled.
    */
    void showEditDialog(bool logChange);

    /**
     * Getter for object property
     *
     * @return object in this
     */
    Object *getObject()
    {
        return object;
    }

    /**
     * Getter for object.
     *
     * @return new object
     */
    MessageNode* getMessageNode() override
    {
        return object;
    }

    /**
     * Getter for class referrence object.
     *
     * @return object class reference.
     */
    virtual ClassReference getClassReference() override
    {
        return object->getInstanceClass();
    }
    /**
     * Iterate throught messages and if find destroy message, return it.
     *
     * @return destroyMessage Destroy message if found, else return nullptr.
     */
    MessageLine *getDestroyMessage();
    /**
     * Iterate throught messages and if find create message, return it.
     *
     * @return CreateMessage Create message if found, else return nullptr.
     */
    MessageLine *getCreateMessage();

    /**
     * Setter fo class reference.
     *
     * @param newClassRef new class reference to be set.
     */
    void setClassReference(ClassReference newClassRef)
    {
        object->setInstanceClass(newClassRef);
    }
protected:
    /**
     * Data source for combobox item.
     */
    ClassDiagram *classDiagram;
    /**
     * Padding int object header |[padding]<NAME>[Padding]|
     */
    qreal textPadding = 10.0;
    /**
     * Object entity
     */
    Object *object;
    /**
     * Paints object's activation rectangle and his head (class + name).
     *
     * @param painter painter to draw everything
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    /**
     * Dialog for edit object name and class will be shown and handled.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
    /**
     * Saves mouse coordinates to variable pressedPos.
     * When is clicked into area to resize lifebox, setsCursor to Qt::SizeVerCursor.
     * If mouse coordinates are in lifebox area, sets cursor to Qt::ClosedHandCursor.
     *
     * @param event - recieved QGraphicsSceneMouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * Mouse release event handler
     *
     * @par When mouse is released, resizing just ended, so scene changing is done.
     *
     * @param event Event details
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * When cursor is Qt::ClosedHandCursor, than moves lifebox by mouse coordinates.y() - pressedPos.y().
     * When cursor is Qt::SizeVerCursor, than resizes object by mouse coordinates.y() - pressedPos.y().
     * All counted values are normalized and saved into object.
     *
     * @param event recieved QGraphicsSceneMouseEvent
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * If mouse is in resize are, then sets cursor to Qt::SizeVerCursor. If mouse is in
     * lifeboxArea then sets cursor to Qt::OpenHandCursor. If mouse is everywhere else,
     * sets cursor to Qt::ArrowCursor.
     *
     * @param event recieved event
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    /**
     * Sets cursor to arrow when leaving with hover.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    /**
     * Returns area, where should be cursor changed into resize cursor.
     *
     * @return Area, where should be cursor changed into resize cursor.
     */
    QRectF resizeArea();
    /**
     * Move all lines by dy.
     *
     * @param dy - difference to move
     */
    void moveAllMessages(qreal dy);
    /**
     * Set life start to position of lifeStart argument.
     *
     * @param lifeStart new start of life - it has to be in interval <0,1>.
     */
    void setLifeStart(qreal lifeStart) override;
    /**
     * Set lifelength so it ends in moment of lifeEnd argument.
     *
     * @param lifeEnd time when life should end - it has to be in interval <0,1>.
     */
    void setLifeEndDestroy(qreal lifeEnd) override;
    /**
     * @brief Set the Destroyed Flaf
     *
     * @param destroyed new value of flag
     */
    void setDestroyed(bool destroyed);
    /**
     * Updates all messages class refernce that are sent to this object.
     *
     * @param classRef new class reference
     */
    void updateMessagesClassReference(ClassReference newClassRef);
};

#endif // OBJECTGRAPHICSITEM_H
