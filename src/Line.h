#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>
#include "classNode.h"
#include <QPointF>

class ClassNode;

class Line : public QGraphicsLineItem
{
public:
    Line(ClassNode *fromClassNode, ClassNode *toClassNode);
    void drawLine();

private:
    ClassNode *fromClassNode;
    ClassNode *toClassNode;
    QPointF getCenterPos(ClassNode *node);
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node);
    QLineF getShortestLine(ClassNode *first, ClassNode *second);
};
#endif // LINE_H
