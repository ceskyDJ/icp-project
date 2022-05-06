#ifndef METHODEDITWIDGET_H
#define METHODEDITWIDGET_H

#include <QWidget>
#include "ClassMethod.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class MethodEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MethodEditWidget(QWidget *parent = nullptr, ClassMethod *method = nullptr);
    ClassMethod *getMethod()
    {
        return methodEntity;
    }
signals:
    void deleteButtonPressed(MethodEditWidget *methodWidget);

private:
    ClassMethod *methodEntity;
    QHBoxLayout *methodLayOut;
    QComboBox *accessModifierComboBox;
    QComboBox *methodTypeComboBox;
    QLineEdit *methodNameLineEdit;
    QLineEdit *methodReturnDataTypeLineEdit;
    QPushButton *deleteButton;

    AccessModifier convertIntToModifier(int modifierChar);
    QString convertModifierToQString(AccessModifier modifier);
    QString convertTypeToQString(ClassMethodType type);
    ClassMethodType convertTextToType(QString type);
    void initializeComponents();
    void setComboBox();
    void setMyLayout();
    void fillData();
    void setDeleteButton();
    void makeConnections();
private slots:
        void accsesModifierChanged(QString newText);
        void typeChanged(QString newText);
        void nameChanged(QString newText);
        void returnDataTypeChanged(QString newText);
        void sendDeleteSignalSlot();
};

#endif // METHODEDITWIDGET_H
