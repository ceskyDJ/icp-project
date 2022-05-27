/**
 * @class AssociationLine.h
 * Represents association line in class diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */

#include "AssociationLine.h"
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFontMetricsF>
#include <QRectF>

/**
 * @brief Line::mouseDoubleClickEvent Handles a double click event - shows input dialog to rename relationship
 * @param event
 */
void AssociationLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    associationName = QInputDialog::getText(event->widget(), "Edit name", "Enter new Name:",
                                            QLineEdit::Normal, associationName);
    update();
}

/**
 * Draws an Assotiation line with cardianlities and name of the relationship.
 *
 * @param painter to draw
 * @param option options
 * @param widget widget
 */
void AssociationLine::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(pen);
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    painter->drawLine(line);
    painter->translate(0.5 * line.p1() + 0.5 * line.p2());
    painter->setPen(pen);

    QRectF nameRect = prepareBoundingBox(getTextBoundingBox(associationName));

    int wayModifier = -1;
    if(line.angle() < 90 || line.angle() > 270)
    {
        painter->rotate(-line.angle());
    }
    else
    {
        painter->rotate(-line.angle() + 180);
        wayModifier = 1;
    }

    QRectF firstCardinalityRect = locateCardinality(prepareBoundingBox(getTextBoundingBox(firstCardinality)), wayModifier, line);
    QRectF secondCardinalityRect = locateCardinality(prepareBoundingBox(getTextBoundingBox(secondCardinality)), -wayModifier, line);

    painter->drawText(nameRect, Qt::TextSingleLine, associationName);
    painter->drawText(firstCardinalityRect, Qt::TextSingleLine, firstCardinality);
    painter->drawText(secondCardinalityRect, Qt::TextSingleLine, secondCardinality);
}

/**
 * Returns bounding rect of text with current font.
 *
 * @param text - bounding rectangle around this text
 * @return bounding rectangle around parameter
 */
QRectF AssociationLine::getTextBoundingBox(QString text) const
{
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}

/**
 * Override method which returns bounding rect of line.
 *
 * @return QRectF A rectnagle around classNode.
 */
QRectF AssociationLine::boundingRect() const
{
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    QPointF leftTop = QPointF{ std::min(line.p1().x(), line.p2().x()), std::min(line.p1().y(), line.p2().y())};
    QPointF rightBot = QPointF{ std::max(line.p1().x(), line.p2().x()), std::max(line.p1().y(), line.p2().y())};
    QRectF bounding = QRectF{leftTop,rightBot};
    QRectF name = getTextBoundingBox(associationName);

    bounding.adjust(-name.width() * 3 / 2, -name.height() * 3 / 2, name.width() * 3 / 2, name.height() * 3 / 2);
    return bounding;
}

/**
 * Places Bounding box up on the line.
 *
 * @param rect QRectF that will be placed over a line.
 * @return transformed rectangle
 */
QRectF AssociationLine::prepareBoundingBox(QRectF rect)
{
    qreal tempHeight = rect.height();
    qreal tempWidth = rect.width() + 2;
    rect.setLeft(-rect.width() / 2);
    rect.setWidth(tempWidth);
    rect.setTop(-(rect.height() * 3 / 2));
    rect.setHeight(tempHeight);
    return rect;
}

/**
 * Places cardinality to the end or start line.
 *
 * @param rect Rectangle that should be modified.
 * @param modifier -1 for start of line, 1 for end of line.
 * @param line line of relationship
 * @return modified QRectF
 */
QRectF AssociationLine::locateCardinality(QRectF rect, int modifier, QLineF line)
{
    qreal fcwidth = rect.width();
    rect.setLeft(line.length() / 2 * modifier + padding * (-modifier));
    rect.setWidth(fcwidth);
    return rect;
}
