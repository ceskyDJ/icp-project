/**
 * @file Line.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "Line.h"
#include <QLineF>
#include <QPointF>
#include <QPen>
#include <QPainter>
#include <QTextItem>
#include <QInputDialog>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>

class LineText;

/**
 * @brief Line::initialize initializes line - from and to + pen
 * @param fromNode source node
 * @param toNode target node
 */
void Line::initialize(ClassNode *fromNode, ClassNode *toNode, bool selfRealtionship)
{
    selfRealtionshipFlag = selfRealtionship;
    fromClassNode = fromNode;
    toClassNode = toNode;
    setZValue(-1);
    setPen(QPen{Qt::black, 2, Qt::SolidLine});
    drawLine();
}

/**
 * @brief Line::drawLine draws a line
 */
void Line::drawLine()
{
    setLine(getShortestLine(fromClassNode, toClassNode));
}

/**
 * @brief Line::getCenterPos Gets Center position of widget.
 * @param node node, where should be counted a middle point
 * @return point where is middle of node
 */
QPointF Line::getCenterPos(ClassNode *node) const
{
    QRectF rect = node->boundingRect();
    int xMid = rect.x() + rect.width()/2;
    int yMid = rect.y() + rect.height()/2;
    return QPointF{node->x() + xMid , node->y()+yMid};
}

/**
 * @brief Line::getShortestLine Counts shortest line connected between 2 nodes
 * @param first First selected node (source)
 * @param second Second selected node (target)
 * @return Shotest line between points
 */
QLineF Line::getShortestLine(ClassNode *first, ClassNode *second) const
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

/**
 * @brief Line::getIntersectPoint Counts point which intersects line border and line from one node to second node.
 * @param connectingLine line between center of nodes
 * @param node Node of which will be count an intersection
 * @return Intersection point
 */
QPointF Line::getIntersectPoint(QLineF connectingLine, ClassNode *node) const
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

/**
 * @brief Line::paint Draws a line
 * @param painter Painter allows to draw a line
 * @param option const QStyleOptionGraphicsItem
 * @param widget QWidget
 */
void Line::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(pen);
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    painter->drawLine(line);
}

/**
 * @brief Line::~Line destructs line - disconnect it first
 */
Line::~Line()
{
    if(fromClassNode != nullptr)
        fromClassNode->removeConnection(this);
    if (toClassNode != nullptr)
        toClassNode->removeConnection(this);
}

void Line::switchNodes()
{
    std::swap(fromClassNode, toClassNode);
}

/**
 * Sets a shape of line - it will be same line but with bigger width
 *
 * @return QPainterPath - path of line but wider
 */
QPainterPath Line::shape() const
{
    if (selfRealtionshipFlag)
    {
        return selfRealtionshipShape();
    }
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    QLineF first_perpendicularLine = line.normalVector();
    QLineF second_perpendicularLine = first_perpendicularLine;
    first_perpendicularLine.setLength(lineBoundingWidth);
    second_perpendicularLine.setAngle(first_perpendicularLine.angle() + 180);
    second_perpendicularLine.setLength(lineBoundingWidth);


    QLineF parallelLine1 = getParallelLine(line, first_perpendicularLine.p2());
    QLineF parallelLine2 = getParallelLine(line, second_perpendicularLine.p2());

    QVector<QPointF> points = {
        parallelLine1.p1(),
        parallelLine1.p2(),
        parallelLine2.p2(),
        parallelLine2.p1(),
        parallelLine1.p1()
    };

    QPolygonF pathPolygon{points};
    QPainterPath newPath{};
    newPath.addPolygon(pathPolygon);
    return newPath;
}

/**
 * Returns a shape for self relationship.
 *
 * @return QPainterPath - shape for self relationship
 */
