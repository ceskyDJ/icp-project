/**
 * @file ActorGraphicsItemEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ActorGraphicsItemEditDialog.h"

/**
 * Initializes components, store name of actor and set it as text of line edit.
 *
 * @param name name of actor
 */
ActorGraphicsItemEditDialog::ActorGraphicsItemEditDialog(QString name) : name{name}
{
    setWindowTitle("Edit actor");
    nameLineEdit.setText(name);
    setAllButtons();
    setMainLayout();
    connectComponents();
}

/**
 * Slot changes current name to new name.
 *
 * @param newName new name
 */
void ActorGraphicsItemEditDialog::nameChanged(QString newName)
{
    name = newName;
}


/**
 * Connect all components/
 */
void ActorGraphicsItemEditDialog::connectComponents()
{
    connect(&nameLineEdit, &QLineEdit::textChanged, this, &ActorGraphicsItemEditDialog::nameChanged);
    connect(&acceptButton, &QPushButton::pressed, this, &ActorGraphicsItemEditDialog::acceptButtonPressed);
    connect(&cancelButton, &QPushButton::pressed, this, &ActorGraphicsItemEditDialog::cancelButtonPressed);
    connect(&removeButton, &QPushButton::pressed, this, &ActorGraphicsItemEditDialog::removeButtonPressed);
}

/**
 * Set button layout - places buttons in layout.
 */
void ActorGraphicsItemEditDialog::setButtonLayout()
{
    buttonLayout.addWidget(&removeButton);
    buttonLayout.addWidget(&cancelButton);
    buttonLayout.addWidget(&acceptButton);
}

/**
 * Place QLineDialog into property layout.
 */
void ActorGraphicsItemEditDialog::setPropertyLayout()
{
    propertyLayout.addRow("Name", &nameLineEdit);
}

/**
 * Places layouts into main layout and sets mainLayout as this layout
 */
void ActorGraphicsItemEditDialog::setMainLayout()
{
    setPropertyLayout();
    setButtonLayout();
    mainLayout.addLayout(&propertyLayout);
    mainLayout.addLayout(&buttonLayout);
    setLayout(&mainLayout);
}

/**
 * Set all buttons - add it icon and text
 */
void ActorGraphicsItemEditDialog::setAllButtons()
{
    setAsAcceptButton(&acceptButton, true);
    setAsCancelButton(&cancelButton, false);
    setAsRemoveButton(&removeButton, false);
}
