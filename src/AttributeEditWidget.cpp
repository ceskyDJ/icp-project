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
    makeConnections();
}

void AttributeEditWidget::initializeComponents()
{
    attrLayOut = new QHBoxLayout;
    accessModifierComboBox = new QComboBox;
    attributeNameLineEdit = new QLineEdit;
    attributeDateTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

void AttributeEditWidget::makeConnections()
{
    connect(accessModifierComboBox,&QComboBox::currentTextChanged, this, &AttributeEditWidget::accsesModifierChanged);
    connect(attributeNameLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::nameChanged);
    connect(attributeDateTypeLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::dataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &AttributeEditWidget::sendDeleteSignalSlot);
}

void AttributeEditWidget::accsesModifierChanged(QString newText)
{
    std::string p = newText.toStdString();
    attributeEntity->setAccessModifier(AccessModifier(p));
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
    for(AccessModifier &accessModifier : AccessModifier::values())
        accessModifierComboBox->addItem(QString::fromStdString(static_cast<std::string>(accessModifier)));
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

void AttributeEditWidget::fillData()
{
    accessModifierComboBox->setCurrentText(QString::fromStdString( static_cast<std::string>(attributeEntity->getAccessModifier())));
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
