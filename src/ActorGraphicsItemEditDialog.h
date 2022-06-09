/**
 * @file ActorGraphicsItemEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTORGRAPHICSITEMEDITDIALOG_H
#define ACTORGRAPHICSITEMEDITDIALOG_H

#include "EditDialogBase.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

/**
 * Dialog for edditing ActorGraphicsItem
 */
class ActorGraphicsItemEditDialog : public EditDialogBase
{
public:
    ActorGraphicsItemEditDialog(QString name);

    /**
     * Returns actor name from user.
     *
     * @return actor name from user
     */
    QString getActorName()
    {
        return name;
    }
private:
    /**
     * Name of actor 
     */
    QString name;
    /**
     * @brief Accept button - closes dialog with QDialog::Accepted
     * 
     */
    QPushButton acceptButton;
    /**
     * @brief Cancel button  - closes dialog with QDialog::rejected
     * 
     */
    QPushButton cancelButton;
    /**
     * @brief Remove button - closes dialog with return code 'remove' sotred in editDialogBase
     * 
     */
    QPushButton removeButton;
    /**
     * @brief LineEdit widget for editting name of actor
     * 
     */
    QLineEdit nameLineEdit;
    /**
     * @brief this->laout - main layout where is everything
     * 
     */
    QVBoxLayout mainLayout;
    /**
     * @brief Layout for all buttons
     * 
     */
    QHBoxLayout buttonLayout;
    /**
     * @brief Layout for line edit.
     * 
     */
    QFormLayout propertyLayout;

    /**
     * Set all buttons - add it icon and text
     */
    void setAllButtons();
    /**
     * Set button layout - places buttons in layout.
     */
    void setButtonLayout();
    /**
     * Place QLineDialog into property layout.
     */
    void setPropertyLayout();
    /**
     * Places layouts into main layout and sets mainLayout as this layout
     */
    void setMainLayout();
    /**
     * Connect all components/
     */
    void connectComponents();
private slots:
    /**
     * Slot changes current name to new name.
     *
     * @param newName new name
     */
    void nameChanged(QString newName);
};

#endif // ACTORGRAPHICSITEMEDITDIALOG_H
