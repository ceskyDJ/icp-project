/**
 * @file LineWithArrowEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "LineWithArrowEditDialog.h"
#include <QIcon>
#include <QWidget>

/**
 * Constructor for dialog - sets relationshipLine, initializes components
 * sets connections and layout.
 *
 * @param relationship
 */
LineWithArrowEditDialog::LineWithArrowEditDialog(
    LineWithArrow *relationship
): sceneUpdateObservable{relationship->getSceneUpdateObservable()}, relationshipLine{relationship}
{
    initializeComponents();
    setAllButtons();
    connectComponents();
    setMyLayout();
    setTitle();
}

/**
 * Initializes all components.
 */
void LineWithArrowEditDialog::initializeComponents()
{
    switchNodesButton = new QPushButton;
    removeRelationshipButton = new QPushButton;
    cancelButton = new QPushButton;
    mainLayout = new QHBoxLayout;
}

/**
 * Sets layout of the dialog.
 */
void LineWithArrowEditDialog::setMyLayout()
{
    mainLayout->addWidget(removeRelationshipButton);
    mainLayout->addWidget(cancelButton);
    mainLayout->addWidget(switchNodesButton);
    setLayout(mainLayout);
}

/**
 * Sets buttons icon and text.
 *
 * @param icon Icon that will be set to button.
 * @param text Text that will be written in button.
 * @param button Buton that will be set.
 */
void LineWithArrowEditDialog::setOneButton(QIcon icon, QString text, QPushButton *button)
{
    button->setIcon(icon);
    button->setText(text);
}

/**
 * Sets all buttons icon and text.
 */
void LineWithArrowEditDialog::setAllButtons()
{
    switchNodesButton->setDisabled(relationshipLine->isSelfRelationship());
    setOneButton(QIcon{":/closeCross.png"}, "Remove relationship", removeRelationshipButton);
    setOneButton(QIcon{":/switch.png"}, "Swicth arrow", switchNodesButton);
    setOneButton(QIcon{":/cancel.png"}, "Cancel", cancelButton);
    cancelButton->setDefault(true);
}

/**
 * Switches arrow in a relationship.
 */
void LineWithArrowEditDialog::switchArrow()
{
    // Update scene
    relationshipLine->switchNodes();
    relationshipLine->update();

    // Update relationship in class diagram
    std::unordered_map<Line *, Relationship *> *existingRelationships = relationshipLine->getExistingRelationships();
    Relationship *relationship = existingRelationships->find(relationshipLine)->second;
    relationship->swapClasses();

    sceneUpdateObservable->sceneChanged();
    close();
}

/**
 * Removes whole relatinoship and close dialog.
 */
void LineWithArrowEditDialog::removeRelationship()
{
    // Delete from class diagram and existing relationships
    std::unordered_map<Line *, Relationship *> *existingRelationships = relationshipLine->getExistingRelationships();
    ClassDiagram *classDiagram = relationshipLine->getClassDiagram();
    auto relationship = existingRelationships->find(relationshipLine)->second;

    classDiagram->removeRelationship(relationship);
    existingRelationships->erase(relationshipLine);

    // Delete from scene and memory
    relationshipLine->getFromClassNode()->removeConnection(relationshipLine);
    relationshipLine->getToClassNode()->removeConnection(relationshipLine);
    delete relationshipLine;
    close();

    sceneUpdateObservable->sceneChanged();
}

/**
 * Close dialog.
 */
void LineWithArrowEditDialog::cancel()
{
    close();
}

/**
 * Sets window title to FROM_NODE --> TO_NODE
 */
void LineWithArrowEditDialog::setTitle()
{
    setWindowTitle("Relationship: " + relationshipLine->getFromClassNode()->getName() + " ---> " +
                   relationshipLine->getToClassNode()->getName());
}

/**
 * Connects buttons pressed signal with corresponding slot (cancel, switch lines, remove relationship).
 */
void LineWithArrowEditDialog::connectComponents()
{
    connect(cancelButton, &QPushButton::pressed, this, &LineWithArrowEditDialog::cancel);
    connect(switchNodesButton, &QPushButton::pressed, this, &LineWithArrowEditDialog::switchArrow);
    connect(removeRelationshipButton, &QPushButton::pressed, this, &LineWithArrowEditDialog::removeRelationship);
}

