/**
 * @file MethodEditWidget.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef METHODEDITWIDGET_H
#define METHODEDITWIDGET_H

#include <QWidget>
#include "ClassMethod.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "MethodParameterEditWidget.h"

/**
 * Allows to edit method - name and paramateres.
 */
class MethodEditWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MethodEditWidget::MethodEditWidget creates new instance of method widget
     * @param parent parrent of widget
     * @param method method that shlould be eddited
     */
    explicit MethodEditWidget(QWidget *parent = nullptr, ClassMethod *method = nullptr);
    ClassMethod *getMethod()
    {
        //get class methods
        std::vector<MethodParameter> newParameters;
        for (int i = 0; i < parameterLayout->count(); ++i)
        {
            QWidget *widget = parameterLayout->itemAt(i)->widget();
            MethodParameterEditWidget *aWidget = dynamic_cast<MethodParameterEditWidget *>(widget);
            newParameters.push_back(*(aWidget->getParameter()));
        }
        methodEntity->setParameters(newParameters);
        return methodEntity;
    }
signals:
    /**
     * @brief Emits this signal when delte button was pressed
     * 
     * @param methodWidget widget to delete
     */
    void deleteButtonPressed(MethodEditWidget *methodWidget);

private:
    /**
     * Method that will be treted
     */
    ClassMethod *methodEntity;
    /**
     * LayoutForMethods
     */
    QGridLayout *methodLayOut;
    /**
     * layout of this eidget
     */
    QVBoxLayout *mainLayOut;
    /**
     * Combobox with acces modifiers
     */
    QComboBox *accessModifierComboBox;
    /**
     * Combobox with method types
     */
    QComboBox *methodTypeComboBox;
    /**
     * Line edit to edit name of method
     */
    QLineEdit *methodNameLineEdit;
    /**
     * Line edit to edit return datatype of method return value
     */
    QLineEdit *methodReturnDataTypeLineEdit;
    /**
     * Iff pressed this button, this method should be removed
     */
    QPushButton *deleteButton;
    /**
     * scroll area for parameters 
     */
    QScrollArea *parameterScrollArea;
    /**
     * Widget for parameter layout
     */
    QWidget *parameterWidget;
    /**
     * Layout for paramters edit widgets
     */
    QVBoxLayout *parameterLayout;
    /**
     * If pressed, new parameter for methdo should be added
     */
    QPushButton *addParameterPushButton;

    /**
     * @brief MethodEditWidget::initializeComponents initializes components
     */
    void initializeComponents();
    /**
     * @brief MethodEditWidget::setComboBox set combobox source data
     */
    void setComboBox();
    /**
     * @brief MethodEditWidget::setMyLayout arranges widgets to layout
     */
    void setMyLayout();
    /**
     * @brief MethodEditWidget::fillData fills data into widgets
     */
    void fillData();
    /**
     * @brief MethodEditWidget::setDeleteButton Sets delete button icon
     */
    void setDeleteButton();
    /**
     * @brief MethodEditWidget::makeConnections Makes unnesecary connections
     */
    void makeConnections();
    /**
     * @brief MethodEditWidget::setScrollArea sets scroll area
     */
    void setScrollArea();
    /**
     * @brief MethodEditWidget::setAddButton Setss add button for method params
     */
    void setAddButton();
    /**
     * @brief MethodEditWidget::addNewParameter Adds a new parameter
     * @param newParameter new parameter that should be added
     */
    void addNewParameter(MethodParameter *newParameter);
private slots:
    /**
     * @brief MethodEditWidget::accsesModifierChanged Slot that handle acces modifier changed + edits a method acces modifier
     * @param newText new acces modifier (serialized)
     */
    void accsesModifierChanged(QString newText);
    /**
     * @brief MethodEditWidget::typeChanged Handles change of method type
     * @param newText New method type
     */
    void typeChanged(QString newText);
    /**
     * @brief MethodEditWidget::nameChanged Hanldes change of name
     * @param newText new name of method
     */
    void nameChanged(QString newText);
    /**
     * @brief MethodEditWidget::returnDataTypeChanged Handle change of return data type
     * @param newText new return data type
     */
    void returnDataTypeChanged(QString newText);
    /**
     * @brief MethodEditWidget::sendDeleteSignalSlot emit signal, that this maethod should me removed
     */
    void sendDeleteSignalSlot();
    /**
     * @brief MethodEditWidget::addNewParameterSlot Slot to add new parameter
     */
    void addNewParameterSlot();
    /**
     * @brief MethodEditWidget::deleteParameter slot to handle deletion of parameter
     * @param paramEdit parameter to remove
     */
    void deleteParameter(MethodParameterEditWidget *paramEdit);
};

#endif // METHODEDITWIDGET_H
