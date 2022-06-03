/**
 * @class classNode
 * Implementation of class node.
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
#include "ClassNodeEmmitor.h"

class Line;
class ClassNodeEmmitor;

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
     * @brief ClassNode::addLine adds new connections
     * @param newLine line to connect
     */
    void addLine(Line* newLine);

    /**
     * @brief ClassNode::removeLine removes line form connected list
     * @param oldLine line to remove
     */
    void removeLine(Line* oldLine);

    /**
     * Returns all connections of class.
     *
     * @return QSet of line * (connections).
     */
    QSet<Line *> getConnections()
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
        connectedLines.remove(line);
    }

    ClassNodeEmmitor* emitor;
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
    QRectF getNameBoundigRect() const;
    QRectF getWholeRect() const;
    QRectF getWholeRect(std::vector<QString> &attributePrintable, std::vector<QString> &methodPrintable) const;
    const int lineIndent = 5;
    const int Padding = 10;
    QColor borderColor = Qt::black;
    QSet<Line *> connectedLines;
    /**
     * Is class node moved since last scene change log
     *
     * @par This is used for excluding (double)clicks on class node
     * without its moving
     */
    bool isMoved = false;

    std::vector<QString> getMethodPrintable(
            std::vector<int> *inheritedIndexes = new std::vector<int>(0)) const;
    std::vector<QString> getAttributePrintable() const;
    QString getMethodParametersPrintable(std::vector<MethodParameter> parameters) const;
    void getMaxWidth(std::vector<QString> toCompare, int *maxWidth) const;
    void setFontItalic(bool enable, QPainter *painter);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void rePaintLines();
    bool isMethodInherited(QString methodName) const;
};

#endif // CLASSNODE_H
