#include "AttributeEditWidget.h"
#include "qaction.h"
#include <QLabel>

AttributeEditWidget::AttributeEditWidget(QWidget *parent, ClassAttribute *attribute)
    : QWidget{parent}
{
    AttributeEditWidget::attributeEntity = attribute;
    initializeComponents();
    setComboBox();
    setDeleteButton();
    setMyLayout();
    fillData();
    connect(accessModifierComboBox,&QComboBox::currentTextChanged, this, &AttributeEditWidget::accsesModifierChanged);
    connect(attributeNameLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::nameChanged);
    connect(attributeDateTypeLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::dataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &AttributeEditWidget::sendDeleteSignalSlot);
}

void AttributeEditWidget::initializeComponents()
{
    attrLayOut = new QHBoxLayout;
    accessModifierComboBox = new QComboBox;
    attributeNameLineEdit = new QLineEdit;
    attributeDateTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

void AttributeEditWidget::accsesModifierChanged(QString newText)
{
    attributeEntity->setAccessModifier(convertIntToModifier(newText[0].unicode()));
}

void AttributeEditWidget::nameChanged(QString newText)
{
    attributeEntity->setName(newText.toStdString());
}

void AttributeEditWidget::dataTypeChanged(QString newText)
{
    attributeEntity->setDataType(newText.toStdString());
}

void AttributeEditWidget::setComboBox()
{
    accessModifierComboBox->addItem("+");
    accessModifierComboBox->addItem("-");
    accessModifierComboBox->addItem("#");
    accessModifierComboBox->addItem("~");
}

void AttributeEditWidget::setMyLayout()
{
    attrLayOut->addWidget(new QLabel("Access modifier:"));
    attrLayOut->addWidget(accessModifierComboBox);
    attrLayOut->addWidget(new QLabel("Name"));
    attrLayOut->addWidget(attributeNameLineEdit);
    attrLayOut->addWidget(new QLabel("Datatype"));
    attrLayOut->addWidget(attributeDateTypeLineEdit);
    attrLayOut->addWidget(deleteButton);
    setLayout(attrLayOut);
}

AccessModifier AttributeEditWidget::convertIntToModifier(int modifierChar)
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

QString AttributeEditWidget::convertModifierToQString(AccessModifier modifier)
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

void AttributeEditWidget::fillData()
{
    accessModifierComboBox->setCurrentText(convertModifierToQString(attributeEntity->getAccessModifier()));
    attributeNameLineEdit->setText(QString::fromStdString(attributeEntity->getName()));
    attributeDateTypeLineEdit->setText(QString::fromStdString(attributeEntity->getDataType()));
}

void AttributeEditWidget::setDeleteButton()
{
    deleteButton->setIcon(QIcon(":/closeCross.png"));
}


void AttributeEditWidget::sendDeleteSignalSlot()
{
    emit deleteButtonPressed(this);
}
