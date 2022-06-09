/**
 * @file ClassEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include "Class.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include "AttributeEditWidget.h"
#include <QScrollArea>
#include "MethodEditWidget.h"
#include "classNode.h"
#include <QMenu>
#include <QAction>
#include <QComboBox>

/**
 * Dialog allows to eddit all data of class entity.
 */
class ClassEditDialog : public QDialog
{
public:
    explicit ClassEditDialog(Class *classEntity);
    Class *getClassEntity()
    {
        return classEntity;
    }
    /**
     * ClassEditDialog::createTitle creates new section in edit dialog - puts a label and add button
     *
     * @param addPushButton button which should be used to add new items
     * @param title for new section
     * @param label label to add push button
     * @return widget representing title
     */
    static QWidget* createTitle(QPushButton *addPushButton, QString title, QString label);

private:
    /**
     * class entity that will be edited
     */
    Class *classEntity;
    /**
     * Line edit to change class name
     */
    QLineEdit *nameTextEdit;
    /**
     * main Layout ow dialog.
     */
    QVBoxLayout *dialogLayout;
    /**
     * All widgets to edit attributes
     */
    std::vector<AttributeEditWidget*> atributeEdits;
    /**
     * Button to add new attribute
     */
    QPushButton *addAtributePushButton;
    /**
     * Button to add new method
     */
    QPushButton *addMethodPushButton;
    /**
     * Garuantee scroll bar
     */
    QScrollArea *attributeScrollArea;
    /**
     * widgets for attribute edits
     */
    QWidget *attributeWidget;
    /**
     * Layout for attributes
     */
    QVBoxLayout *attributeLayout;
    /**
     * Scroll area for methods
     */
    QScrollArea *methodScrollArea;
    /**
     * Widget for method editting
     */
    QWidget *methodWidget;
    /**
     * Layout for method widget
     */
    QVBoxLayout *methodLayout;
    /**
     * Accept button - accept changes
     */
    QPushButton *confirmChangesPushButton;
    /**
     * Reject changes button
     */
    QPushButton *rejectChangesPushButton;
    /**
     * After click on this button classnode should be removed
     */
    QPushButton *deleteNodePushButton;
    /**
     * Widget for all buttons
     */
    QWidget *buttonWidget;
    /**
     * contextmenu
     */
    QMenu *contextMenu;
    /**
     * Comobobox to selectd all class types
     */
    QComboBox *classTypeComboBox;

    /**
     * Initializes all components.
     */
    void initializeComponents();
    /**
     * Arranges widgets to layout.
     */
    void setMainLayout();
    /**
     * @brief Make all unnesesary connections
     */
    void makeConnections();
    /**
     * @brief ClassEditDialog::addNewAttribute Adds new attribute to scroll area
     * @param newAttribute new attribute to add
     */
    void addNewAttribute(ClassAttribute *newAttribute);
    /**
     * @brief ClassEditDialog::addNewMethod Adds new method to scroll area.
     * @param newMethod method to add
     */
    void addNewMethod(ClassMethod *newMethod);
    /**
     * @brief sets new scroll areas
     */
    void setScrollAreas();
    /**
     * @brief set scroll area - creates widget with layout in scroll area
     * @param areaWidget widget where will be controls added
     * @param areaLayout layout for widgets
     * @param scrollArea scroll area
     */
    void setScrollArea(QWidget *areaWidget, QVBoxLayout *areaLayout, QScrollArea *scrollArea);
    void setButtons();
    /**
     * @brief sets combobox properies
     */
    void setComboBox();
    /**
     * @brief fills data into dialog controls
     */
    void fillData();

private slots:
    /**
     * deletes attribute
     *
     * @param toDelete attribute that should be deleted
     */
    void deleteAttribute(AttributeEditWidget *toDelete);
    /**
     * @brief Slot which will be called after emit singal of add button
     */
    void addNewAttributeSlot();
    /**
     * ClassEditDialog::deleteMethod deletes a method
     *
     * @param toDelete method that should be deleted
     */
    void deleteMethod(MethodEditWidget *toDelete);
    /**
     * Slot which will be called after emit singal of add button
     */
    void addNewMethodSlot();
    /**
     * @brief slot when name changes
     * @param newName new name of class
     */
    void onNameChanged(QString newName);
    /**
     * @brief confirmation button slot
     */
    void onConfirmChangesPressed();
    /**
     * @brief button slot to reject changes
     */
    void onRejectChangesPressed();
    /**
     * @brief slot for changig type
     * @param newType of class
     */
    void onClassTypeChanged(QString newType);
};

#endif // CLASSEDITDIALOG_H
