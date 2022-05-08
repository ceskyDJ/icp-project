#include "Line.h"
#include <QLineF>
#include <QPointF>
#include <QPen>
#include <QPainter>
#include <QTextItem>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

class LineText;

Line::Line(ClassNode *fromNode, ClassNode *toNode)
{
    fromClassNode = fromNode;
    toClassNode = toNode;
    setZValue(-1);
    setPen(QPen{Qt::black, 2, Qt::SolidLine});
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

void Line::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    QFontMetricsF metrics{qApp->font()};
    QRectF boundingRect = metrics.boundingRect(name);

    QRectF rect = boundingRect;
    rect.setTopLeft(line.center());
    rect.setSize(boundingRect.size());
    painter->drawText(rect,Qt::AlignLeft ,name, &boundingRect);
    QGraphicsLineItem::paint(painter, option, widget);
}

void Line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    name = QInputDialog::getText(event->widget(), "Edit name", "Enter new Name:", QLineEdit::Normal, name);
    update();
}

Line::~Line()
{
    fromClassNode->removeConnection(this);
    toClassNode->removeConnection(this);
}
