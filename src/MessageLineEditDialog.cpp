/**
 * @file MessageLineEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "MessageLineEditDialog.h"

/**
 * Construct a new Message Line Edit Dialog
 * 
 * @param showPropertyLayout  tells if combobox with method shoul be shown
 * @param classRef class reference
 * @param methodRef  current method reference
 */
MessageLineEditDialog::MessageLineEditDialog(bool showPropertyLayout,
                                             ClassReference classRef, MethodReference methodRef)
    : showPropertyLayout{showPropertyLayout}, classRef{classRef}
{
    setWindowTitle("Edit message dialog");
    setAllButtons();
    setAllLayouts();
    connectComponents();
    fillComboBoxData(methodRef);
    methodCombobox.setCurrentText(QString::fromStdString(methodRef.getReferredMethodName()));
}

/**
 * Fills combobox data from class
 *
 * @param methodRef Method reference - used if no methods are in class reference.
 * Then add this as item to combobox.
 */
void MessageLineEditDialog::fillComboBoxData(MethodReference methodRef)
{
    std::vector<ClassMethod> allMethods = classRef->getMethods();
    for (ClassMethod classMethodItem : allMethods)
        methodCombobox.addItem(QString::fromStdString(classMethodItem.getName()));
    if(allMethods.size() == 0)
        methodCombobox.addItem(QString::fromStdString(methodRef.getReferredMethodName()));
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

}
