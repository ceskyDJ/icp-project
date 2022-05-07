#include "MethodEditWidget.h"
#include <QLabel>
#include "ClassEditDialog.h"

MethodEditWidget::MethodEditWidget(QWidget *parent, ClassMethod *method)
    : QWidget{parent}
{
    MethodEditWidget::methodEntity = method;
    initializeComponents();
    setComboBox();
    setDeleteButton();
    setScrollArea();
    setAddButton();
    setMyLayout();
    fillData();
    makeConnections();
}


void MethodEditWidget::initializeComponents()
{
    methodLayOut = new QGridLayout;
    accessModifierComboBox = new QComboBox;
    methodTypeComboBox = new QComboBox;
    methodNameLineEdit = new QLineEdit;
    methodReturnDataTypeLineEdit = new QLineEdit;
    deleteButton = new QPushButton;
    parameterScrollArea = new QScrollArea;
    parameterWidget = new QWidget;
    parameterLayout = new QVBoxLayout;
    mainLayOut = new QVBoxLayout;
    addParameterPushButton = new QPushButton;
}

void MethodEditWidget::makeConnections()
{
    connect(accessModifierComboBox,&QComboBox::currentTextChanged, this, &MethodEditWidget::accsesModifierChanged);
    connect(methodNameLineEdit, &QLineEdit::textChanged,
            this, &MethodEditWidget::nameChanged);
    connect(methodReturnDataTypeLineEdit, &QLineEdit::textChanged,
            this, &MethodEditWidget::returnDataTypeChanged);
    connect(deleteButton, &QPushButton::pressed, this, &MethodEditWidget::sendDeleteSignalSlot);

    connect(methodTypeComboBox, &QComboBox::currentTextChanged, this, &MethodEditWidget::typeChanged);
    connect(addParameterPushButton, &QPushButton::pressed, this, &MethodEditWidget::addNewParameterSlot);
}

void MethodEditWidget::accsesModifierChanged(QString newText)
{
    std::string accesMod = newText.toStdString();
    methodEntity->setAccessModifier(AccessModifier(accesMod));
}

void MethodEditWidget::typeChanged(QString newText)
{
    std::string methodType = newText.toStdString();
    methodEntity->setType(ClassMethodType::deserialize(methodType));
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
    for(AccessModifier &accessModifier : AccessModifier::values())
        accessModifierComboBox->addItem(QString::fromStdString(static_cast<std::string>(accessModifier)));

    for(ClassMethodType &methodType : ClassMethodType::values())
        methodTypeComboBox->addItem(QString::fromStdString(methodType.serialize()));

}

void MethodEditWidget::setMyLayout()
{
    QWidget *mainWidget = new QWidget;
    methodLayOut->addWidget(new QLabel("Type:"), 0, 0);
    methodLayOut->addWidget(methodTypeComboBox, 0, 1);
    methodLayOut->addWidget(new QLabel("Access modifier:"), 0, 2);
    methodLayOut->addWidget(accessModifierComboBox, 0, 3);
    methodLayOut->addWidget(new QLabel("Name"), 0, 4);
    methodLayOut->addWidget(methodNameLineEdit, 0, 5);
    methodLayOut->addWidget(new QLabel("Return type"), 0, 6);
    methodLayOut->addWidget(methodReturnDataTypeLineEdit, 0, 7);
    methodLayOut->addWidget(deleteButton, 0, 8);

    mainLayOut->addWidget(mainWidget);
    mainLayOut->addWidget(ClassEditDialog::createTitle(addParameterPushButton,"Parameters", "New parameter"));

    mainLayOut->addWidget(parameterScrollArea);
    std::vector<MethodParameter> parameters = methodEntity->getParameters();
    for(size_t i = 0; i < parameters.size(); ++i)
    {//je nezbytne to takto udelat, protoze to jinak pada pri nastaveni hodnoty
        addNewParameter(new MethodParameter(parameters[i].getName(), parameters[i].getDataType()));
    }

    mainWidget->setLayout(methodLayOut);
    setLayout(mainLayOut);
}



void MethodEditWidget::fillData()
{
    ClassMethodType methodType = methodEntity->getType();
    methodTypeComboBox->setCurrentText(QString::fromStdString(methodType.serialize()));
    accessModifierComboBox->setCurrentText(QString::fromStdString(static_cast<std::string>(methodEntity->getAccessModifier())));
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

void MethodEditWidget::setScrollArea()
{
    parameterWidget->setLayout(parameterLayout);
    parameterLayout->setAlignment(Qt::AlignTop);
    parameterScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    parameterScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    parameterScrollArea->setWidgetResizable(true);
    parameterScrollArea->setWidget(parameterWidget);
}

void MethodEditWidget::setAddButton()
{
    addParameterPushButton->setIcon(QIcon(":/addCross.png"));
}

void MethodEditWidget::addNewParameter(MethodParameter *newParameter)
{
    MethodParameterEditWidget *newWidget = new MethodParameterEditWidget(nullptr, newParameter);
    parameterLayout->addWidget(newWidget);
    connect(newWidget, &MethodParameterEditWidget::deleteButtonPressed, this, &MethodEditWidget::deleteParameter);
}

void MethodEditWidget::addNewParameterSlot()
{
    addNewParameter(new MethodParameter("", ""));
}

void MethodEditWidget::deleteParameter(MethodParameterEditWidget *paramEdit)
{
    parameterLayout->removeWidget(paramEdit);
    delete paramEdit;
}
