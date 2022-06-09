/**
 * @file ActorGraphicsItem.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTORGRAPHICSITEM_H
#define ACTORGRAPHICSITEM_H

#include <QGraphicsItem>
#include "ActivationGraphicsObjectBase.h"
#include "Actor.h"
#include <QGraphicsSceneMouseEvent>

/**
 * Representation of actor in sequence diagram as graphics item.
 */
class ActorGraphicsItem : public ActivationGraphicsObjectBase
{
public:
    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     */
    explicit ActorGraphicsItem(SceneUpdateObservable *sceneUpdateObservable);

    /**
     * Class constructor
     *
     * @param sceneUpdateObservable Pointer to observable for distributing information about scene changes (dependency)
     * @param actor Pointer to actor to use
     */
    ActorGraphicsItem(SceneUpdateObservable *sceneUpdateObservable, Actor *actor);

    qreal width() const override;

    /**
     * Setter for new name of actor.
     *
     * @param newName new name to be set
     */
    void setName(const QString &newName)
    {
        actor->setName(newName.toStdString());
    }

    /**
     * Getter for actor
     *
     * @return pointer to actor
     */
    Actor *getActor()
    {
        return actor;
    }


    /**
     * Getter for actor.
     *
     * @return new object
     */
    MessageNode* getMessageNode() override
    {
        return actor;
    }
private:
    qreal personWidth = 50;
    Actor *actor;


    void heightUpdated(qreal newHeight);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF resizeArea();
};

#endif // ACTORGRAPHICSITEM_H
