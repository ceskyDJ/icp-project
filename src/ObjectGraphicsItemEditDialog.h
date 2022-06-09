/**
 * @file ObjectGraphicsItemEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef OBJECTGRAPHICSITEMEDITDIALOG_H
#define OBJECTGRAPHICSITEMEDITDIALOG_H

#include <QFormLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QAbstractSpinBox>
#include <QPushButton>
#include <QComboBox>
#include "EditDialogBase.h"
#include "ClassDiagram.h"
#include "ClassReference.h"

/**
 * Dialog to edit ObjectGraphicsItem - change reffered class from class diagram.
 */
class ObjectGraphicsItemEditDialog : public EditDialogBase
{
public:
    /**
     * Sets all widgets and layout and fill data.
     *
     * @param objectName current name of object
     * @param className current name of class
     * @param classDiagram source class diagram
     */
    ObjectGraphicsItemEditDialog(QString objectName, QString className, ClassDiagram *classDiagram);

    /**
     * Getter for class name.
     *
     * @return selected class name
     */
    QString getClassName()
    {
        return objectNameLineEdit.text();
    }

    /**
     * Getter for object. Get new name of object.
     *
     * @return new name of object
     */
    QString getObjectName()
    {
        return objectNameLineEdit.text();
    }

    /**
     * Getter for class reference.
     *
     * @return selected class reference
     */
    ClassReference getClassRef()
    {
        std::vector<Class *> allClasses = classDiagram->getClasses();
        for (Class * classItem : allClasses)
        {
            if(classItem->getName() == classNameCombo.currentText().toStdString())
                return ClassReference{classItem};
        }
        return ClassReference{classNameCombo.currentText().toStdString()};
    }
private:
    /**
     * If pressed changes are accepted
     */
    QPushButton acceptButton;
    /**
     * If pressed dialog is closed and nothing else happens
     */
    QPushButton cancelButton;
    /**
     * If pressed, objec should be removed
     */
    QPushButton removeButton;
    /**
     * Line edit to edit object name
     */
    QLineEdit objectNameLineEdit;
    /**
     * Combobox to select clas by name.
     */
    QComboBox classNameCombo;
    /**
     * Layout of this dialog.
     */
    QVBoxLayout mainLayout;
    /**
     * Layout for this dialog
     */
    QHBoxLayout buttonLayout;
    /**
     * Layout for proprty changing items
     */
    QFormLayout propertyLayout;
    /**
     * support to select new classes
     */
    ClassDiagram *classDiagram;


    /**
     * Connect all components
     */
    void connectComponents();
    /**
     * Set all layouts
     */
    void setAllLayouts();
    /**
     * Set all buttons - gives them icon and label.
     */
    void setAllButtons();
    /**
     * Sets button layout.
     */
    void setButtonLayout();
    /**
     * Sets form layout.
     */
    void setPropertyLayout();
private slots:
    /**
     * @brief Slot is used when new name of object is set. Store the new value.
     * 
     * @param newName New name of object
     */
   void objectNameChanged(QString newName);
   /**
    * @brief  Slot is used when new class of object is selecetd. Store the new value.
    * 
    * @param newText new text of clas name
    */
   void newClassSelected(QString newText);
};

#endif // OBJECTGRAPHICSITEMEDITDIALOG_H
