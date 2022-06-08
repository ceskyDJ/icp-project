/**
 * @file MethodParameterEditWidget.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "MethodParameterEditWidget.h"
#include <QLabel>

/**
 * @brief MethodParameterEditWidget::MethodParameterEditWidget Constructs new methodparametereditwidget
 * @param parent parrent widget
 * @param param parameter to edit
 */
MethodParameterEditWidget::MethodParameterEditWidget(QWidget *parent, MethodParameter *param)
    : QWidget{parent}
{
    parameterEntity = param;
    initializeComponents();
    setDeleteButton();
    setMyLayout();
    fillData();
    connect(parameterNameLineEdit, &QLineEdit::textChanged,
            this, &MethodParameterEditWidget::nameChanged);
    connect(parameterDateTypeLineEdit, &QLineEdit::textChanged,
            this, &MethodParameterEditWidget::dataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &MethodParameterEditWidget::sendDeleteSignalSlot);
}

/**
 * @brief MethodParameterEditWidget::initializeComponents Initializes components
 */
void MethodParameterEditWidget::initializeComponents()
{
    parameterLayout = new QHBoxLayout;
    parameterNameLineEdit = new QLineEdit;
    parameterDateTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

/**
 * @brief MethodParameterEditWidget::nameChanged hanldes name changes
 * @param newText new method name
 */
void MethodParameterEditWidget::nameChanged(QString newText)
{
    parameterEntity->setName(newText.toStdString());
}

/**
 * @brief MethodParameterEditWidget::dataTypeChanged handles data type changes
 * @param newText new data type name
 */
void MethodParameterEditWidget::dataTypeChanged(QString newText)
{
    parameterEntity->setDataType(newText.toStdString());
}

/**
 * @brief MethodParameterEditWidget::setMyLayout Arranges layout to widget
 */
void MethodParameterEditWidget::setMyLayout()
{
    parameterLayout->addWidget(new QLabel("Název"));
    parameterLayout->addWidget(parameterNameLineEdit);
    parameterLayout->addWidget(new QLabel("Datový typ"));
    parameterLayout->addWidget(parameterDateTypeLineEdit);
    parameterLayout->addWidget(deleteButton);
    setLayout(parameterLayout);
}

/**
 * @brief MethodParameterEditWidget::fillData Fills data into controls
 */
void MethodParameterEditWidget::fillData()
{
    parameterNameLineEdit->setText(QString::fromStdString(parameterEntity->getName()));
    parameterDateTypeLineEdit->setText(QString::fromStdString(parameterEntity->getDataType()));
}

/**
 * @brief MethodParameterEditWidget::setDeleteButton sets delete button
 */
void MethodParameterEditWidget::setDeleteButton()
{
    deleteButton->setIcon(QIcon(":/closeCross.png"));
}

/**
 * @brief MethodParameterEditWidget::sendDeleteSignalSlot Emits a signal that this should be deleted
 */
void MethodParameterEditWidget::sendDeleteSignalSlot()
{
    emit deleteButtonPressed(this);
}
