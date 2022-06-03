/**
 * @class AssociationLine.h
 * Represents association line in class diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ASSOCIATIONLINE_H
#define ASSOCIATIONLINE_H

#include "Line.h"

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
    QString associationName = "association name";
    QString firstCardinality = "*f";
    QString secondCardinality = "*s";
    qreal padding = 20;


    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    QRectF boundingRect() const;
    QRectF prepareBoundingBox(QRectF rect);
    QRectF locateCardinality(QRectF rect, int modifier, QLineF line, qreal additionPadding = 0);
};

#endif // ASSOCIATIONLINE_H
