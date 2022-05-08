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
    Line(ClassNode *fromNode, ClassNode *toNode);
    void drawLine();
    ~Line();
private:
    QString name = "relName";
    ClassNode *fromClassNode;
    ClassNode *toClassNode;
    QPointF getCenterPos(ClassNode *node);
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node);
    QLineF getShortestLine(ClassNode *first, ClassNode *second);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/);

};
#endif // LINE_H
