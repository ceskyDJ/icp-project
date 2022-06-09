/**
 * @file classNode.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * Některé funkce byly inspirovány příklady od Petra Peringera
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CLASSNODE_H
#define CLASSNODE_H

#include <QGraphicsItem>
#include <QSet>
#include <QApplication>
#include <QPushButton>
#include "ClassAttribute.h"
#include "Class.h"
#include "ClassAttribute.h"
#include "ClassMethod.h"
#include "Line.h"
#include "SceneUpdateObservable.h"
#include "ClassNodeEmitter.h"

class Line;

/**
 * Implementation of class node - Graphics representation of class.
 */
class ClassNode : public QGraphicsItem
{
public:
    /**
     * Sets a class node entity.
     *
     * @param classEntity Class which is going to be drawn
     * @param existingClasses Classes existing in diagram
     * @param sceneUpdateObservable Observable for notifying about scene changes
     */
    ClassNode(
        Class *classEntity,
        std::unordered_map<std::string, ClassNode *> *existingClasses,
        SceneUpdateObservable *sceneUpdateObservable
    );

    /**
     * Overrided method that returns object bounding rect.
     *
     * @return bounding rect of classnode
     */
    QRectF boundingRect() const override;

    /**
     * Draws a class node with its methods and attribures
     *
     * @param painter to draw
     * @param option options
     * @param widget widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
    /**
     * Sets name of class.
     *
     * @param newName new name of class
     */
    void setName(QString newName)
    {
        classEntity->setName(newName.toStdString());
        update();
    }

    /**
     * Adds an attribute to the class.
     *
     * @param newAtribute Attribute that should be added to the class.
     */
    void addAtribute(ClassAttribute newAtribute)
    {
        classEntity->addAttribute(newAtribute);
        update();
    }

    /**
     * Adds a method to the class.
     *
     * @param newMethod Method that should be added into class.
     */
    void addMethod(ClassMethod newMethod)
    {
        classEntity->addMethod(newMethod);
        update();
    }

    /**
     * Returns a name of the class.
     *
     * @return name of class
     */
    QString getName()
    {
        return QString::fromStdString(classEntity->getName());
    }

    /**
     * Returns an attributes of class.
     *
     * @return attributes of class in std::vector
     */
    std::vector<ClassAttribute> getAtributes()
    {
        return classEntity->getAttributes();
    }

    /**
     * Gets methods of class.
     *
     * @return std::vector of class methods
     */
    std::vector<ClassMethod> getMethods()
    {
        return classEntity->getMethods();
    }

    /**
     * Replaces current attributes in class.
     *
     * @param atributes New attributes that will be set as attributes in class.
     */
    void setAtributes(std::vector<ClassAttribute> attributes)
    {
        classEntity->setAttributes(attributes);
        update();
    }

    /**
     * Replaces class methods.
     *
     * @param methods New methods that will be set as methods in class.
     */
    void setMethods(std::vector<ClassMethod> methods)
    {
        classEntity->setMethods(methods);
        update();
    }

    /**
     * Replaces whole class.
     *
     * @param newEntity new class
     */
    void setEntity(Class *newEntity)
    {
        classEntity = newEntity;
        update();
    }

    /**
     * Returns whole class entity.
     *
     * @return Class
     */
    Class *getClassEntity()
    {
        return classEntity;
    }

    /**
     * Sers a new border Color.
     *
     * @param Color that should be set.
     */
    void setBorderColor(QColor color)
    {
        borderColor = color;
        update();
    }

    /**
     * Adds new connections
     *
     * @param newLine line to connect
     */
    void addLine(Line* newLine);

    /**
     * Removes line form connected list.
     *
     * @param oldLine line to remove
     */
    void removeLine(Line* oldLine);

    /**
     * Returns all connections of class.
     *
     * @return QSet of line * (connections).
     */
    QVector<Line *> getConnections()
    {
        return connectedLines;
    }

