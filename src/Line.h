/**
 * @class Line
 * General line - others are abstract.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>
#include "classNode.h"
#include <QPointF>
#include <QPen>
#include <QPainterPath>

class ClassNode;
class LineText;

class Line : public QGraphicsLineItem
{
public:
    Line();
    void drawLine();
    ~Line();
    void initialize(ClassNode *fromNode, ClassNode *toNode);

    /**
     * Returns a classNode that is pointed to, in relationship.
     *
     * @return second class node
     */
    ClassNode *getToClassNode()
    {
        return toClassNode;
    }

    /**
     * Returns a classNode that is pointed from, in relationship.
     *
     * @return second class node
     */
    ClassNode *getFromClassNode()
    {
        return fromClassNode;
    }

    /**
     * Sets a classNode that is pointed to, in relationship.
     *
     * @return second class node
     */
    void setToClassNode(ClassNode *newToNode)
    {
        toClassNode = newToNode;
    }

    /**
     * Sets a classNode that is pointed from, in relationship.
     *
     * @return second class node
     */
    void setFromClassNode(ClassNode *newFromNode)
    {
        fromClassNode = newFromNode;
    }

    void switchNodes();
protected:
    QPen pen{Qt::black, 2, Qt::SolidLine};
    ClassNode *fromClassNode;
    ClassNode *toClassNode;
    qreal lineBoundingWidth = 10;


    QPointF getCenterPos(ClassNode *node) const;
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node) const;
    QLineF getShortestLine(ClassNode *first, ClassNode *second) const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QPainterPath shape() const;
    QLineF getParallelLine(QLineF parallelLine, QPointF startPoint) const;
};
#endif // LINE_H
