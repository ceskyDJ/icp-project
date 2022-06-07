/**
 * @class EditDialogBase
 * Base functionality for inherited edit dialogs
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef EDITDIALOGBASE_H
#define EDITDIALOGBASE_H

#include <QDialog>
#include <QPushButton>
#include <QIcon>

class EditDialogBase : public QDialog
{
public:
    /**
     * Result value of dialog if remove button was pressed
     */
    const static int remove = -1;

    /**
     * Result value of dialog if switch arrow button was pressed
     */
    const static int switchArrows = -2;
protected:

    /**
     * Set one Button - gives it icon and label + set default and autodefault.
     */
    void setOneButton(QPushButton *button, QIcon icon, QString text, bool setDefault);

    /**
     * Sets button as it looks likde remove button.
     *
     * @param button button to edit
     * @param setDefault to set default and autoDefault to this value
     */
    void setAsRemoveButton(QPushButton *button, bool setDefault);

    /**
     * Sets button as it looks likde accept button.
     *
     * @param button button to edit
     * @param setDefault to set default and autoDefault to this value
     */
    void setAsAcceptButton(QPushButton *button, bool setDefault);

    /**
     * Sets button as it looks likde cancel button.
     *
     * @param button button to edit
     * @param setDefault to set default and autoDefault to this value
     */
    void setAsCancelButton(QPushButton *button, bool setDefault);

    /**
     * Sets button as it looks likde cancel button.
     *
     * @param button button to edit
     * @param setDefault to set default and autoDefault to this value
     */
    void setAsSwitchArrowButton(QPushButton *button, bool setDefault);
protected slots:
    /**
     * Slot handles when accept button is pressed. Close dialog with QDialog::Accepted.
     */
    void acceptButtonPressed();

    /**
     * Slot handles when cancel button is pressed. Close dialog with QDialog::Rejected.
     */
    void cancelButtonPressed();

    /**
     * Slot handles when cancel button is pressed. Close dialog with EditDialogBase::remove
     */
    void removeButtonPressed();

    /**
     * Slot handles when switchArrow button is pressed. Close dialog with EditDialogBase::switchArrows
     */
    void swicthArrowButtonPressed();
};

#endif // EDITDIALOGBASE_H
