#include "ClassEditDialog.h"
#include <QLabel>
ClassEditDialog::ClassEditDialog(Class classEntity)
{
    ClassEditDialog::classEntity = classEntity;
    initializeComponents();
    setMainLayout();
}

void ClassEditDialog::initializeComponents()
{
    nameTextEdit = new QLineEdit;
    dialogLayout = new QVBoxLayout;
}

void ClassEditDialog::setMainLayout()
{
    QFormLayout *nameLayout = new QFormLayout;
    QWidget *nameWidget = new QWidget;
    nameLayout->addRow("Název třídy:", nameTextEdit);
    nameTextEdit->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum));
    nameWidget->setLayout(nameLayout);

    QWidget *attr = new QWidget;
    QHBoxLayout *attrLayOut = new QHBoxLayout;
    attrLayOut->addWidget(new QLineEdit());
    attrLayOut->addWidget(new QLineEdit());
    attrLayOut->addWidget(new QLineEdit());
    attr->setLayout(attrLayOut);

    dialogLayout->addWidget(nameWidget);
    dialogLayout->addWidget(new QLabel("Třídní atributy:"));
    dialogLayout->addWidget(attr);
    setLayout(dialogLayout);
    setMinimumSize(400,500);
    setWindowTitle("Úprava třídy");
}
