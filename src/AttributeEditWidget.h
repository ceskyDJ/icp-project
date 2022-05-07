#ifndef ATTRIBUTEEDITWIDGET_H
#define ATTRIBUTEEDITWIDGET_H

#include <QWidget>
#include "ClassAttribute.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class AttributeEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttributeEditWidget(QWidget *parent = nullptr, ClassAttribute *attribute = nullptr);
    ClassAttribute *getAttribute()
    {
        return attributeEntity;
    }
signals:
    void deleteButtonPressed(AttributeEditWidget *attributeWidget);

private:
    ClassAttribute *attributeEntity;
    QHBoxLayout *attrLayOut;
    QComboBox *accessModifierComboBox;
    QLineEdit *attributeNameLineEdit;
    QLineEdit *attributeDateTypeLineEdit;
    QPushButton *deleteButton;

    void initializeComponents();
    void setComboBox();
    void setMyLayout();
    void fillData();
    void setDeleteButton();
    void makeConnections();

private slots:
        void accsesModifierChanged(QString newText);
        void nameChanged(QString newText);
        void dataTypeChanged(QString newText);
        void sendDeleteSignalSlot();
};

#endif // ATTRIBUTEEDITWIDGET_H
