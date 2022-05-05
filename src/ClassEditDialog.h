#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include "Class.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

class ClassEditDialog : public QDialog
{
public:
    ClassEditDialog(Class classEntity);
    Class getClassEntity()
    {
        return classEntity;
    }

private:
    Class classEntity;
    QLineEdit *nameTextEdit;
    QVBoxLayout *dialogLayout;

    void initializeComponents();
    void setMainLayout();
};

#endif // CLASSEDITDIALOG_H
