/**
 * @class AttributeEditWidget
 * Widget that allows to load, show and edit data of Class atributes.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "AttributeEditWidget.h"
#include "qaction.h"
#include <QLabel>

/**
 * AttributeEditWidget::AttributeEditWidget Constructor which prepares widget.
 *
 * @param parent pointer to parrent of Widget
 * @param attribute attribute that should be eddited
 */
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

/**
 * AttributeEditWidget::initializeComponents Initializes components - creates their instances
 */
void AttributeEditWidget::initializeComponents()
{
    attrLayOut = new QHBoxLayout;
    accessModifierComboBox = new QComboBox;
    attributeNameLineEdit = new QLineEdit;
    attributeDateTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
}

/**
 * AttributeEditWidget::makeConnections Connects unnesecary signals and slots.
 */
void AttributeEditWidget::makeConnections()
{
    connect(accessModifierComboBox,&QComboBox::currentTextChanged, this, &AttributeEditWidget::accsesModifierChanged);
    connect(attributeNameLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::nameChanged);
    connect(attributeDateTypeLineEdit, &QLineEdit::textChanged,
            this, &AttributeEditWidget::dataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &AttributeEditWidget::sendDeleteSignalSlot);
}

/**
 * AttributeEditWidget::accsesModifierChanged Slot that sets access modifier in entity.
 * It gets data from accessModifierCombobox.
 *
 * @param newText
 */
void AttributeEditWidget::accsesModifierChanged(QString newText)
{
    std::string p = newText.toStdString();
    attributeEntity->setAccessModifier(AccessModifier(p));
}

/**
 * AttributeEditWidget::nameChanged Slot which sests new attribute name.
 *
 * @param newText
 */
void AttributeEditWidget::nameChanged(QString newText)
{
    attributeEntity->setName(newText.toStdString());
}

/**
 * AttributeEditWidget::dataTypeChanged Slot which sests new attribute datatype.
 *
 * @param newText
 */
void AttributeEditWidget::dataTypeChanged(QString newText)
{
    attributeEntity->setDataType(newText.toStdString());
}

/**
 * AttributeEditWidget::setComboBox Sests combobox datasource
 */
void AttributeEditWidget::setComboBox()
{
    for(AccessModifier &accessModifier : AccessModifier::values())
        accessModifierComboBox->addItem(QString::fromStdString(static_cast<std::string>(accessModifier)));
}

/**
 * AttributeEditWidget::setMyLayout Puts a new layout with all widgets.
 */
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

/**
 * AttributeEditWidget::fillData Fills data to dialog widgets from attribute.
 */
void AttributeEditWidget::fillData()
{
    accessModifierComboBox->setCurrentText(QString::fromStdString( static_cast<std::string>(attributeEntity->getAccessModifier())));
    attributeNameLineEdit->setText(QString::fromStdString(attributeEntity->getName()));
    attributeDateTypeLineEdit->setText(QString::fromStdString(attributeEntity->getDataType()));
}

/**
 * AttributeEditWidget::setDeleteButton Sets delete button style.
 */
void AttributeEditWidget::setDeleteButton()
{
    deleteButton->setIcon(QIcon(":/closeCross.png"));
}

/**
 * AttributeEditWidget::sendDeleteSignalSlot Emits a signal to delete this atribute
 */
void AttributeEditWidget::sendDeleteSignalSlot()
{
    emit deleteButtonPressed(this);
}
