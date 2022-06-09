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
    /**
     * @brief Construct a new Activation Object Emitter object
     * 
     * @param parent as every object 
     * @param activationObject objcet that will be sent into all signals
     */
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
    /**
     * Object that will be sent on any emit signal. 
     */
    ActivationGraphicsObjectBase *activationObject;

signals:
    /**
     * Signal is emitted when user click on the objcet.
     * 
     * @param activationObject Object that was click on.
     */
    void objectPressed(ActivationGraphicsObjectBase *activationObject);
    /**
     * Signal will be emitted if object should be removed
     * 
     * @param activationObject object to remove
     * @param logChange sceneupadte
     */
    void removeObject(ActivationGraphicsObjectBase *activationObject, bool logChange);
    /**
     * Siganl is emitted when activationItem should be moved to left.
     * 
     * @param activationObject object to move
     */
    void moveLeft(ActivationGraphicsObjectBase *activationObject);
    /**
     * Siganl is emitted when activationItem should be moved to right.
     * 
     * @param activationObject object to move
     */
    void moveRight(ActivationGraphicsObjectBase *activationObject);
};

#endif // ACTIVATIONOBJECTEMITTER_H
