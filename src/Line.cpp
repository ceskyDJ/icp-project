#include "Line.h"
#include <QLineF>
#include <QPointF>

Line::Line(ClassNode *fromNode, ClassNode *toNode)
{
    fromClassNode = fromNode;
    toClassNode = toNode;
    setZValue(-1);

    drawLine();
}


void Line::drawLine()
{
    setLine(getShortestLine(fromClassNode, toClassNode));
}

QPointF Line::getCenterPos(ClassNode *node)
{
    QRectF rect = node->boundingRect();
    qreal a = rect.x();
    (void)a;
    int xMid = rect.x() + rect.width()/2;
    int yMid = rect.y() + rect.height()/2;
    return QPointF{node->x() + xMid , node->y()+yMid};
}

QLineF Line::getShortestLine(ClassNode *first, ClassNode *second)
{
    QPointF firstPoint = getCenterPos(first);
    QPointF secondPoint = getCenterPos(second);

    QPointF firstIntersectionPoint;
    QPointF secondIntersectionPoint;

    QLineF line = QLineF{firstPoint, secondPoint};

    firstIntersectionPoint = getIntersectPoint(line, first);
    secondIntersectionPoint = getIntersectPoint(line, second);

    return QLineF{firstIntersectionPoint, secondIntersectionPoint};
}

QPointF Line::getIntersectPoint(QLineF connectingLine, ClassNode *node)
{
    QRectF rect = node->boundingRect();
    qreal xPos = node->x() + rect.x();
    qreal yPos = node->y() + rect.y();
    std::vector<QPointF> connectPoints{QPointF{xPos, yPos},
                                       QPointF{ xPos + rect.width(), yPos},
                                       QPointF{ xPos + rect.width(), yPos + rect.height()},
                                       QPointF{ xPos, yPos + rect.height()},
                                       QPointF{ xPos, yPos}
                                      };
    QPointF toReturn = QPointF{-1000, -1000};
    for(int i = 0; (size_t)i < connectPoints.size() - 1; ++i)
    {
        if(connectingLine.intersects(QLineF{connectPoints[i], connectPoints[i + 1]}, &toReturn) == QLineF::BoundedIntersection)
            return toReturn;
    }
    return toReturn;
}
