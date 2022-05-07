#include "MethodParameterEditWidget.h"
#include <QLabel>

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


void MethodParameterEditWidget::initializeComponents()
{
    parameterLayout = new QHBoxLayout;
    parameterNameLineEdit = new QLineEdit;
    parameterDateTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

void MethodParameterEditWidget::nameChanged(QString newText)
{
    parameterEntity->setName(newText.toStdString());
}

void MethodParameterEditWidget::dataTypeChanged(QString newText)
{
    parameterEntity->setDataType(newText.toStdString());
}

void MethodParameterEditWidget::setMyLayout()
{
    parameterLayout->addWidget(new QLabel("Název"));
    parameterLayout->addWidget(parameterNameLineEdit);
    parameterLayout->addWidget(new QLabel("Datový typ"));
    parameterLayout->addWidget(parameterDateTypeLineEdit);
    parameterLayout->addWidget(deleteButton);
    setLayout(parameterLayout);
}

void MethodParameterEditWidget::fillData()
{
    parameterNameLineEdit->setText(QString::fromStdString(parameterEntity->getName()));
    parameterDateTypeLineEdit->setText(QString::fromStdString(parameterEntity->getDataType()));
}

void MethodParameterEditWidget::setDeleteButton()
{
    deleteButton->setIcon(QIcon(":/closeCross.png"));
}


void MethodParameterEditWidget::sendDeleteSignalSlot()
{
    emit deleteButtonPressed(this);
}
