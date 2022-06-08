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
    void drawArrow(QPainter *painter) const override;
    void drawTexts(QPainter *painter, QLineF line) const override;
    QString relationshipName = "relationship name";
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/) override;
};

#endif // DIRECTEDASSOCIATIONLINE_H
