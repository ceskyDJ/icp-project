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
    /**
     * Class constructor
     * 
     * @param relationship Relationship which should be edited
     */
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
    /**
     * Button that if pressed, changes will be accpted.
     */
    QPushButton *acceptButton;
    /**
     * Button that if pressed, changes will NOT be accpeted.
     */
    QPushButton *cancelButton;
    /**
     * If pressed, item should be removed.
     */
    QPushButton *deleteButton;
    /**
     * Line edit for editting name of relationship.
     */
    QLineEdit *associationNameLineEdit;
    /**
     * Line edit for first cardinality
     */
    QLineEdit *firstCardinalityLineEdit;
    /**
     * Line edit for second cardinality
     */
    QLineEdit *secondCardinalityLineEdit;
    /**
     * Layout for buttons
     */
    QHBoxLayout *buttonLayout;
    /**
     * Layout of this.
     */
    QVBoxLayout *mainLayout;
    /**
     * Layout for properties   line edits.
     */
    QFormLayout *lineEditLayout;
    /**
     * Relationship that this class represents
     */
    UndirectedAssociation *relationship;
    /**
     * Flag that is true when accept was selected
     */
    bool acceptSelected = false;
    /**
     * Flag that is true when object should be deleted
     */
    bool removeSelected = false;


    /**
     * Initializes components
     */
    void initializeComponents();
    /**
     * Connects components.
     */
    void connectComponents();
    /**
     * Set the All Layouts object.
     */
    void setAllLayouts();
    /**
     * Set the Button Layout object.
     */
    void setButtonLayout();
    /**
     * Set the Form Layout object.
     */
    void setFormLayout();
    /**
     * Set the main Layout object.
     */
    void setMainLayout();
    /**
     * Set the All Buttons object.
     */
    void setAllButtons();
    /**
     * Set the One Button's icon and text 
     * 
     * @param icon icon of button 
     * @param text Text that should be displayed on button.
     * @param button Pointer to the treated button.
     */
    void setOneButton(QIcon icon, QString text, QPushButton *button);
private slots:
    /**
     * Cancel slot closes dialog.
     */
    void cancel();
    /**
     * Closes dialog and sets accept flag to true.
     */
    void acceptChanges();
    /**
     * Sets remove flag to true and closes dialog.
     */
    void removeAssociation();
    /**
     * Sets a new name of association.
     *
     * @param newName new association name
     */
    void setName(QString newName);
    /**
     * Sets first cardinality.
     *
     * @param newCardinality new first cardinality
     */
    void setFirstCardinality(QString newCardinality);
    /**
     * Sets second cardinality
     *
     * @param newCardinality new second cardinality
     */
    void setSecondCardinality(QString newCardinality);
};

#endif // ASSOCIATIONLINEEDITDIALOG_H