QPainterPath Line::selfRealtionshipShape() const
{
    QRectF bounding = boundingRect();
    bounding = adjustSelfRect(bounding, -1);
    qreal leftPadding = bounding.x() + bounding.width() - selfPadding;
    qreal botPadding = bounding.y() + bounding.height() - selfPadding;

    QVector<QPointF> linePoints = {
        QPointF{leftPadding, bounding.y() + lineBoundingWidth},
        QPointF{leftPadding, bounding.y() - lineBoundingWidth},
        QPointF{bounding.x() + bounding.width() + lineBoundingWidth, bounding.y() - lineBoundingWidth},
        QPointF{bounding.x() + bounding.width() + lineBoundingWidth, bounding.y() + bounding.height() + lineBoundingWidth},
        QPointF{bounding.x() - lineBoundingWidth, bounding.y() + bounding.height() + lineBoundingWidth},
        QPointF{bounding.x() - lineBoundingWidth, botPadding},
        QPointF{bounding.x() + lineBoundingWidth, botPadding},
        QPointF{bounding.x() + lineBoundingWidth, bounding.y() + bounding.height() - lineBoundingWidth },
        QPointF{bounding.x() + bounding.width() - lineBoundingWidth, bounding.y() + bounding.height() - lineBoundingWidth },
        QPointF{bounding.x() + bounding.width() - lineBoundingWidth, bounding.y() + lineBoundingWidth },
        QPointF{leftPadding, bounding.y() + lineBoundingWidth}
    };

    QPainterPath path;
    QPolygonF temp{linePoints};
    path.addPolygon(temp);
    return path;
}

/**
 * Returns a line that is parallel with parallelLine but starts in another p1.
 *
 * @param lineToPerpend Line that will be copied.
 * @param startPoint new start point
 * @return Parallel line with startPoint as p1
 */
QLineF Line::getParallelLine(QLineF parallelLine, QPointF startPoint) const
{
    QLineF newLine{};
    newLine.setP1(startPoint);
    newLine.setAngle(parallelLine.angle());
    newLine.setLength(parallelLine.length());
    return newLine;
}


/**
 * Returns bounding rect of text with current font.
 *
 * @param text - bounding rectangle around this text
 * @return bounding rectangle around parameter
 */
QRectF Line::getTextBoundingBox(QString text) const
{
    text = (text.count() == 0)? "I":text;
    static const QFontMetricsF metrics{qApp->font()};
    return metrics.boundingRect(text);
}

/**
 * Adjusts bounding rect for self relationship
 *
 * @param rect rect to adjust
 * @param multyply 1 for bounding rect, -1 for drawing
 */
QRectF Line::adjustSelfRect(QRectF rect, int multyply) const
{
    rect.adjust((lineBoundingWidth * 2) * -multyply, lineBoundingWidth * 2 * -multyply,
                (lineBoundingWidth * 2) * multyply, lineBoundingWidth * 2 * multyply);
    return rect;
}

/**
 * Override method which returns bounding rect of line.
 *
 * @return QRectF A rectnagle around classNode.
 */
QRectF Line::boundingRect() const
{
    if (selfRealtionshipFlag)
    {
        QRectF nodeBounding = fromClassNode->boundingRect();
        QPointF threeQuater{nodeBounding.x() + nodeBounding.width() / 2, nodeBounding.y() + nodeBounding.height() / 2};
        threeQuater.setX(threeQuater.x() + nodeBounding.width() * 0.25);
        threeQuater.setY(threeQuater.y() + nodeBounding.height() * 0.25);
        nodeBounding.setTopLeft(threeQuater);
        nodeBounding.adjust(0,0, selfPadding, selfPadding);
        nodeBounding = adjustSelfRect(nodeBounding, 1);
        nodeBounding.translate(fromClassNode->pos());
        return nodeBounding;
    }
    QLineF line = getShortestLine(fromClassNode, toClassNode);
    QPointF leftTop = QPointF{ std::min(line.p1().x(), line.p2().x()), std::min(line.p1().y(), line.p2().y())};
    QPointF rightBot = QPointF{ std::max(line.p1().x(), line.p2().x()), std::max(line.p1().y(), line.p2().y())};
    QRectF bounding = QRectF{leftTop,rightBot};

    adjustBounding(&bounding);
    return bounding;
}

void Line::adjustBounding(QRectF *rect) const
{
    rect->adjust(0,0,0,0);
}
