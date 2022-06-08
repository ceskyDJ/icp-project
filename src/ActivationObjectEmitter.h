/**
 * @file ActivationObjectEmitter.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTIVATIONOBJECTEMITTER_H
#define ACTIVATIONOBJECTEMITTER_H

#include <QObject>

class ActivationGraphicsObjectBase;

/**
 * Support class to provide slots and signals to ActivationGraphicsObjectBase items.
 */
class ActivationObjectEmitter : public QObject
{
    Q_OBJECT
public:
    explicit ActivationObjectEmitter(QObject *parent = nullptr,
                                     ActivationGraphicsObjectBase *activationObject = nullptr);
    /**
     * Emits a signal objectPressed.
     */
    void emitPressedSignal();
    /**
     * Emits a signal removeObject
     *
     * @param logChange True - change will be loged, false = change will NOT be logged
     */
    void emitRemoveObjectSignal(bool logChange);

    /**
     * Emits a signal moveLeft.
     */
    void emitMoveLeft();
    /**
     * Emits a singal moveRight.
     */
    void emitMoveRight();
private:
    ActivationGraphicsObjectBase *activationObject;

signals:
    void objectPressed(ActivationGraphicsObjectBase *activationObject);
    void removeObject(ActivationGraphicsObjectBase *activationObject, bool logChange);
    void moveLeft(ActivationGraphicsObjectBase *activationObject);
    void moveRight(ActivationGraphicsObjectBase *activationObject);
};

#endif // ACTIVATIONOBJECTEMITTER_H
