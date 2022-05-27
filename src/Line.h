/**
 * @class Line
 * General line - others are abstract.
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

class ClassNode;
class LineText;

class Line : public QGraphicsLineItem {
public:
    /**
     * Line constructor
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     */
    Line(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram
    ): existingRelationships{existingRelationships}, classDiagram{classDiagram} {};

    ~Line();

    void drawLine();

    void initialize(ClassNode *fromNode, ClassNode *toNode);

    /**
     * Returns a classNode that is pointed to, in relationship.
     *
     * @return second class node
     */
    ClassNode *getToClassNode() {
        return toClassNode;
    }

    /**
     * Returns a classNode that is pointed from, in relationship.
     *
     * @return second class node
     */
    ClassNode *getFromClassNode() {
        return fromClassNode;
    }

    /**
     * Sets a classNode that is pointed to, in relationship.
     *
     * @return second class node
     */
    void setToClassNode(ClassNode *newToNode) {
        toClassNode = newToNode;
    }

    /**
     * Sets a classNode that is pointed from, in relationship.
     *
     * @return second class node
     */
    void setFromClassNode(ClassNode *newFromNode) {
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

    void switchNodes();
protected:
    QPen pen{Qt::black, 2, Qt::SolidLine};
    ClassNode *fromClassNode;
    ClassNode *toClassNode;
    qreal lineBoundingWidth = 10;
    /**
     * Pointer to map of existing relationships and their lines
     */
    std::unordered_map<Line *, Relationship *> *existingRelationships;
    /**
     * Pointer to class diagram
     */
    ClassDiagram *classDiagram;


    QPointF getCenterPos(ClassNode *node) const;
    QPointF getIntersectPoint(QLineF connectingLine, ClassNode *node) const;
    QLineF getShortestLine(ClassNode *first, ClassNode *second) const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QPainterPath shape() const;
    QLineF getParallelLine(QLineF parallelLine, QPointF startPoint) const;
};
#endif // LINE_H
