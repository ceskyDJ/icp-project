/**
 * @file ActivationObjectEmitter.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ActivationObjectEmitter.h"

ActivationObjectEmitter::ActivationObjectEmitter(QObject *parent, ActivationGraphicsObjectBase *activationObject)
    : QObject{parent}, activationObject{activationObject}
{ }


/**
 * Emits a signal objectPressed.
 */
void ActivationObjectEmitter::emitPressedSignal()
{
    emit objectPressed(activationObject);
}

/**
 * Emits a signal removeObject
 */
void ActivationObjectEmitter::emitRemoveObjectSignal(bool logChange)
{
    emit removeObject(activationObject, logChange);
}

/**
 * Emits a signal moveLeft.
 */
void ActivationObjectEmitter::emitMoveLeft()
{
    emit moveLeft(activationObject);
}
/**
 * Emits a singal moveRight.
 */
void ActivationObjectEmitter::emitMoveRight()
{
    emit moveRight(activationObject);
}
