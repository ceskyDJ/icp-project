/**
 * @class LineWithArrowEditDialog
 * Dialog which allow to revers line directory or remove reltaionship.
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
LineWithArrowEditDialog::LineWithArrowEditDialog(LineWithArrow *relationship)
{
    relationshipLine = relationship;
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
    setOneButton(QIcon{":/closeCross.png"}, "Remove relationship", removeRelationshipButton);
    setOneButton(QIcon{":/switch.png"}, "Swicth arrow", switchNodesButton);
    setOneButton(QIcon{":/cancel.png"}, "Cancel", cancelButton);
}

/**
 * Switches arrow in a relationship.
 */
void LineWithArrowEditDialog::switchArrow()
{
    relationshipLine->switchNodes();
    setTitle();
}

/**
 * Removes whole relatinoship and close dialog.
 */
void LineWithArrowEditDialog::removeRelationship()
{
    relationshipLine->getFromClassNode()->removeConnection(relationshipLine);
    relationshipLine->getToClassNode()->removeConnection(relationshipLine);
    delete relationshipLine;
    close();
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
