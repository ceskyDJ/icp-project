/**
 * @file Line.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>
#include <QPointF>
#include <QPen>
#include <QPainterPath>
#include <QPainter>
#include "classNode.h"
#include "ClassDiagram.h"
#include "SceneUpdateObservable.h"

class ClassNode;
class LineText;

/**
 * Base class for all lines. Provides basic methods for drawing to all relationships.
 */
class Line: public QGraphicsLineItem {
public:
    /**
     * Line constructor
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
    Line(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    ): existingRelationships{existingRelationships}, classDiagram{classDiagram},
            sceneUpdateObservable{sceneUpdateObservable} {
        pen = QPen{Qt::black, 2, Qt::SolidLine};
        fromClassNode = nullptr;
        toClassNode = nullptr;
        selfRealtionshipFlag = false;
        specialSelfWidthPadding = 0;
    };

    /**
     * @brief Destroy the Line object
     * 
     */
    ~Line();
    /**
     * @brief Line::drawLine draws a line
     */
    void drawLine();
    /**
     * Initializes line - from and to + initializes pen.
     * @param fromNode source node
     * @param toNode target node
     */
    void initialize(ClassNode *fromNode, ClassNode *toNode, bool selfRealtionship);

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

    /**
     * Getter for existing relationships
     *
     * @return Pointer to existing relationships
     */
    std::unordered_map<Line *, Relationship *> *getExistingRelationships()
    {
        return existingRelationships;
    }

    /**
     * Getter for class diagram
     *
     * @return Pointer to class diagram
     */
    ClassDiagram *getClassDiagram()
    {
        return classDiagram;
    }

    /**
     * Getter for scene update observable
     *
     * @return Pointer to observable for distributing information about scene changes
     */
    SceneUpdateObservable *getSceneUpdateObservable()
    {
        return sceneUpdateObservable;
    }

    /**
     * Return realtionship self flag
     *
     * @return true if line is self-relationship
     * @return false if line is NOT self-relationship
     */
    bool isSelfRelationship()
    {
        return selfRealtionshipFlag;
    }

    /**
     * Switches nodes in line. 'From node' is set as 'to node' and 'to Node' is set as 'from node'.
     */
    void switchNodes();
    /**
     * Override method which returns bounding rect of line.
     *
     * @return QRectF A rectnagle around classNode.
     */
    QRectF boundingRect() const;
protected:
    // Dependencies
    /**
     * Pointer to map of existing relationships and their lines
     */
    std::unordered_map<Line *, Relationship *> *existingRelationships;
    /**
     * Pointer to class diagram
     */
    ClassDiagram *classDiagram;
    /**
     * Observable for distributing information about scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;

    /**
     * padding of line in self relationship
     */
    qreal selfPadding = 50;
    /**
     * Special additional padding in self relationship
     */
    qreal specialSelfWidthPadding;
    /**
     * pen used to draw
     */
    QPen pen;
    /**
     * Classnode which is first point
     */
    ClassNode *fromClassNode;
    /**
     * Classnode that is like second point
     */
    ClassNode *toClassNode;
    /**
     * Width of line, where is possible to invoke double click event
     */
    qreal lineBoundingWidth = 10;
    /**
     * Tells if relationship is self relationship
     */
    bool selfRealtionshipFlag;

    /**
     * Gets Center position of widget.
     *
     * @param node node, where should be counted a middle point
     * @return point where is middle of node
     */
    QPointF getCenterPos(ClassNode *node) const;
    /**
     * Counts point which intersects line border and line from one node to second node.
     *
     * @param connectingLine line between center of nodes
     * @param node Node of which will be count an intersection
     * @return Intersection point
     */
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node) const;
    /**
     * Counts shortest line connected between 2 nodes
     *
     * @param first First selected node (source)
     * @param second Second selected node (target)
     * @return Shotest line between points
     */
    QLineF getShortestLine(ClassNode *first, ClassNode *second) const;
    /**
     * Draws a line.
     *
     * @param painter Painter allows to draw a line
     * @param option const QStyleOptionGraphicsItem
     * @param widget QWidget
     */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    /**
     * Sets a shape of line - it will be same line but with bigger width
     *
     * @return QPainterPath - path of line but wider
     */
    QPainterPath shape() const;
    /**
     * Returns a line that is parallel with parallelLine but starts in another p1.
     *
     * @param lineToPerpend Line that will be copied.
     * @param startPoint new start point
     * @return Parallel line with startPoint as p1
     */
    QLineF getParallelLine(QLineF parallelLine, QPointF startPoint) const;
    /**
     * Returns bounding rect of text with current font.
     *
     * @param text - bounding rectangle around this text
     * @return bounding rectangle around parameter
     */
    QRectF getTextBoundingBox(QString text) const;
    /**
     * Returns a shape for self relationship.
     *
     * @return QPainterPath - shape for self relationship
     */
    QPainterPath selfRealtionshipShape() const;
    /**
     * Adjusts bounding rect for self relationship
     *
     * @param rect rect to adjust
     * @param multiply 1 for bounding rect, -1 for drawing
     */
    virtual QRectF adjustSelfRect(QRectF rect, int multiply) const;
    /**
     * Adjusts bounding by specific requirements.
     *
     * @param pointer to rect to adjust
     */
    virtual void adjustBounding(QRectF *rect) const;
    /**
     * Method that paints self relationship (virtual) - need to ne implemented at child.
     */
    virtual void paintSelfRelationship(QPainter *painter);
    /**
     * Move Points in rectangle according to number of connections (one should't lie on other ones)
     *
     * @param firstPoint center point in first node
     * @param secondPoint center point in second node
     * @param first classnode (where firstPoint is it's middle point in scene)
     * @param second classnode (where secondPoint is it's middle point in scene)
     */
    void movePointsByConnectionCount(QPointF *firstPoint, QPointF *secondPoint,
                                     ClassNode *firstNode, ClassNode *secondNode) const;
    /**
     * Find intersectionPoints of line and rect and creates line between them.
     *
     * @param rect rectanlge that should be intersected
     * @param line line that should be intersected
     */
    QLineF qrectIntersectsLine(QRectF rect, QLineF line) const;
    /**
     * Move point in line according to the index by index in connection count.
     * EXAMLPLE connectionCount is 2, so there are 2 * 2 parts and line is from top middle point to bot middle point:
     * new point is on position (line_Lenght / 2*2) [4 parts] * (index * 2 + 1) [to reach middle of part if separated to 2 parts]
     * for index 0 there will be selected part1 which is middle of the first half
     * for index 1 there will be selected part3 which is middle of the second half
     *          |----|  <--node beg
     * node --> |----|  <--part1
     *          |----|  <--part2
     *          |----|  <--part3
     *          |----|  <--node end
     *
     * @param line line where to move
     * @param point new value is stored here
     * @param connectionCount count of all connections with same nodes
     * @param index index of line in connections
     */
    void movePointInLine(QLineF line, QPointF *point,int connectionCount, int index) const;
    /**
     * Sets endpoints by their x position, to be same in both sides
     *
     * @param line line that could be reversed
     */
    void setEndPoints(QLineF *line) const;
};
#endif // LINE_H
