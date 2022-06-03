/**
 * @file ClassEditDialog.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include "ClassEditDialog.h"
#include <QLabel>
#include <algorithm>

/**
 * ClassEditDialog::ClassEditDialog constructor
 * @param classEntity Class that should be eddited
 */
ClassEditDialog::ClassEditDialog(Class *classEntity): classEntity{classEntity}
{
    initializeComponents();
    setScrollAreas();
    setButtons();
    setComboBox();
    setMainLayout();
    makeConnections();
    fillData();
}

/**
 * ClassEditDialog::initializeComponents Initializes all components.
 */
void ClassEditDialog::initializeComponents()
{
    nameTextEdit = new QLineEdit;
    dialogLayout = new QVBoxLayout;
    addAtributePushButton = new QPushButton;
    addMethodPushButton = new QPushButton;
    attributeScrollArea = new QScrollArea;
    attributeWidget = new QWidget;
    attributeLayout = new QVBoxLayout;
    methodScrollArea = new QScrollArea;
    methodWidget = new QWidget;
    methodLayout = new QVBoxLayout;
    confirmChangesPushButton = new QPushButton;
    rejectChangesPushButton = new QPushButton;
    buttonWidget = new QWidget;
    contextMenu = new QMenu;
    classTypeComboBox = new QComboBox;
}

/**
 * ClassEditDialog::setMainLayout Arranges widgets to layout.
 */
void ClassEditDialog::setMainLayout()
{
    QHBoxLayout *nameLayout = new QHBoxLayout;
    QWidget *nameWidget = new QWidget;
    nameLayout->addWidget(new QLabel("Class name:"));
    nameLayout->addWidget(nameTextEdit);
    nameLayout->addWidget(new QLabel("Class type:"));
    nameLayout->addWidget(classTypeComboBox);
    nameWidget->setLayout(nameLayout);

    dialogLayout->addWidget(nameWidget);
    dialogLayout->addWidget(createTitle(addAtributePushButton, "Attributes", "New attribute"));
    dialogLayout->addWidget(attributeScrollArea);
    for (size_t i = 0; i < classEntity->getAttributes().size(); i++)
    {
        addNewAttribute(&(classEntity->getAttributes()[i]));
    }

    dialogLayout->addWidget(createTitle(addMethodPushButton, "Methods", "New method"));
    dialogLayout->addWidget(methodScrollArea);
    for (size_t i = 0; i < classEntity->getMethods().size(); i++)
    {
        addNewMethod(&(classEntity->getMethods()[i]));
    }

    dialogLayout->addWidget(buttonWidget);
    setLayout(dialogLayout);
    setMinimumSize(700,700);
    setWindowTitle("Úprava třídy");
}

/**
 * ClassEditDialog::deleteAttribute deletes attribute
 *
 * @param toDelete attribute that should be deleted
 */
void ClassEditDialog::deleteAttribute(AttributeEditWidget *toDelete)
{
    dialogLayout->removeWidget(toDelete);
    delete toDelete;
}

/**
 * ClassEditDialog::deleteMethod deletes a method
 *
 * @param toDelete method that should be deleted
 */
void ClassEditDialog::deleteMethod(MethodEditWidget *toDelete)
{
    dialogLayout->removeWidget(toDelete);
    delete toDelete;
}

/**
 * ClassEditDialog::createTitle creates new section in edit dialog - puts a label and add button
 *
 * @param addPushButton button which should be used to add new items
 * @param title for new section
 * @param label label to add push button
 * @return widget representing title
 */
QWidget* ClassEditDialog::createTitle(QPushButton *addPushButton, QString title, QString label)
{
    QHBoxLayout *menuLayout = new QHBoxLayout;
    QIcon a = QIcon(":/addCross.png");
    addPushButton->setIcon(a);
    addPushButton->setText(label);
    menuLayout->addWidget(new QLabel(title));
    menuLayout->addWidget(addPushButton);

    QWidget *titleWidget = new QWidget;
    titleWidget->setLayout(menuLayout);
    return titleWidget;
}

/**
 * @brief ClassEditDialog::addNewAttribute Adds new attribute to scroll area
 * @param newAttribute new attribute to add
 */
void ClassEditDialog::addNewAttribute(ClassAttribute *newAttribute)
{
    AttributeEditWidget *newWidget = new AttributeEditWidget(nullptr, newAttribute);
    attributeLayout->addWidget(newWidget);
    connect(newWidget, &AttributeEditWidget::deleteButtonPressed, this, &ClassEditDialog::deleteAttribute);
}

/**
 * @brief ClassEditDialog::addNewMethod Adds new method to scroll area.
 * @param newMethod method to add
 */
void ClassEditDialog::addNewMethod(ClassMethod *newMethod)
{
    MethodEditWidget *newWidget = new MethodEditWidget(nullptr, newMethod);
    methodLayout->addWidget(newWidget);
    connect(newWidget, &MethodEditWidget::deleteButtonPressed, this, &ClassEditDialog::deleteMethod);
}

/**
 * @brief ClassEditDialog::addNewAttributeSlot Slot which will be called after emit singal of add button
 */
