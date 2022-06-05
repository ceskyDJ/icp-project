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
QRectF ActivationGraphicsObjectBase::getTextBoundingBox(QString text) const
{
    text = (text.count() == 0)? "I":text;
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}
