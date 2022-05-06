#include "MethodEditWidget.h"
#include <QLabel>

MethodEditWidget::MethodEditWidget(QWidget *parent, ClassMethod *method)
    : QWidget{parent}
{
    MethodEditWidget::methodEntity = method;
    initializeComponents();
    setComboBox();
    setDeleteButton();
    setMyLayout();
    fillData();
    makeConnections();
}


void MethodEditWidget::initializeComponents()
{
    methodLayOut = new QHBoxLayout;
    accessModifierComboBox = new QComboBox;
    methodTypeComboBox = new QComboBox;
    methodNameLineEdit = new QLineEdit;
    methodReturnDataTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

void MethodEditWidget::makeConnections()
{
    connect(accessModifierComboBox,&QComboBox::currentTextChanged, this, &MethodEditWidget::accsesModifierChanged);
    connect(methodNameLineEdit, &QLineEdit::textChanged,
            this, &MethodEditWidget::nameChanged);
    connect(methodReturnDataTypeLineEdit, &QLineEdit::textChanged,
            this, &MethodEditWidget::returnDataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &MethodEditWidget::sendDeleteSignalSlot);

    connect(methodTypeComboBox,&QComboBox::currentTextChanged, this, &MethodEditWidget::typeChanged);
}

void MethodEditWidget::accsesModifierChanged(QString newText)
{
    methodEntity->setAccessModifier(convertIntToModifier(newText[0].unicode()));
}

void MethodEditWidget::typeChanged(QString newText)
{
    methodEntity->setType(convertTextToType(newText));
}

void MethodEditWidget::nameChanged(QString newText)
{
    methodEntity->setName(newText.toStdString());
}

void MethodEditWidget::returnDataTypeChanged(QString newText)
{
    methodEntity->setReturnDataType(newText.toStdString());
}

void MethodEditWidget::setComboBox()
{
    accessModifierComboBox->addItem("+");
    accessModifierComboBox->addItem("-");
    accessModifierComboBox->addItem("#");
    accessModifierComboBox->addItem("~");

    methodTypeComboBox->addItem("NORMAL");
    methodTypeComboBox->addItem("ABSTRACT");
}

void MethodEditWidget::setMyLayout()
{
    methodLayOut->addWidget(new QLabel("Typ:"));
    methodLayOut->addWidget(methodTypeComboBox);
    methodLayOut->addWidget(new QLabel("Modifikátor přístupu:"));
    methodLayOut->addWidget(accessModifierComboBox);
    methodLayOut->addWidget(new QLabel("Název"));
    methodLayOut->addWidget(methodNameLineEdit);
    methodLayOut->addWidget(new QLabel("Návratový typ"));
    methodLayOut->addWidget(methodReturnDataTypeLineEdit);
    methodLayOut->addWidget(deleteButton);
    setLayout(methodLayOut);
}

AccessModifier MethodEditWidget::convertIntToModifier(int modifierChar)
{
    switch (modifierChar) {
    case '+':
        return AccessModifier::PUBLIC;
    case '-':
        return AccessModifier::PRIVATE;
    case '#':
        return AccessModifier::PROTECTED;
    case '~':
        return AccessModifier::PACKAGE_PRIVATE;
    default:
        return AccessModifier::PUBLIC;
    }
}

QString MethodEditWidget::convertModifierToQString(AccessModifier modifier)
{
    switch (modifier) {
    case AccessModifier::PUBLIC:
        return "+";
    case AccessModifier::PRIVATE:
        return "-";
    case AccessModifier::PROTECTED:
        return "#";
    case AccessModifier::PACKAGE_PRIVATE:
        return "~";
    default:
        return "+";
    }
}

QString MethodEditWidget::convertTypeToQString(ClassMethodType type)
{
    switch (type) {
    case ClassMethodType::NORMAL:
        return "NORMAL";
    case ClassMethodType::ABSTRACT:
    default:
        return "ABSTRACT";
    }
}

ClassMethodType MethodEditWidget::convertTextToType(QString type)
{
    if(type == "ABSTRACT")
        return ClassMethodType::ABSTRACT;
    else
        return ClassMethodType::NORMAL;
}

void MethodEditWidget::fillData()
{
    methodTypeComboBox->setCurrentText(convertTypeToQString(methodEntity->getType()));
    accessModifierComboBox->setCurrentText(convertModifierToQString(methodEntity->getAccessModifier()));
    methodNameLineEdit->setText(QString::fromStdString(methodEntity->getName()));
    methodReturnDataTypeLineEdit->setText(QString::fromStdString(methodEntity->getReturnDataType()));
}

void MethodEditWidget::setDeleteButton()
{
    deleteButton->setIcon(QIcon(":/closeCross.png"));
}


void MethodEditWidget::sendDeleteSignalSlot()
{
    emit deleteButtonPressed(this);
}
