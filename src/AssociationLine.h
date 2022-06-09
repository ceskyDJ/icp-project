/**
 * @file AssociationLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ASSOCIATIONLINE_H
#define ASSOCIATIONLINE_H

#include "Line.h"

/**
 * Represents association line in class diagram.
 */
class AssociationLine : public Line
{
public:
    using Line::Line;

    /**
     * Get the Name of assotiation relationship.
     * 
     * @return QString name
     */
    QString getName()
    {
        return associationName;
    }

    /**
     * Get the First Cardinality of assotiation relationship.
     * 
     * @return QString first cardinality
     */
    QString getFirstCardinality()
    {
        return firstCardinality;
    }

    /**
     * Get the Second Cardinality of assotiation relationship.
     * 
     * @return QString second cardinality
     */
    QString getSecondCardinality()
    {
        return secondCardinality;
    }

    /**
     * Set the Name of assotiation relationship.
     * 
     * @param name new name
     */
    void setName(QString name)
    {
        associationName = name;
    }

    /**
     * Set the First Cardinality of assotiation relationship.
     * 
     * @param cardinality new cardinality
     */
    void setFirstCardinality(QString cardinality)
    {
        firstCardinality = cardinality;
    }

    /**
     * Set the Second Cardinality of assotiation relationship.
     * 
     * @param cardinality new cardinality
     */
    void setSecondCardinality(QString cardinality)
    {
        secondCardinality = cardinality;
    }
protected:
    /**
     * name of relationship
     */
    QString associationName = "association name";
    /**
     * first cardinality in association
     */
    QString firstCardinality = "*";
    /**
     * second cardinality in association
     */
    QString secondCardinality = "*";
    /**
     * padding for text (on sides)
     */
    qreal padding = 20;

    /**
     * Handles a double click event - shows input dialog to rename relationship
     * 
     * @param event recieved event
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Draws an Assotiation line with cardianlities and name of the relationship.
     *
     * @param painter to draw
     * @param option options
     * @param widget widget
     */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    /**
     * Adjusts regular boundingbox
     *
     * @param rect that should be adjusted
     */
    void adjustBounding(QRectF *rect) const;
    /**
     * Places Bounding box up on the line.
     *
     * @param rect QRectF that will be placed over a line.
     * @return transformed rectangle
     */
    QRectF prepareBoundingBox(QRectF rect);
    /**
     * Places cardinality to the end or start line.
     *
     * @param rect Rectangle that should be modified.
     * @param modifier -1 for start of line, 1 for end of line.
     * @param line line of relationship
     * @return modified QRectF
     */
    QRectF locateCardinality(QRectF rect, int modifier, QLineF line, qreal additionPadding = 0);
    /**
     * Adjusts bounding rectangle for self realtionship.
     *
     * @param rect rectangle to adjust
     * @param multiply 1 for adjust, -1 for resolving line from bounding rect
     * @return adjusted BoundingRect
     */
    QRectF adjustSelfRect(QRectF rect, int multiply) const;
    /**
     * Paints self realtionship.
     *
     * @param painter Painter to paint relationship
     */
    void paintSelfRelationship(QPainter *painter);
};

#endif // ASSOCIATIONLINE_H
