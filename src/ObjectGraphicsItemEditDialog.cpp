/**
 * @file ObjectGraphicsItemEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ObjectGraphicsItemEditDialog.h"

ObjectGraphicsItemEditDialog::ObjectGraphicsItemEditDialog(QString objectName, QString className)
: objectName{objectName}, className{className}
{
    setWindowTitle("Edit onbject");
    setAllButtons();
    setAllLayouts();
    connectComponents();
}


/**
 * Connect all components
 */
void ObjectGraphicsItemEditDialog::connectComponents()
{
    connect(&acceptButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::acceptButtonPressed);
    connect(&cancelButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::cancelButtonPressed);
    connect(&removeButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::removeButtonPressed);

    connect(&objectNameLineEdit, &QLineEdit::textChanged, this, &ObjectGraphicsItemEditDialog::objectNameChanged);
    connect(&classNameCombo, &QComboBox::currentTextChanged, this, &ObjectGraphicsItemEditDialog::newClassSelected);
}

/**
 * Set all layouts
 */
void ObjectGraphicsItemEditDialog::setAllLayouts()
{
    setButtonLayout();
    setPropertyLayout();
    mainLayout.addLayout(&propertyLayout);
    mainLayout.addLayout(&buttonLayout);
    setLayout(&mainLayout);
}

/**
 * Set all buttons - gives them icon and label.
 */
void ObjectGraphicsItemEditDialog::setAllButtons()
{
    setAsAcceptButton(&acceptButton, true);
    setAsRemoveButton(&removeButton, false);
    setAsCancelButton(&cancelButton, false);
}

/**
 * Sets button layout.
 */
void ObjectGraphicsItemEditDialog::setButtonLayout()
{
    buttonLayout.addWidget(&removeButton);
    buttonLayout.addWidget(&cancelButton);
    buttonLayout.addWidget(&acceptButton);
}

/**
 * Sets form layout.
 */
void ObjectGraphicsItemEditDialog::setPropertyLayout()
{
    objectNameLineEdit.setText(objectName);
    propertyLayout.addRow("Object name", &objectNameLineEdit);
    classNameCombo.addItem("Class 1");
    classNameCombo.addItem("Class 2");
    classNameCombo.addItem("Class 3");
    propertyLayout.addRow("Class name", &classNameCombo);
}

/**
 * Slot handles when name of object is changed - rewrite currentName.
 *
 * @param newName new name of object.
 */
void ObjectGraphicsItemEditDialog::objectNameChanged(QString newName)
{
    objectName = newName;
}

/**
 * Slot handles when a new text in combobox is selected
 *
 * @param newText new selected text
 */
void ObjectGraphicsItemEditDialog::newClassSelected(QString newText)
{
    className = newText;
}
