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
    ClassEditDialog *classEditDialog;

    QToolButton *agregationToolItem;
    QToolButton *realizationToolItem;
    QToolButton *compositionToolItem;
    QToolButton *generalisationToolItem;
    QToolButton *classShapeToolItem;
    QToolButton *removeSelectedToolItem;
    ClassNode *firstToSelect = nullptr;
    ClassNode *secondToSelect = nullptr;
    QColor realtionShipSelectedColor = Qt::darkGreen;
    QColor nodeNormalColor = Qt::black;
    QColor nodeColor = nodeNormalColor;
    QColor nodeFirstSelectedColor = Qt::darkMagenta;

    void setModellingSpace();
    void setTaskBars();
    void initializeComponents();
    void setWindowLayout();
    void setMainWindow();
    void setTooBox();
    void connectComponents();
    void setAllNodesColor(QColor color);
    QWidget *prepareToolItem(QIcon icon, QString labelString, QToolButton *newToolButton);
    QWidget *prepareSequencDiagramTab(QString label);
    ClassNode *getSelectedNode();
    void connectLines();
private slots:
    void addClassNode();
    void removeClassNode();
    void relationShipSelected();
    void selectionChanged();

};

#endif // CLASSDIAGRAMWINDOW_H
