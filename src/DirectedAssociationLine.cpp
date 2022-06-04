/**
 * @file DirectedAssociationLine.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "DirectedAssociationLine.h"
#include <QPolygonF>
#include <QLinearGradient>
#include <QPainterPath>
#include "DirectedAssociationLineEditDialog.h"

/**
 * Set arrow height and width.
 *
 * @param existingRelationships Pointer to map of existing relationships and their lines
 * @param classDiagram Pointer to class diagram
 * @param sceneUpdateObservable Observable for distributing information about scene changes
 */
DirectedAssociationLine::DirectedAssociationLine(
    std::unordered_map<Line *, Relationship *> *existingRelationships,
    ClassDiagram *classDiagram,
    SceneUpdateObservable *sceneUpdateObservable
): LineWithArrow{existingRelationships, classDiagram, sceneUpdateObservable}
{
    arrowHeight = 20;
    arrowWidth = 20;
}

/**
 * Draws an arrow adequate to the directed association line.
 *
 * @param painter to draw line
 */
void DirectedAssociationLine::drawArrow(QPainter *painter) const
{
    QVector<QPointF> points = {
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2},
        QPointF{arrowWidth / 2, 0},
        QPointF{-arrowWidth / 2 + 1, -arrowHeight / 2},
        QPointF{-arrowWidth / 2 + 1, arrowHeight / 2}
    };

    QPolygonF arrowPolygon{points};
    QPainterPath arrowPath;
    QLinearGradient arrowGradient{};
    arrowGradient.setColorAt(0,Qt::black);
    arrowGradient.setColorAt(1,Qt::black);
    arrowPath.addPolygon(arrowPolygon);
    painter->setBrush(arrowGradient);
    painter->drawPath(arrowPath);
}

/**
 * Draws relationship name in the middle of the line
 *
 * @param painter painter to draw a text
 * @param line currnet line
 */
void DirectedAssociationLine::drawTexts(QPainter *painter, QLineF line) const
{
    QRectF textRect = getTextBoundingBox(relationshipName);
    textRect.setY(-textRect.height() * 1.5);
    textRect.setX(-textRect.width() * 0.5);

    qreal angle = (line.angle() < 90 || line.angle() > 270)? -line.angle(): - line.angle() + 180;
    painter->translate(line.center());
    painter->rotate(angle);
    painter->drawText(textRect, relationshipName);
    painter->rotate(-angle);
    painter->translate(-line.center());
}

/**
 * Opens dialog for edditing line attributes and then handles with return value.
 */
void DirectedAssociationLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    DirectedAssociationLineEditDialog dialog{this};
    if (dialog.exec() == QDialog::Accepted && relationshipName != dialog.getNewName()) {
        // Update scene
        relationshipName = dialog.getNewName();
        update();

        // Update class diagram
        auto directedAssociation = dynamic_cast<DirectedAssociation *>(existingRelationships->find(this)->second);
        directedAssociation->setName(relationshipName.toStdString());

        sceneUpdateObservable->sceneChanged();
    }
    else if (dialog.switchArrowsPressed()) {
        // Update scene
        std::swap(fromClassNode, toClassNode);
        update();

        // Update class diagram
        auto directedAssociation = dynamic_cast<DirectedAssociation *>(existingRelationships->find(this)->second);
        directedAssociation->swapClasses();

        sceneUpdateObservable->sceneChanged();
    }
    else if(dialog.removePressed()) {
        // Delete from class diagram
        Relationship *relationship = existingRelationships->find(this)->second;
        classDiagram->removeRelationship(relationship);

        // Delete from existing relationships
        existingRelationships->erase(this);

        // Delete from scene and memory
        delete this;

        sceneUpdateObservable->sceneChanged();
    }
}
