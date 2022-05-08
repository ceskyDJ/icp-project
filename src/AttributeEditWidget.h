/**
 * @class AttributeEditWidget
 * Widget that allows to load, show and edit data of Class atributes.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
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
    /**
     * getAttribute Returns eddited attribute
     *
     * @return ClassAttribute* - eddited attribute
     */
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

    /**
     * AttributeEditWidget::initializeComponents Initializes components - creates their instances
     */
    void initializeComponents();

    /**
     * AttributeEditWidget::makeConnections Connects unnesecary signals and slots.
     */
    void makeConnections();

    /**
     * AttributeEditWidget::setComboBox Sests combobox datasource
     */
    void setComboBox();

    /**
     * AttributeEditWidget::setMyLayout Puts a new layout with all widgets.
     */
    void setMyLayout();

    /**
     * AttributeEditWidget::fillData Fills data to dialog widgets from attribute.
     */
    void fillData();

    /**
     * AttributeEditWidget::setDeleteButton Sets delete button style.
     */
    void setDeleteButton();


private slots:
    /**
     * AttributeEditWidget::accsesModifierChanged Slot that sets access modifier in entity.
     * It gets data from accessModifierCombobox.
     *
     * @param newText
     */
    void accsesModifierChanged(QString newText);

    /**
     * AttributeEditWidget::nameChanged Slot which sests new attribute name.
     *
     * @param newText
     */
    void nameChanged(QString newText);

    /**
     * AttributeEditWidget::dataTypeChanged Slot which sests new attribute datatype.
     *
     * @param newText
     */
    void dataTypeChanged(QString newText);

    /**
     * AttributeEditWidget::sendDeleteSignalSlot Emits a signal to delete this atribute
     */
    void sendDeleteSignalSlot();
};

#endif // ATTRIBUTEEDITWIDGET_H
