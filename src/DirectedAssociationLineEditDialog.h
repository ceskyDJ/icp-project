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
    DirectedAssociationLineEditDialog(DirectedAssociationLine *line);
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
    DirectedAssociationLine *relationshipLine;
    QFormLayout *newNameLayout;
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    QPushButton *removeButton;
    QPushButton *switchArrowsButton;
    QLineEdit *nameLineEdit;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QFormLayout *lineEditLayout;
    bool removeSelected = false;
    bool switchNodesSelected = false;


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
    void removeLine();
    void setName(QString newName);
    void switchNodes();
};

#endif // DIRECTEDASSOCIATIONLINEEDITDIALOG_H
