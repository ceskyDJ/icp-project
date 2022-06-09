/**
 * @file AssociationLineEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahe (xsmahe01)
 */
#ifndef ASSOCIATIONLINEEDITDIALOG_H
#define ASSOCIATIONLINEEDITDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "AssociationLine.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGraphicsSceneMouseEvent>
#include <QLineEdit>
#include <QWidget>

/**
 * Dialog which allow to edit or delete relationship.
 */
class AssociationLineEditDialog : public QDialog
{
public:
    AssociationLineEditDialog(UndirectedAssociation *relationship);
    /**
     * Checks if dialog was confirmed.
     * 
     * @return true if accept was selected
     * @return false if accept was NOT selected
     */
    bool accepted()
    {
        return acceptSelected;
    }

    /**
     * getRelationship Get edited relationship.
     * @return edited relationship
     */
    UndirectedAssociation *getRelationship()
    {
        return relationship;
    }

    /**
     * Returns if relationship should be deleted.
     * @return true if delete button was pressed.
     * @return false if delete button was not pressed.
     */
    bool deleteRelationship()
    {
        return removeSelected;
    }
private:
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    QPushButton *deleteButton;
    QLineEdit *associationNameLineEdit;
    QLineEdit *firstCardinalityLineEdit;
    QLineEdit *secondCardinalityLineEdit;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QFormLayout *lineEditLayout;
    UndirectedAssociation *relationship;
    bool acceptSelected = false;
    bool removeSelected = false;

    void initializeComponents();
    void connectComponents();
    void setAllLayouts();
    void setButtonLayout();
    void setFormLayout();
    void setMainLayout();
    void setAllButtons();
    void setOneButton(QIcon icon, QString text, QPushButton *button);
private slots:
    void cancel();
    void acceptChanges();
    void removeAssociation();
    void setName(QString newName);
    void setFirstCardinality(QString newCardinality);
    void setSecondCardinality(QString newCardinality);
};

#endif // ASSOCIATIONLINEEDITDIALOG_H
