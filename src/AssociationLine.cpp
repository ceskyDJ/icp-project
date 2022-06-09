/**
 * @file AssociationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */

#include "AssociationLine.h"
#include <QGraphicsSceneMouseEvent>
#include <QFontMetricsF>
#include <QRectF>
#include "AssociationLineEditDialog.h"
#include "UndirectedAssociation.h"

/**
 * Handles a double click event - shows input dialog to rename relationship
 * 
 * @param event recieved event
 */
void AssociationLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    UndirectedAssociation *oldUndirectedAssociation = dynamic_cast<UndirectedAssociation *>(
        existingRelationships->find(this)->second);
    UndirectedAssociation newUndirectedAssociation{*oldUndirectedAssociation};

    AssociationLineEditDialog editDialog{&newUndirectedAssociation};
    editDialog.exec();
    if(editDialog.accepted() && newUndirectedAssociation != *oldUndirectedAssociation) {
        // Update
        setName(QString::fromStdString(newUndirectedAssociation.getName()));
        setFirstCardinality(QString::fromStdString(newUndirectedAssociation.getFirstClassCardinality()));
        setSecondCardinality(QString::fromStdString(newUndirectedAssociation.getSecondClassCardinality()));
        update();

        // Update class diagram
        *oldUndirectedAssociation = newUndirectedAssociation;

        sceneUpdateObservable->sceneChanged();
    } else if(editDialog.deleteRelationship()) {
        // Delete from class diagram and memory
        Relationship *undirectedAssociation = existingRelationships->find(this)->second;
        classDiagram->removeRelationship(undirectedAssociation);
        delete undirectedAssociation;

        // Delete from existing relationships
        existingRelationships->erase(this);

        // Delete from memory and scene
        delete this;

        sceneUpdateObservable->sceneChanged();
    }
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
    prepareGeometryChange();
    specialSelfWidthPadding = std::max(getTextBoundingBox(associationName).width() - selfPadding,
                                       getTextBoundingBox(firstCardinality).width());
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);
    if(selfRealtionshipFlag)
    {
        paintSelfRelationship(painter);
        return;
    }


    QLineF line = getShortestLine(fromClassNode, toClassNode);
    painter->drawLine(line);
    painter->translate(0.5 * line.p1() + 0.5 * line.p2());

    QRectF nameRect = prepareBoundingBox(getTextBoundingBox(associationName));

    int wayModifier = -1;
    qreal firstAdditionPadding = 0;
    qreal secondAdditionPadding = 0;
    if(line.angle() < 90 || line.angle() > 270)
    {
        painter->rotate(-line.angle());
        secondAdditionPadding = getTextBoundingBox(secondCardinality).width();
    }
    else
    {
        painter->rotate(-line.angle() + 180);
        wayModifier = 1;
        firstAdditionPadding = getTextBoundingBox(firstCardinality).width();
    }

    QRectF firstCardinalityRect = locateCardinality(prepareBoundingBox(getTextBoundingBox(firstCardinality)),
                                                    wayModifier, line, firstAdditionPadding);
    QRectF secondCardinalityRect = locateCardinality(prepareBoundingBox(getTextBoundingBox(secondCardinality)),
                                                    -wayModifier, line, secondAdditionPadding);

    painter->drawText(nameRect, Qt::TextSingleLine, associationName);
    painter->drawText(firstCardinalityRect, Qt::TextSingleLine, firstCardinality);
    painter->drawText(secondCardinalityRect, Qt::TextSingleLine, secondCardinality);
}

/**
 * Adjusts regular boundingbox
 *
 * @param rect that should be adjusted
 */
void AssociationLine::adjustBounding(QRectF *rect) const
{
    QRectF name = getTextBoundingBox(associationName);
    rect->adjust(-name.width() * 3 / 2, -name.height() * 3 / 2, name.width() * 3 / 2, name.height() * 3 / 2);
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
QRectF AssociationLine::locateCardinality(QRectF rect, int modifier, QLineF line, qreal additionPadding)
{
    qreal fcwidth = rect.width();
    rect.setLeft(line.length() / 2 * modifier + (padding + additionPadding) * (-modifier));
    rect.setWidth(fcwidth);
    return rect;
}

/**
 * Adjusts bounding rectangle for self realtionship.
 *
 * @param rect rectangle to adjust
 * @param multiply 1 for adjust, -1 for resolving line from bounding rect
 * @return adjusted BoundingRect
 */
QRectF AssociationLine::adjustSelfRect(QRectF rect, int multiply) const
{
    rect.adjust((getTextBoundingBox(secondCardinality).width() + lineBoundingWidth) * -multiply,
                getTextBoundingBox(firstCardinality).height() * 1.5 * -multiply,
                lineBoundingWidth * multiply,
                lineBoundingWidth * multiply);
    return rect;
}

/**
 * Paints self realtionship.
 *
 * @param painter Painter to paint relationship
 */
void AssociationLine::paintSelfRelationship(QPainter *painter)
{
    QRectF bounding = boundingRect();
    bounding = adjustSelfRect(bounding, -1);
    qreal leftPadding = bounding.x() + bounding.width() - selfPadding - specialSelfWidthPadding;
    qreal botPadding = bounding.y() + bounding.height() - selfPadding;

    QVector<QPointF> linePoints = {
        QPointF{leftPadding, bounding.y()},
        QPointF{bounding.x() + bounding.width(), bounding.y()},
        QPointF{bounding.x() + bounding.width(), bounding.y() + bounding.height()},
        QPointF{bounding.x(), bounding.y() + bounding.height()},
        QPointF{bounding.x(), botPadding}
    };
    for (int i = 0; i < linePoints.size() - 1; i++)
        painter->drawLine(linePoints[i], linePoints[i + 1]);

    QRectF firstCardinalityBounding = prepareBoundingBox(getTextBoundingBox(firstCardinality));
    firstCardinalityBounding.translate(QPointF{linePoints[0].x() + firstCardinalityBounding.width() * 0.5 + 10,
                                               linePoints[0].y()});
    painter->drawText(firstCardinalityBounding, firstCardinality);

    QRectF secondCardinalityBounding = getTextBoundingBox(secondCardinality);
    secondCardinalityBounding.translate(
                QPointF{linePoints[linePoints.size() -1].x() - secondCardinalityBounding.width() - 10,
                        linePoints[linePoints.size() -1].y() - secondCardinalityBounding.y()});
    painter->drawText(secondCardinalityBounding, secondCardinality);

    QRectF associationNameRect = prepareBoundingBox(getTextBoundingBox(associationName));
    associationNameRect.translate(QRectF(linePoints[2], linePoints[3]).center());
    painter->drawText(associationNameRect, associationName);
}
