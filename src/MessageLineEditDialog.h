/**
 * @file MessageLineEditDialog.h
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

/**
 * Dialog for edditing all message lines. Allows to change method, switch arrows and remove line.
 */
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

        for (int i = 0; (size_t)i < allMethods.size(); i++)
        {
            if(allMethods[i].getName() == methodCombobox.currentText().toStdString())
                return MethodReference{&(classRef->getMethods()[i])};

        }
        return MethodReference{methodCombobox.currentText().toStdString()};
    }
protected:
    /**
     * Flag that tells if combobox should be shown
     */
    bool showPropertyLayout;
    /**
     * combobox with methods
     */
    QComboBox methodCombobox;
    /**
     * If button pressed, object should be removed
     */
    QPushButton removeButton;
    /**
     * If button pressed, changes shou be accepted
     */
    QPushButton acceptButton;
    /**
     * If button pressed close dialog and do nothing
     */
    QPushButton cancelButton;
    /**
     * If button pressed, switch line arrows if possible
     */
    QPushButton switchButton;
    /**
     * layout of this dialog
     */
    QVBoxLayout mainLayout;
    /**
     * layout for all buttons
     */
    QHBoxLayout buttonLayout;
    /**
     * layout for combobox
     */
    QFormLayout proprtyLayout;
    /**
     * reference on class - unnecesary for method pick
     */
    ClassReference classRef;

    /**
     * Fills combobox data from class
     *
     * @param methodRef Method reference - used if no methods are in class reference.
     * Then add this as item to combobox.
     */
    void fillComboBoxData(MethodReference methodRef);
    /**
     * Set All buttons.
     */
    void setAllButtons();
    /**
     * Set all layouts and set this layout as mainLayout.
     */
    void setAllLayouts();
    /**
     * Fill layout for edditing properties - just combobox with methods.
     */
    void setPropertyLayout();
    /**
     * Fills button layout - add buttons to layout.
     */
    void setButtonLayout();
    /**
     * connect components with slots
     */
    void connectComponents();   
};

#endif // MESSAGELINEEDITDIALOG_H
