/**
 * @file ObjectGraphicsItemEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ObjectGraphicsItemEditDialog.h"

/**
 * Sets all widgets and layout and fill data.
 *
 * @param objectName current name of object
 * @param className current name of class
 * @param classDiagram source class diagram
 */
ObjectGraphicsItemEditDialog::ObjectGraphicsItemEditDialog
    (QString objectName, QString className, ClassDiagram *classDiagram)
    : classDiagram{classDiagram}
{
    setWindowTitle("Edit onbject");
    setAllButtons();
    setAllLayouts();
    connectComponents();

    classNameCombo.setCurrentText(className);
    objectNameLineEdit.setText(objectName);
}


/**
 * Connect all components
 */
void ObjectGraphicsItemEditDialog::connectComponents()
{
    connect(&acceptButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::acceptButtonPressed);
    connect(&cancelButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::cancelButtonPressed);
    connect(&removeButton, &QPushButton::pressed, this, &ObjectGraphicsItemEditDialog::removeButtonPressed);
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
    propertyLayout.addRow("Object name", &objectNameLineEdit);
    std::vector<Class*> classes = classDiagram->getClasses();
    for(Class *classItem : classes)
        classNameCombo.addItem(QString::fromStdString(classItem->getName()));

    propertyLayout.addRow("Class name", &classNameCombo);
}
