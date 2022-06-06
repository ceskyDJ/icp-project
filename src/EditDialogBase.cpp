/**
 * @file EditDialogBase.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "EditDialogBase.h"

/**
 * Set one Button - gives it icon and label + set default and autodefault.
 */
void EditDialogBase::setOneButton(QPushButton *button ,QIcon icon, QString text, bool setDefault)
{
    button->setIcon(icon);
    button->setText(text);
    button->setAutoDefault(setDefault);
    button->setDefault(setDefault);
}

/**
 * Sets button as it looks likde remove button.
 *
 * @param button button to edit
 * @param setDefault to set default and autoDefault to this value
 */
void EditDialogBase::setAsRemoveButton(QPushButton *button, bool setDefault)
{
    setOneButton(button, QIcon{":/closeCross.png"}, "Remove object", setDefault);
}

/**
 * Sets button as it looks likde accept button.
 *
 * @param button button to edit
 * @param setDefault to set default and autoDefault to this value
 */
void EditDialogBase::setAsAcceptButton(QPushButton *button, bool setDefault)
{
    setOneButton(button, QIcon{":/nike.png"}, "Accept", setDefault);
}

/**
 * Sets button as it looks likde cancel button.
 *
 * @param button button to edit
 * @param setDefault to set default and autoDefault to this value
 */
void EditDialogBase::setAsCancelButton(QPushButton *button, bool setDefault)
{
    setOneButton(button, QIcon{":/cancel.png"}, "Cancel", setDefault);
}


/**
 * Slot handles when accept button is pressed. Close dialog with QDialog::Accepted.
 */
void EditDialogBase::acceptButtonPressed()
{
    accept();
}

/**
 * Slot handles when cancel button is pressed. Close dialog with QDialog::Rejected.
 */
void EditDialogBase::cancelButtonPressed()
{
    reject();
}

/**
 * Slot handles when cancel button is pressed. Close dialog with EditDialogBase::remove
 */
void EditDialogBase::removeButtonPressed()
{
    done(remove);
}

/**
 * Slot handles when switchArrow button is pressed. Close dialog with EditDialogBase::switchArrows
 */
void EditDialogBase::swicthArrowButtonPressed()
{
    done(switchArrows);
}

/**
 * Sets button as it looks likde switchArrow button.
 *
 * @param button button to edit
 * @param setDefault to set default and autoDefault to this value
 */
void EditDialogBase::setAsSwitchArrowButton(QPushButton *button, bool setDefault)
{
    setOneButton(button, QIcon{":/switch.png"}, "Switch arrow", setDefault);
}
