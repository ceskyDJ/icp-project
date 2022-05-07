#ifndef METHODPARAMETEREDITWIDGET_H
#define METHODPARAMETEREDITWIDGET_H

#include <QWidget>
#include "MethodParameter.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class MethodParameterEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MethodParameterEditWidget(QWidget *parent = nullptr, MethodParameter *param = new MethodParameter("", ""));
    MethodParameter *getParameter()
    {
        return parameterEntity;
    }
signals:
    void deleteButtonPressed(MethodParameterEditWidget *parameterWidget);

private:
    MethodParameter *parameterEntity;
    QHBoxLayout *parameterLayout;
    QLineEdit *parameterNameLineEdit;
    QLineEdit *parameterDateTypeLineEdit;
    QPushButton *deleteButton;

    void initializeComponents();
    void setMyLayout();
    void fillData();
    void setDeleteButton();
private slots:
        void nameChanged(QString newText);
        void dataTypeChanged(QString newText);
        void sendDeleteSignalSlot();
};

#endif // METHODPARAMETEREDITWIDGET_H