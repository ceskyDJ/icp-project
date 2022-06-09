/**
 * @file MethodParameterEditWidget.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef METHODPARAMETEREDITWIDGET_H
#define METHODPARAMETEREDITWIDGET_H

#include <QWidget>
#include "MethodParameter.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

/**
 * Allows to edit method parameter.
 */
class MethodParameterEditWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MethodParameterEditWidget::MethodParameterEditWidget Constructs new methodparametereditwidget
     * @param parent parrent widget
     * @param param parameter to edit
     */
    explicit MethodParameterEditWidget(QWidget *parent = nullptr, MethodParameter *param = new MethodParameter("", ""));
    MethodParameter *getParameter()
    {
        return parameterEntity;
    }
signals:
    /**
     * @brief signal is emmited when delete button is pressed 
     * 
     * @param parameterWidget widget to be removed
     */
    void deleteButtonPressed(MethodParameterEditWidget *parameterWidget);

private:
    /**
     * Entity to be edited.
     */
    MethodParameter *parameterEntity;
    /**
     * parameter layout
     */
    QHBoxLayout *parameterLayout;
    /**
     * Line edit to parameter name dit
     */
    QLineEdit *parameterNameLineEdit;
    /**
     * Line edit to edit parameter data type
     */
    QLineEdit *parameterDateTypeLineEdit;
    /**
     * if pressed, method should be deleted
     */
    QPushButton *deleteButton;

    /**
     * @brief MethodParameterEditWidget::initializeComponents Initializes components
     */
    void initializeComponents();
    /**
     * @brief MethodParameterEditWidget::setMyLayout Arranges layout to widget
     */
    void setMyLayout();
    /**
     * @brief MethodParameterEditWidget::fillData Fills data into controls
     */
    void fillData();
    /**
     * @brief MethodParameterEditWidget::setDeleteButton sets delete button
     */
    void setDeleteButton();
private slots:
    /**
     * @brief MethodParameterEditWidget::nameChanged hanldes name changes
     * @param newText new method name
     */
    void nameChanged(QString newText);
    /**
     * @brief MethodParameterEditWidget::dataTypeChanged handles data type changes
     * @param newText new data type name
     */
    void dataTypeChanged(QString newText);
    /**
     * @brief MethodParameterEditWidget::sendDeleteSignalSlot Emits a signal that this should be deleted
     */
    void sendDeleteSignalSlot();
};

#endif // METHODPARAMETEREDITWIDGET_H
