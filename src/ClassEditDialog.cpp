#include "ClassEditDialog.h"
#include <QLabel>
#include <algorithm>

ClassEditDialog::ClassEditDialog(Class classEntity)
{
    ClassEditDialog::classEntity = classEntity;
    initializeComponents();
    setScrollAreas();
    setMainLayout();
    makeConnections();
    nameTextEdit->setText(QString::fromStdString(classEntity.getName()));
}

void ClassEditDialog::initializeComponents()
{
    nameTextEdit = new QLineEdit;
    dialogLayout = new QVBoxLayout;
    addAtributePushButton = new QPushButton;
    attributeScrollArea = new QScrollArea;
    attributeWidget = new QWidget;
    attributeLayout = new QVBoxLayout;
    methodScrollArea = new QScrollArea;
    methodWidget = new QWidget;
    methodLayout = new QVBoxLayout;
    addMethodPushButton = new QPushButton;
}

void ClassEditDialog::setMainLayout()
{
    QFormLayout *nameLayout = new QFormLayout;
    QWidget *nameWidget = new QWidget;
    nameLayout->addRow("Název třídy:", nameTextEdit);
    nameTextEdit->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum));
    nameWidget->setLayout(nameLayout);

    dialogLayout->addWidget(nameWidget);
    dialogLayout->addWidget(createTitle(addAtributePushButton, "Atributy"));
    dialogLayout->addWidget(attributeScrollArea);
    for (size_t i = 0; i < classEntity.getAttributes().size(); i++)
    {
        addNewAttribute(&(classEntity.getAttributes()[i]));
    }

    dialogLayout->addWidget(createTitle(addMethodPushButton, "Metody"));
    dialogLayout->addWidget(methodScrollArea);
    for (size_t i = 0; i < classEntity.getMethods().size(); i++)
    {
        addNewMethod(&(classEntity.getMethods()[i]));
    }

    setLayout(dialogLayout);
    setMinimumSize(400,500);
    setWindowTitle("Úprava třídy");
}

void ClassEditDialog::deleteAttribute(AttributeEditWidget *toDelete)
{
    dialogLayout->removeWidget(toDelete);
    delete toDelete;
}

QWidget* ClassEditDialog::createTitle(QPushButton *addPushButton, QString title)
{
    QHBoxLayout *menuLayout = new QHBoxLayout;
    addPushButton->setIcon(QIcon(":/addCross.png"));
    menuLayout->addWidget(new QLabel(title));
    menuLayout->addWidget(addPushButton);

    QWidget *titleWidget = new QWidget;
    titleWidget->setLayout(menuLayout);
    return titleWidget;
}

void ClassEditDialog::addNewAttribute(ClassAttribute *newAttribute)
{
    AttributeEditWidget *newWidget = new AttributeEditWidget(nullptr, newAttribute);
    attributeLayout->addWidget(newWidget);
    connect(newWidget, &AttributeEditWidget::deleteButtonPressed, this, &ClassEditDialog::deleteAttribute);
}

void ClassEditDialog::addNewMethod(ClassMethod *newMethod)
{
    MethodEditWidget *newWidget = new MethodEditWidget(nullptr, newMethod);
    methodLayout->addWidget(newWidget);
    //connect(newWidget, &MethodEditWidget::deleteButtonPressed, this, &ClassEditDialog::deleteMethod);
}

void ClassEditDialog::addNewAttributeSlot()
{
    addNewAttribute(new ClassAttribute("", AccessModifier::PUBLIC, ""));
}

void ClassEditDialog::makeConnections()
{
    connect(addAtributePushButton, &QPushButton::pressed, this, &ClassEditDialog::addNewAttributeSlot);
    connect(nameTextEdit, &QLineEdit::textChanged, this, ClassEditDialog::onNameChanged);
}

void ClassEditDialog::setScrollAreas()
{
    setScrollArea(attributeWidget, attributeLayout, attributeScrollArea);
    setScrollArea(methodWidget, methodLayout, methodScrollArea);
}

void ClassEditDialog::setScrollArea(QWidget *areaWidget, QVBoxLayout *areaLayout, QScrollArea *scrollArea)
{
    areaWidget->setLayout(areaLayout);
    areaLayout->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(areaWidget);
}

void ClassEditDialog::onNameChanged(QString newName)
{
    classEntity.setName(newName.toStdString());
}