void ClassEditDialog::addNewAttributeSlot()
{
    addNewAttribute(new ClassAttribute("", AccessModifier::PUBLIC, ""));
}

/**
 * @brief ClassEditDialog::addNewMethodSlot Slot which will be called after emit singal of add button
 */
void ClassEditDialog::addNewMethodSlot()
{
    std::vector<MethodParameter> vec;
    addNewMethod(new ClassMethod("", AccessModifier::PUBLIC, vec));
}

/**
 * @brief ClassEditDialog::makeConnections Make all unnesesary connections
 */
void ClassEditDialog::makeConnections()
{
    connect(addAtributePushButton, &QPushButton::pressed, this, &ClassEditDialog::addNewAttributeSlot);
    connect(nameTextEdit, &QLineEdit::textChanged, this, &ClassEditDialog::onNameChanged);
    connect(addMethodPushButton, &QPushButton::pressed, this, &ClassEditDialog::addNewMethodSlot);
    connect(confirmChangesPushButton, &QPushButton::pressed, this, &ClassEditDialog::onConfirmChangesPressed);
    connect(rejectChangesPushButton, &QPushButton::pressed, this, &ClassEditDialog::onRejectChangesPressed);
    connect(classTypeComboBox, &QComboBox::currentTextChanged, this, &ClassEditDialog::onClassTypeChanged);
}

/**
 * @brief ClassEditDialog::setScrollAreas sets new scroll areas
 */
void ClassEditDialog::setScrollAreas()
{
    setScrollArea(attributeWidget, attributeLayout, attributeScrollArea);
    setScrollArea(methodWidget, methodLayout, methodScrollArea);
}

/**
 * @brief ClassEditDialog::setScrollArea set scroll area - creates widget with layout in scroll area
 * @param areaWidget widget where will be controls added
 * @param areaLayout layout for widgets
 * @param scrollArea scroll area
 */
void ClassEditDialog::setScrollArea(QWidget *areaWidget, QVBoxLayout *areaLayout, QScrollArea *scrollArea)
{
    areaWidget->setLayout(areaLayout);
    areaLayout->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(areaWidget);
}

/**
 * @brief ClassEditDialog::onNameChanged slot when name changes
 * @param newName new name of class
 */
void ClassEditDialog::onNameChanged(QString newName)
{
    classEntity->setName(newName.toStdString());
}

/**
 * @brief ClassEditDialog::setButtons sets dialog buttons
 */
void ClassEditDialog::setButtons()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    confirmChangesPushButton->setText("Confirm");
    confirmChangesPushButton->setIcon(QIcon(":/nike.png"));

    rejectChangesPushButton->setText("Reject");
    rejectChangesPushButton->setIcon(QIcon(":/closeCross.png"));

    buttonLayout->addWidget(rejectChangesPushButton);
    buttonLayout->addWidget(confirmChangesPushButton);
    buttonLayout->setAlignment(Qt::AlignRight);
    buttonWidget->setLayout(buttonLayout);
}

/**
 * @brief ClassEditDialog::onConfirmChangesPressed confirmation button slot
 */
void ClassEditDialog::onConfirmChangesPressed()
{
    //get class attributes
    std::vector<ClassAttribute> newAttribs;
    for (int i = 0; i < attributeLayout->count(); ++i)
    {
        QWidget *widget = attributeLayout->itemAt(i)->widget();
        AttributeEditWidget *attrWidget = dynamic_cast<AttributeEditWidget *>(widget);
        newAttribs.push_back(*(attrWidget->getAttribute()));
    }

    //get class methods
    std::vector<ClassMethod> newMethods;
    for (int i = 0; i < methodLayout->count(); ++i)
    {
        QWidget *widget = methodLayout->itemAt(i)->widget();
        MethodEditWidget *methodParWidget = dynamic_cast<MethodEditWidget *>(widget);
        newMethods.push_back(*(methodParWidget->getMethod()));
    }

    classEntity->setAttributes(newAttribs);
    classEntity->setMethods(newMethods);
    accept();
}

/**
 * @brief ClassEditDialog::onRejectChangesPressed button slot to reject changes
 */
void ClassEditDialog::onRejectChangesPressed()
{
    reject();
}

/**
 * @brief ClassEditDialog::setComboBox sets combobox properies
 */
void ClassEditDialog::setComboBox()
{
    std::vector<ClassType> classTypes = ClassType::values();
    for(ClassType &classType : classTypes)
        classTypeComboBox->addItem(QString::fromStdString(classType.serialize()));
}

/**
 * @brief ClassEditDialog::fillData fills data into dialog controls
 */
void ClassEditDialog::fillData()
{
    nameTextEdit->setText(QString::fromStdString(classEntity->getName()));
    classTypeComboBox->setCurrentText(QString::fromStdString(classEntity->getClassType().serialize()));
}

/**
 * @brief ClassEditDialog::onClassTypeChanged slot for changig type
 * @param newType of class
 */
void ClassEditDialog::onClassTypeChanged(QString newType)
{
    std::string methodType = newType.toStdString();
    classEntity->setClassType(ClassType::deserialize(methodType));
}
