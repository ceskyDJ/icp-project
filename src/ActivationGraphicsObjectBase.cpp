/**
 * @file ActivationGraphicsObjectBase.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ActivationGraphicsObjectBase.h"
#include <QApplication>

qreal ActivationGraphicsObjectBase::height = 500;
qreal ActivationGraphicsObjectBase::headerHeight = 60;
qreal ActivationGraphicsObjectBase::lifeSpaceStart = 10;
qreal ActivationGraphicsObjectBase::lifeboxWidth = 20;
qreal ActivationGraphicsObjectBase::destroyCrossSize = 30;

/**
 * Returns bounding rect of actor.
 *
 * @return bounding rect of actor
 */
QRectF ActivationGraphicsObjectBase::boundingRect() const
{
     QRectF bounding{
        0,
        0,
        width(),
        height + destroyCrossSize};
     bounding.adjust(-selectedPen.width(), -selectedPen.width(), selectedPen.width(), selectedPen.width());
     return bounding;
}


/**
 * Return bounding box that is as big as is indeed for given text
 *
 * @param text text around which is rectangle counted for.
 * @return bounding rect around text
 */
QRectF ActivationGraphicsObjectBase::getTextBoundingBox(QString text) const
{
    text = (text.count() == 0)? "I":text;
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}

/**
 * @brief lifeBoxRect Count and return area where lifebox is located.
 * If not overrided, return whole lifebox available area.
 *
 * @return area where lifebox is located
 */
QRectF ActivationGraphicsObjectBase::lifeBoxRect()
{
    return QRectF{
        width() * 0.5 - lifeboxWidth * 0.5,
        lifeSpaceStart + headerHeight,
        lifeboxWidth * 0.5,
        height - lifeSpaceStart - headerHeight
    };
}

/**
 * Add message into object messages
 *
 * @param message message to add
 */
void ActivationGraphicsObjectBase::addMesage(MessageLine *message)
{
    messages.push_back(message);
}

/**
 * Remove message from messages
 *
 * @param message message to remove
 */
void ActivationGraphicsObjectBase::removeMesage(MessageLine *message)
{
    int index = messages.indexOf(message);
    if (index >= 0)
        messages.remove(index);
}

/**
 * Destructor - deletes all messages from self.
 */
ActivationGraphicsObjectBase::~ActivationGraphicsObjectBase()
{
    for(MessageLine *line : messages)
        delete line;
}

/**
 * Return width of whole object.
 * @return width of whole object
 */
qreal ActivationGraphicsObjectBase::width() const
{
    return 0.0;
}

/**
 * Returns life length of object in interval <0,1>. If not overriden, return 1.
 *
 * @return life length of object in interval <0,1>, if not overriden, return 1 1.
 */
qreal ActivationGraphicsObjectBase::getLifeLength()
{
    return 1.0;
}

/**
 * Returns start of life box in interval <0,1>. If not overriden, return 0.
 *
 * @return start of life box in interval <0,1>, if not overriden return 0
 */
qreal ActivationGraphicsObjectBase::getStartOfLifeBox()
{
    return 0.0;
}

/**
 * Set life start to position of lifeStart argument. If not overriden, does nothign.
 */
void ActivationGraphicsObjectBase::setLifeStart(qreal)
{

}

/**
 * Set lifelength so it ends in moment of lifeEnd argument. If not overriden, does nothign.
 */
void ActivationGraphicsObjectBase::setLifeEndDestroy(qreal)
{

}

/**
 * Set destroyed flag.
 *
 * @param destroyed true/false to set destroyed flag
 */
void ActivationGraphicsObjectBase::setDestroyed(bool destroyed)
{
    this->destroyed = destroyed;
}
