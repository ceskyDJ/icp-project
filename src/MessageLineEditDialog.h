/**
 * @class MessageLineEditDialog
 * Dialog for edditing message lines.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef MESSAGELINEEDITDIALOG_H
#define MESSAGELINEEDITDIALOG_H

#include "EditDialogBase.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include "ClassReference.h"
#include "MethodReference.h"

class MessageLineEditDialog : public EditDialogBase
{
public:
    MessageLineEditDialog(bool showPropertyLayout);
protected:
    bool showPropertyLayout;
    QComboBox methodCombobox;
    QPushButton removeButton;
    QPushButton acceptButton;
    QPushButton cancelButton;
    QPushButton switchButton;
    QVBoxLayout mainLayout;
    QHBoxLayout buttonLayout;
    QFormLayout proprtyLayout;


    void fillComboBoxData();
    void setAllButtons();
    void setAllLayouts();
    void setPropertyLayout();
    void setButtonLayout();
    void connectComponents();
protected slots:
    void methodComboboxChanged(QString newText);
};

#endif // MESSAGELINEEDITDIALOG_H
