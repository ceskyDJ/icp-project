/**
 * @file DirectedAssociationLineEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef DIRECTEDASSOCIATIONLINEEDITDIALOG_H
#define DIRECTEDASSOCIATIONLINEEDITDIALOG_H

#include "LineWithArrowEditDialog.h"
#include "DirectedAssociationLine.h"
#include <QFormLayout>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>

/**
 * Dialog for editing DirectAssociationDialog.
 */
class DirectedAssociationLineEditDialog : public QDialog
{
public:
    /**
     * @brief Construct a new Association Line edit dialog.
     *
     * @param line Line which should be edited.
     */
    DirectedAssociationLineEditDialog(DirectedAssociationLine *line);
    /**
     * Destructs this object - it has to delete direct association pointer
     */
    ~DirectedAssociationLineEditDialog();
    /**
     * Gets new name of line.
     *
     * @return new name of line.
     */
    QString getNewName()
    {
        return relationshipLine->getName();
    }

    /**
     * Getter for remove node flag.
     *
     * @return true if remove button was pressed
     * @return falsr if remove button was NOT pressed
     */
    bool removePressed()
    {
        return removeSelected;
    }

    /**
     * Getter for switch ndoes flag
     *
     * @return true if switchArrow button was pressed
     * @return falsr if switchArrow button was NOT pressed
     */
    bool switchArrowsPressed()
    {
        return switchNodesSelected;
    }
protected:
    /**
     * Directed association item that represents this object.
     */
    DirectedAssociationLine *relationshipLine;
    /**
     * Editting name layout.
     */
    QFormLayout *newNameLayout;
    /**
     * Button that guarantes thatchanges will be accepted.
     */
    QPushButton *acceptButton;
    /**
     * Button that cancels changes
     */
    QPushButton *cancelButton;
    /**
     * After pressing this button, line should be removed 
     */
    QPushButton *removeButton;
    /**
     * After pressing this button, line will swucth and arrow.
     */
    QPushButton *switchArrowsButton;
    /**
     * line edit used to edit name of relationship
     */
    QLineEdit *nameLineEdit;
    /**
     * Layout for buttons
     */
    QHBoxLayout *buttonLayout;
    /**
     * layout of this item
     */
    QVBoxLayout *mainLayout;
    /**
     * Layout for line edits
     */
    QFormLayout *lineEditLayout;
    /**
     * flag that shows that user pressed on remove  button
     */
    bool removeSelected = false;
    /**
     * flag that shows that user pressed switch node
     */
    bool switchNodesSelected = false;


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
     * Closes dialog and sets accept flag.
     */
    void acceptChanges();
    /**
     * Sets remove flag to true and closes dialog.
     */
    void removeLine();
    /**
     * Sets a new name of relationship.
     *
     * @param newName new relationship name
     */
    void setName(QString newName);
    /**
     * Sets switch arrow flag to true and ends dialog.
     */
    void switchNodes();
};

#endif // DIRECTEDASSOCIATIONLINEEDITDIALOG_H
