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
    MessageLineEditDialog(bool showPropertyLayout, ClassReference classRef, MethodReference methodRef);

    /**
     * Getter for new method reference.
     *
     * @return new method reference
     */
    MethodReference getMethodReference()
    {
        std::vector<ClassMethod> allMethods = classRef->getMethods();
        allMethods = classRef->getMethods();

        for (int i = 0; (size_t)i < allMethods.size(); i++)
        {
            if(allMethods[i].getName() == methodCombobox.currentText().toStdString())
                return MethodReference{&(classRef->getMethods()[i])};

        }
        return MethodReference{methodCombobox.currentText().toStdString()};
    }
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
    ClassReference classRef;

    void fillComboBoxData();
    void setAllButtons();
    void setAllLayouts();
    void setPropertyLayout();
    void setButtonLayout();
    void connectComponents();   
};

#endif // MESSAGELINEEDITDIALOG_H
