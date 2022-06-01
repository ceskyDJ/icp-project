/**
 * @file DirectedAssociationLineEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "DirectedAssociationLineEditDialog.h"
#include <QWidget>

/**
 * @brief Construct a new Association Line edit dialog.
 *
 * @param line Line which should be edited.
 */
DirectedAssociationLineEditDialog::DirectedAssociationLineEditDialog(DirectedAssociationLine *line)
{
    relationshipLine = new DirectedAssociationLine(
        line->getExistingRelationships(),
        line->getClassDiagram(),
        line->getSceneUpdateObservable()
    );
    relationshipLine->initialize(line->getFromClassNode(), line->getToClassNode(), line->isSelfRelationship());
    setWindowTitle("Edit relationship");
    initializeComponents();
    setAllButtons();
    connectComponents();
    setAllLayouts();
    setMainLayout();
    nameLineEdit->setText(line->getName());
}

/**
 * Initializes components
 */
void DirectedAssociationLineEditDialog::initializeComponents()
{
    acceptButton = new QPushButton;
    cancelButton = new QPushButton;
    removeButton = new QPushButton;
    switchArrowsButton = new QPushButton;
    nameLineEdit = new QLineEdit;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    lineEditLayout = new QFormLayout;
}

/**
 * Connects components.
 */
void DirectedAssociationLineEditDialog::connectComponents()
{
    connect(cancelButton, &QPushButton::pressed, this, &DirectedAssociationLineEditDialog::cancel);
    connect(acceptButton, &QPushButton::pressed, this, &DirectedAssociationLineEditDialog::acceptChanges);
    connect(removeButton, &QPushButton::pressed, this, &DirectedAssociationLineEditDialog::removeLine);
    connect(switchArrowsButton, &QPushButton::pressed, this, &DirectedAssociationLineEditDialog::switchNodes);
    connect(nameLineEdit, &QLineEdit::textChanged, this, &DirectedAssociationLineEditDialog::setName);
}

/**
 * Set the All Layouts object.
 */
void DirectedAssociationLineEditDialog::setAllLayouts()
{
    setFormLayout();
    setButtonLayout();
    setMainLayout();
}

/**
 * Set the Button Layout object.
 */
void DirectedAssociationLineEditDialog::setButtonLayout()
{
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(switchArrowsButton);
    buttonLayout->addWidget(acceptButton);
    acceptButton->setAutoDefault(true);
    acceptButton->setDefault(true);
}

/**
 * Set the Form Layout object.
 */
void DirectedAssociationLineEditDialog::setFormLayout()
{
    nameLineEdit->setText(relationshipLine->getName());
    lineEditLayout->addRow("Relationship name", nameLineEdit);
}

/**
 * Set the main Layout object.
 */
void DirectedAssociationLineEditDialog::setMainLayout()
{
    QWidget *lineEditWidget = new QWidget();
    lineEditWidget->setLayout(lineEditLayout);
    QWidget *buttonWidget = new QWidget();
    buttonWidget->setLayout(buttonLayout);

    mainLayout->addWidget(lineEditWidget);
    mainLayout->addWidget(buttonWidget);
    setLayout(mainLayout);
}

/**
 * Set the All Buttons object.
 */
void DirectedAssociationLineEditDialog::setAllButtons()
{
    setOneButton(QIcon{":/closeCross.png"}, "Remove relationship", removeButton);
    setOneButton(QIcon{":/nike.png"}, "Accept changes", acceptButton);
    setOneButton(QIcon{":/cancel.png"}, "Cancel", cancelButton);
    setOneButton(QIcon{":/switch.png"}, "Switch arrow", switchArrowsButton);
    acceptButton->setAutoDefault(true);
    acceptButton->setDefault(true);
    removeButton->setAutoDefault(false);
    removeButton->setDefault(false);
    cancelButton->setAutoDefault(false);
    cancelButton->setDefault(false);
    switchArrowsButton->setAutoDefault(false);
    switchArrowsButton->setDefault(false);

}

/**
 * Set the One Button's icon and text
 *
 * @param icon icon of button
 * @param text Text that should be displayed on button.
 * @param button Pointer to the treated button.
 */
void DirectedAssociationLineEditDialog::setOneButton(QIcon icon, QString text, QPushButton *button)
{
    button->setIcon(icon);
    button->setText(text);
}

/**
 * Cancel slot closes dialog.
 */
void DirectedAssociationLineEditDialog::cancel()
{
    close();
}

/**
 * Closes dialog and sets accept flag.
 */
void DirectedAssociationLineEditDialog::acceptChanges()
{
    accept();
}

/**
 * Sets remove flag to true and closes dialog.
 */
void DirectedAssociationLineEditDialog::removeLine()
{
    removeSelected = true;
    close();
}

/**
 * Sets switch arrow flag to true and ends dialog.
 */
void DirectedAssociationLineEditDialog::switchNodes()
{
    switchNodesSelected = true;
    close();
}

/**
 * Sets a new name of relationship.
 *
 * @param newName new relationship name
 */
void DirectedAssociationLineEditDialog::setName(QString newName)
{
    relationshipLine->setName(newName);
}

/**
 * Destructs this object - it has to delete direct association pointer
 */
DirectedAssociationLineEditDialog::~DirectedAssociationLineEditDialog()
{
    delete relationshipLine;
}
