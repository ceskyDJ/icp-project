/**
 * @class LineWithArrowEditDialog
 * Dialog which allow to revers line directory or remove reltaionship.
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

class LineWithArrowEditDialog : public QDialog
{
public:
    explicit LineWithArrowEditDialog(LineWithArrow *relationship);
protected:
    // Dependencies
    /**
     * Observable for distributing information about scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;

    QPushButton *switchNodesButton;
    QPushButton *removeRelationshipButton;
    QPushButton *cancelButton;
    QHBoxLayout *mainLayout;
    LineWithArrow *relationshipLine;

    void initializeComponents();
    void connectComponents();
    void setMyLayout();
    void setOneButton(QIcon icon, QString text, QPushButton *button);
    void setAllButtons();
    void setTitle();
private slots:
    void switchArrow();
    void removeRelationship();
    void cancel();
};

#endif // RELATIONSHIPEDITDIALOG_H
