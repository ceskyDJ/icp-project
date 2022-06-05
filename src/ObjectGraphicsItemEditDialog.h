/**
 * @class ObjectGraphicsItemEditDialog
 * Dialog to edit ObjectGraphicsItem
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

class ObjectGraphicsItemEditDialog : public EditDialogBase
{
public:
    ObjectGraphicsItemEditDialog(QString objectName, QString className);

    /**
     * Getter for class name.
     *
     * @return selected class name
     */
    QString getClassName()
    {
        return className;
    }

    /**
     * Getter for object. Get new name of object.
     *
     * @return new name of object
     */
    QString getObjectName()
    {
        return objectName;
    }
private:
    QString objectName;
    QString className;
    QPushButton acceptButton;
    QPushButton cancelButton;
    QPushButton removeButton;
    QLineEdit objectNameLineEdit;
    QComboBox classNameCombo;
    QVBoxLayout mainLayout;
    QHBoxLayout buttonLayout;
    QFormLayout propertyLayout;


    void connectComponents();
    void setAllLayouts();
    void setAllButtons();
    void setButtonLayout();
    void setPropertyLayout();
private slots:
   void objectNameChanged(QString newName);
   void newClassSelected(QString newText);
};

#endif // OBJECTGRAPHICSITEMEDITDIALOG_H
