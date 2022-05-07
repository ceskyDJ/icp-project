#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include "Class.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include "AttributeEditWidget.h"
#include <QScrollArea>
#include "MethodEditWidget.h"

class ClassEditDialog : public QDialog
{
public:
    ClassEditDialog(Class classEntity);
    Class getClassEntity()
    {
        return classEntity;
    }
    static QWidget* createTitle(QPushButton *addPushButton, QString title, QString label);

private:
    Class classEntity;
    QLineEdit *nameTextEdit;
    QVBoxLayout *dialogLayout;
    std::vector<AttributeEditWidget*> atributeEdits;
    QPushButton *addAtributePushButton;
    QPushButton *addMethodPushButton;

    QScrollArea *attributeScrollArea;
    QWidget *attributeWidget;
    QVBoxLayout *attributeLayout;

    QScrollArea *methodScrollArea;
    QWidget *methodWidget;
    QVBoxLayout *methodLayout;
    QPushButton *confirmChangesPushButton;
    QPushButton *rejectChangesPushButton;
    QWidget *buttonWidget;

    void initializeComponents();
    void setMainLayout();
    void makeConnections();
    void addNewAttribute(ClassAttribute *newAttribute);
    void addNewMethod(ClassMethod *newMethod);
    void setScrollAreas();
    void setScrollArea(QWidget *areaWidget, QVBoxLayout *areaLayout, QScrollArea *scrollArea);
    void setButtons();
private slots:
    void deleteAttribute(AttributeEditWidget *toDelete);
    void addNewAttributeSlot();
    void deleteMethod(MethodEditWidget *toDelete);
    void addNewMethodSlot();
    void onNameChanged(QString newName);
    void onConfirmChangesPressed();
    void onRejectChangesPressed();
};

#endif // CLASSEDITDIALOG_H
