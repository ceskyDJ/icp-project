#ifndef OBJECTGRAPHICSITEMEDITDIALOG_H
#define OBJECTGRAPHICSITEMEDITDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QAbstractSpinBox>
#include <QPushButton>
#include <QComboBox>

class ObjectGraphicsItemEditDialog : public QDialog
{
public:
    ObjectGraphicsItemEditDialog();


private:
    QPushButton acceptButton;
    QPushButton cancelButton;
    QLineEdit objectNameLineEdit;
    QComboBox classNameCombo;
    QVBoxLayout mainLayout;
    QFormLayout propertyLayout;
    QString className;
    QString objectName;



    void initializeComponents();
    void connectComponents();
    void setAllLayouts();
    void setOneButton();
    void setAllButtons();
};

#endif // OBJECTGRAPHICSITEMEDITDIALOG_H
