/**
 * @file ClassDiagramWindow.h
 * Má z úkol vytvořit okno pro kreslení UML diagramů tříd.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef CLASSDIAGRAMWINDOW_H
#define CLASSDIAGRAMWINDOW_H
#include "qmainwindow.h"
#include <QWidget>
#include <QToolBar>
#include <QToolBox>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QLabel>
#include "classNode.h"
#include "ClassEditDialog.h"

class ClassDiagramWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClassDiagramWindow();

private:
    int minToolboxWidth = 200;
    int toolboxItemSize = 50;

    QToolBar *taskBar;
    QToolBar *diagramTabs;
    QToolBox *toolBox;
    QGraphicsScene *classDiagramScene;
    QGraphicsView *classDiagramView;
    QWidget *classDiagramCenterWidget;

    QToolButton *agregationToolItem;
    QToolButton *fellowshipToolItem;
    QToolButton *compositionToolItem;
    QToolButton *generalisationToolItem;
    QToolButton *classShapeToolItem;

    void setModellingSpace();
    void setTaskBars();
    void initializeComponents();
    void setWindowLayout();
    void setMainWindow();
    void setTooBox();
    void connectComponents();
    QWidget *prepareToolItem(QIcon icon, QString labelString, QToolButton *newToolButton);
    QWidget *prepareSequencDiagramTab(QString label);

private slots:
    void addClassNode();

signals:

};

#endif // CLASSDIAGRAMWINDOW_H