    /**
     * Removes a connection from this node.
     *
     * @param line Connection that should be replaced
     */
    void removeConnection(Line *line)
    {
        int index = connectedLines.indexOf(line);
        if(index != -1)
            connectedLines.remove(index);
    }

    /**
     * Object that emits necessary signal.
     */
    ClassNodeEmitter emitter;
    /**
     * Count number of connections with exactly these nodes in
     * parameters and store index of comparedLine into index.
     *
     * @param secondNode one node in connection line
     * @param comparedLine Line that we are looking for.
     * @param index returns order of same connections
     * @return Count of connections with exactly these 2 nodes.
     */
    int getNumberOfConnectionsWithNode(ClassNode *secondNode, const Line *comparedLine, int *index) const;
private:
    /**
     * Pointer to stored class
     */
    Class *classEntity;

    // Dependencies
    /**
     * Classes existing in class diagram mapped to class nodes
     */
    std::unordered_map<std::string, ClassNode *> *existingClasses;
    /**
     * Observable for distributing information about scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;

    QRectF borederRect();
    /**
     * Counts and returns boundigrect of className attribute.
     *
     * @return QRectF Rectangle of classNode.
     */
    QRectF getNameBoundigRect() const;
    /**
     * Counts and returns a whole rect of ClassNode.
     *
     * @return QRectF - whole rect of ClassNode.
     */
    QRectF getWholeRect() const;
    /**
     * Counts and returns a whole rect of ClassNode.
     *
     * @param attributePrintable QStrings of all class attributes
     * @return QRectF - whole rect of ClassNode.
     */
    QRectF getWholeRect(std::vector<QString> &attributePrintable, std::vector<QString> &methodPrintable) const;
    /**
     * indent of line
     */
    const int lineIndent = 5;
    /**
     * Padding of text
     */
    const int Padding = 10;
    /**
     * border color of node
     */
    QColor borderColor = Qt::black;
    /**
     * all connected lined to this classnode
     */
    QVector<Line *> connectedLines;
    /**
     * Is class node moved since last scene change log
     *
     * @par This is used for excluding (double)clicks on class node
     * without its moving
     */
    bool isMoved = false;

    /**
     * Makes and returns all methods of class prepared to print ( +MethodName(params...) ).
     *
     * @return Vector of all class methods prepared to print.
     */
    std::vector<QString> getMethodPrintable(
            std::vector<int> *inheritedIndexes = new std::vector<int>(0)) const;
    /**
     * Makes and returns all attributes of class prepared to print (+AttName:dataType).
     *
     * @return Vector of all class attributes prepared to print.
     */
    std::vector<QString> getAttributePrintable() const;
    /**
     * Joins all method's parameters to printable representation.
     *
     * @param parameters
     * @return string representing method parameter
     */
    QString getMethodParametersPrintable(std::vector<MethodParameter> parameters) const;
    /**
     * Counts a max width of rectangle around the strings in param toCompare and saves it into maxWidth.
     *
     * @param toCompare Vector of strings which should be compared.
     * @param maxWidth A pointer to variable of type int, where will be stored max width.
     */
    void getMaxWidth(std::vector<QString> toCompare, qreal *maxWidth) const;
    /**
     * Sets font to italic or to normal.
     *
     * @param enable true = italic, false = normal
     * @param painter pointer to painter that should be eddited
     */
    void setFontItalic(bool enable, QPainter *painter);
    /**
     *  Handles double click event - shows eddit dialog, then changes entity.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Event handler for mouse release event
     *
     * @param event Event details
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /**
     * Event handler for mouse move event
     *
     * @param event Event details
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * When item is changed then repaint it.
     *
     * @param change GraphicsItemChange
     * @param value const QVariant
     * @return itemchange
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    /**
     * Paints a line again
     */
    void rePaintLines();
    /**
     * Checks if method is inherited from another (by name)
     *
     * @param methodName Method that is being checked.
     * @return if method is inherited than returns true otherwise retrun false;
     */
    bool isMethodInherited(QString methodName) const;
};

#endif // CLASSNODE_H
