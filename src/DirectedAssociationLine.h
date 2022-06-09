/**
 * @file DirectedAssociationLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef DIRECTEDASSOCIATIONLINE_H
#define DIRECTEDASSOCIATIONLINE_H
#include "LineWithArrow.h"

/**
 * Allows to draw a directed association line in class diagram.
 */
class DirectedAssociationLine : public LineWithArrow
{
public:
    /**
     * Set arrow height and width.
     *
     * @param existingRelationships Pointer to map of existing relationships and their lines
     * @param classDiagram Pointer to class diagram
     * @param sceneUpdateObservable Observable for distributing information about scene changes
     */
    DirectedAssociationLine(
        std::unordered_map<Line *, Relationship *> *existingRelationships,
        ClassDiagram *classDiagram,
        SceneUpdateObservable *sceneUpdateObservable
    );

    /**
     * Getter for relationship line.
     *
     * @return relationship name
     */
    QString getName()
    {
        return relationshipName;
    }

    /**
     * Setter for relationship name.
     *
     * @param newName that will be set as relationship name.
     */
    void setName(QString &newName)
    {
        relationshipName = newName;
    }
protected:
    /**
     * Draws an arrow adequate to the directed association line.
     *
     * @param painter to draw line
     */
    void drawArrow(QPainter *painter) const override;
    /**
     * Draws relationship name in the middle of the line
     *
     * @param painter painter to draw a text
     * @param line currnet line
     */
    void drawTexts(QPainter *painter, QLineF line) const override;

    /**
     * Name of relationship
     */
    QString relationshipName = "relationship name";
    /**
     * Opens dialog for edditing line attributes and then handles with return value.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/) override;
};

#endif // DIRECTEDASSOCIATIONLINE_H
