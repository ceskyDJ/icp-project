/**
 * @file LineWithArrowEditDialog.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef LINEWITHARROWEDITDIALOG_H
#define LINEWITHARROWEDITDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "LineWithArrow.h"
#include <QHBoxLayout>
#include <QGraphicsSceneMouseEvent>

/**
 * Dialog which allows to revers line directory or remove reltaionship.
 */
class LineWithArrowEditDialog : public QDialog
{
public:
    /**
     * Constructor for dialog - sets relationshipLine, initializes components
     * sets connections and layout.
     *
     * @param relationship
     */
    explicit LineWithArrowEditDialog(LineWithArrow *relationship);
protected:
    // Dependencies
    /**
     * Observable for distributing information about scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;
    /**
     * button after which should be nodes switched (from and to)
     */
    QPushButton *switchNodesButton;
    /**
     * After click on this button, line should be removed
     */
    QPushButton *removeRelationshipButton;
    /**
     * After click on this button nothing happens - only dialog will be closed 
     */
    QPushButton *cancelButton;

    /**
     * layout of whole dialog 
     */
    QHBoxLayout *mainLayout;
    /**
     * This object represents this line:
     */
    LineWithArrow *relationshipLine;

    /**
     * Initializes all components.
     */
    void initializeComponents();
    /**
     * Connects buttons pressed signal with corresponding slot (cancel, switch lines, remove relationship).
     */
    void connectComponents();
    /**
     * Sets layout of the dialog.
     */
    void setMyLayout();
    /**
     * Sets buttons icon and text.
     *
     * @param icon Icon that will be set to button.
     * @param text Text that will be written in button.
     * @param button Buton that will be set.
     */
    void setOneButton(QIcon icon, QString text, QPushButton *button);
    /**
     * Sets all buttons icon and text.
     */
    void setAllButtons();
    /**
     * Sets window title to FROM_NODE --> TO_NODE
     */
    void setTitle();
private slots:
    /**
     * Switches arrow in a relationship.
     */
    void switchArrow();
    /**
     * Removes whole relatinoship and close dialog.
     */
    void removeRelationship();
    /**
     * Close dialog.
     */
    void cancel();
};

#endif // RELATIONSHIPEDITDIALOG_H
