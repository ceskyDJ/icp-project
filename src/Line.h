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

class ClassNode;
class LineText;

class Line : public QGraphicsLineItem
{
public:
    Line();
    void drawLine();
    ~Line();
    void initialize(ClassNode *fromNode, ClassNode *toNode);
protected:
    QString name = "relName";
    ClassNode *fromClassNode;
    ClassNode *toClassNode;
    QPointF getCenterPos(ClassNode *node) const;
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node) const;
    QLineF getShortestLine(ClassNode *first, ClassNode *second) const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/);

};
#endif // LINE_H
