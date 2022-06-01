/**
 * @file AssociationLineEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include "AssociationLineEditDialog.h"
#include <QWidget>

/**
 * Class constructor
 * 
 * @param relationship Relationship which should be edited
 */
AssociationLineEditDialog::AssociationLineEditDialog(UndirectedAssociation *relationship): relationship{relationship}
{
    setWindowTitle("Edit association");
    initializeComponents();
    setAllButtons();
    connectComponents();
    setAllLayouts();
    setMainLayout();
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
    associationNameLineEdit->setText(QString::fromStdString(relationship->getName()));
    firstCardinalityLineEdit->setText(QString::fromStdString(relationship->getFirstClassCardinality()));
    secondCardinalityLineEdit->setText(QString::fromStdString(relationship->getSecondClassCardinality()));

    QString firstClassName = QString::fromStdString(relationship->getFirstClass()->getName());
    QString secondClassName = QString::fromStdString(relationship->getSecondClass()->getName());

    lineEditLayout->addRow("Association name", associationNameLineEdit);
    lineEditLayout->addRow("Cardinality (near " + firstClassName + ")", firstCardinalityLineEdit);
    lineEditLayout->addRow("Cardinality (near " + secondClassName + ")", secondCardinalityLineEdit);
}

/**
 * Set the main Layout object.
 */
void AssociationLineEditDialog::setMainLayout()
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
void AssociationLineEditDialog::setAllButtons()
{
    setOneButton(QIcon{":/closeCross.png"}, "Remove relationship", deleteButton);
    setOneButton(QIcon{":/nike.png"}, "Accept changes", acceptButton);
    setOneButton(QIcon{":/cancel.png"}, "Cancel", cancelButton);
    acceptButton->setDefault(true);
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
    relationship->setName(newName.toStdString());
}

/**
 * Sets first cardinality.
 *
 * @param newCardinality new first cardinality
 */
void AssociationLineEditDialog::setFirstCardinality(QString newCardinality)
{
    relationship->setFirstClassCardinality(newCardinality.toStdString());
}

/**
 * Sets second cardinality
 *
 * @param newCardinality new second cardinality
 */
void AssociationLineEditDialog::setSecondCardinality(QString newCardinality)
{
    relationship->setSecondClassCardinality(newCardinality.toStdString());
}
