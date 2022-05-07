#ifndef METHODEDITWIDGET_H
#define METHODEDITWIDGET_H

#include <QWidget>
#include "ClassMethod.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "MethodParameterEditWidget.h"

class MethodEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MethodEditWidget(QWidget *parent = nullptr, ClassMethod *method = nullptr);
    ClassMethod *getMethod()
    {
        //get class methods
        std::vector<MethodParameter> newParameters;
        for (int i = 0; i < parameterLayout->count(); ++i)
        {
            QWidget *widget = parameterLayout->itemAt(i)->widget();
            MethodParameterEditWidget *aWidget = dynamic_cast<MethodParameterEditWidget *>(widget);
            newParameters.push_back(*(aWidget->getParameter()));
        }
        methodEntity->setParameters(newParameters);
        return methodEntity;
    }
signals:
    void deleteButtonPressed(MethodEditWidget *methodWidget);

private:
    ClassMethod *methodEntity;
    QGridLayout *methodLayOut;
    QVBoxLayout *mainLayOut;
    QComboBox *accessModifierComboBox;
    QComboBox *methodTypeComboBox;
    QLineEdit *methodNameLineEdit;
    QLineEdit *methodReturnDataTypeLineEdit;
    QPushButton *deleteButton;
    QScrollArea *parameterScrollArea;
    QWidget *parameterWidget;
    QVBoxLayout *parameterLayout;
    QPushButton *addParameterPushButton;


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
    void setScrollArea();
    void setAddButton();
    void addNewParameter(MethodParameter *newParameter);
private slots:
    void accsesModifierChanged(QString newText);
    void typeChanged(QString newText);
    void nameChanged(QString newText);
    void returnDataTypeChanged(QString newText);
    void sendDeleteSignalSlot();
    void addNewParameterSlot();
    void deleteParameter(MethodParameterEditWidget *paramEdit);
};

#endif // METHODEDITWIDGET_H
