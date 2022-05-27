/**
 * @file AssociationLineEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "AssociationLineEditDialog.h"
#include <QWidget>

/**
 * @brief Construct a new Association Line.
 * 
 * @param line Line which should be edited.
 */
AssociationLineEditDialog::AssociationLineEditDialog(AssociationLine *line)
{
    copyLine(relationship, line);
    setWindowTitle("Edit association");
    initializeComponents();
    setAllButtons();
    connectComponents();
    setAllLayouts();
    setMainLayout();
}

/**
 * Copy AsssociationLine name and cardinalities.
 * 
 * @param copy This will be a copy of lineToCopy.
 * @param lineToCopy This line will be copied.
 */
void AssociationLineEditDialog::copyLine(AssociationLine *copy, AssociationLine *lineToCopy)
{
    copy->setName(lineToCopy->getName());
    copy->setFirstCardinality(lineToCopy->getFirstCardinality());
    copy->setSecondCardinality(lineToCopy->getSecondCardinality());
    copy->setFromClassNode(lineToCopy->getFromClassNode());
    copy->setToClassNode(lineToCopy->getToClassNode());
}

/**
 * Initializes components
 */
void AssociationLineEditDialog::initializeComponents()
{
    acceptButton = new QPushButton;
    cancelButton = new QPushButton;
    deleteButton = new QPushButton;
    associationNameLineEdit = new QLineEdit;
    firstCardinalityLineEdit = new QLineEdit;
    secondCardinalityLineEdit = new QLineEdit;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    lineEditLayout = new QFormLayout;
}

/**
 * Connects components.
 */
void AssociationLineEditDialog::connectComponents()
{
    connect(cancelButton, &QPushButton::pressed, this, &AssociationLineEditDialog::cancel);
    connect(acceptButton, &QPushButton::pressed, this, &AssociationLineEditDialog::acceptChanges);
    connect(deleteButton, &QPushButton::pressed, this, &AssociationLineEditDialog::removeAssociation);

    connect(associationNameLineEdit, &QLineEdit::textChanged, this, &AssociationLineEditDialog::setName);
    connect(firstCardinalityLineEdit, &QLineEdit::textChanged, this, &AssociationLineEditDialog::setFirstCardinality);
    connect(secondCardinalityLineEdit, &QLineEdit::textChanged, this, &AssociationLineEditDialog::setSecondCardinality);
}

/**
 * Set the All Layouts object.
 */
void AssociationLineEditDialog::setAllLayouts()
{
    setFormLayout();
    setButtonLayout();
    setMainLayout();
}

/**
 * Set the Button Layout object.
 */
void AssociationLineEditDialog::setButtonLayout()
{
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButton);
}

/**
 * Set the Form Layout object.
 */
void AssociationLineEditDialog::setFormLayout()
{
    associationNameLineEdit->setText(relationship->getName());
    firstCardinalityLineEdit->setText(relationship->getFirstCardinality());
    secondCardinalityLineEdit->setText(relationship->getSecondCardinality());

    lineEditLayout->addRow("Association name", associationNameLineEdit);
    lineEditLayout->addRow("Cardinality (near " + relationship->getFromClassNode()->getName() + ")",
                           firstCardinalityLineEdit);
    lineEditLayout->addRow("Cardinality (near " + relationship->getToClassNode()->getName() + ")",
                           secondCardinalityLineEdit);
}

/**
 * Set the main Layout object.
 */
void AssociationLineEditDialog::setMainLayout()
{
    mainLayout->addLayout(lineEditLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

/**
 * Set the All Buttons object.
 */
void AssociationLineEditDialog::setAllButtons()
{
    setOneButton(QIcon{":/closeCross.png"}, "Remove relationship", deleteButton);
    setOneButton(QIcon{":/nike.png"}, "Accept changes", acceptButton);
    setOneButton(QIcon{":/cancel.png"}, "Cancel", cancelButton);
}

/**
 * Set the One Button's icon and text 
 * 
 * @param icon icon of button 
 * @param text Text that should be displayed on button.
 * @param button Pointer to the treated button.
 */
void AssociationLineEditDialog::setOneButton(QIcon icon, QString text, QPushButton *button)
{
    button->setIcon(icon);
    button->setText(text);
}

/**
 * Cancel slot closes dialog.
 */
void AssociationLineEditDialog::cancel()
{
    close();
}

/**
 * Closes dialog and sets accept flag to true.
 */
void AssociationLineEditDialog::acceptChanges()
{
    acceptSelected = true;
    close();
}

/**
 * Sets remove flag to true and closes dialog.
 */
void AssociationLineEditDialog::removeAssociation()
{
    removeSelected = true;
    close();
}

/**
 * Sets a new name of association.
 *
 * @param newName new association name
 */
void AssociationLineEditDialog::setName(QString newName)
{
    relationship->setName(newName);
}

/**
 * Sets first cardinality.
 *
 * @param newCardinality new first cardinality
 */
void AssociationLineEditDialog::setFirstCardinality(QString newCardinality)
{
    relationship->setFirstCardinality(newCardinality);
}

/**
 * Sets second cardinality
 *
 * @param newCardinality new second cardinality
 */
void AssociationLineEditDialog::setSecondCardinality(QString newCardinality)
{
    relationship->setSecondCardinality(newCardinality);
}
