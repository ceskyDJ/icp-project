/**
 * @class ActorGraphicsItemEditDialog
 * Dialog for edditing ActorGraphicsItem
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ACTORGRAPHICSITEMEDITDIALOG_H
#define ACTORGRAPHICSITEMEDITDIALOG_H

#include "EditDialogBase.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

class ActorGraphicsItemEditDialog : public EditDialogBase
{
public:
    ActorGraphicsItemEditDialog(QString name);

    /**
     * Returns actor name from user.
     *
     * @return actor name from user
     */
    QString getActorName()
    {
        return name;
    }
private:
    QString name;
    QPushButton acceptButton;
    QPushButton cancelButton;
    QPushButton removeButton;
    QLineEdit nameLineEdit;
    QVBoxLayout mainLayout;
    QHBoxLayout buttonLayout;
    QFormLayout propertyLayout;

    void setAllButtons();
    void setOneButton(QPushButton *button ,QIcon icon, QString text, bool setDefault);
    void setButtonLayout();
    void setPropertyLayout();
    void setMainLayout();
    void connectComponents();
private slots:
    void nameChanged(QString newName);
};

#endif // ACTORGRAPHICSITEMEDITDIALOG_H
