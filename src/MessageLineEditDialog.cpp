/**
 * @file MessageLineEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "MessageLineEditDialog.h"

MessageLineEditDialog::MessageLineEditDialog(bool showPropertyLayout)
: showPropertyLayout{showPropertyLayout}
{
    setWindowTitle("Edit message dialog");
    setAllButtons();
    setAllLayouts();
    connectComponents();
    fillComboBoxData();
}

/**
 * Fills combobox data from class
 */
void MessageLineEditDialog::fillComboBoxData()
{
    methodCombobox.addItem("Method 1");
    methodCombobox.addItem("Method 2");
    methodCombobox.addItem("Method 3");
    //methodCombobox.setCurrentText(QString::fromStdString(methodRef.getReferredMethodName()));
}

/**
 * Set All buttons.
 */
void MessageLineEditDialog::setAllButtons()
{
    setAsAcceptButton(&acceptButton, true);
    setAsRemoveButton(&removeButton, false);
    setAsCancelButton(&cancelButton, false);
    setAsSwitchArrowButton(&switchButton, false);
}

/**
 * Set all layouts and set this layout as mainLayout.
 */
void MessageLineEditDialog::setAllLayouts()
{
    if(showPropertyLayout)
    {
        setPropertyLayout();
        mainLayout.addLayout(&proprtyLayout);
    }
    setButtonLayout();
    mainLayout.addLayout(&buttonLayout);
    setLayout(&mainLayout);
}

/**
 * Fill layout for edditing properties - just combobox with methods.
 */
void MessageLineEditDialog::setPropertyLayout()
{
    proprtyLayout.addRow("Method name", &methodCombobox);
}

/**
 * Fills button layout - add buttons to layout.
 */
void MessageLineEditDialog::setButtonLayout()
{
    buttonLayout.addWidget(&removeButton);
    buttonLayout.addWidget(&cancelButton);
    buttonLayout.addWidget(&switchButton);
    if(showPropertyLayout)
        buttonLayout.addWidget(&acceptButton);
}

/**
 * connect components with slots
 */
void MessageLineEditDialog::connectComponents()
{
    connect(&acceptButton, &QPushButton::pressed, this, &MessageLineEditDialog::acceptButtonPressed);
    connect(&removeButton, &QPushButton::pressed, this, &MessageLineEditDialog::removeButtonPressed);
    connect(&switchButton, &QPushButton::pressed, this, &MessageLineEditDialog::swicthArrowButtonPressed);
    connect(&cancelButton, &QPushButton::pressed, this, &MessageLineEditDialog::cancelButtonPressed);

    connect(&methodCombobox, &QComboBox::currentTextChanged, this, &MessageLineEditDialog::methodComboboxChanged);
}

/**
 * If selected text has changed, changes value of this text
 *
 * @param newText new name of method
 */
void MessageLineEditDialog::methodComboboxChanged(QString newText)
{
    (void)newText; //TODO
}
