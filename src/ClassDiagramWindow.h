/**
 * @class ClassDiagramWindow.h
 * Windows that allows user to draw diagrams.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
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
#include "Line.h"
#include "GeneralizationLine.h"
#include "LineWithArrow.h"
#include "CompositionLine.h"
#include "AgregationLine.h"
#include "AssociationLine.h"
#include "DirectedAssociationLine.h"
#include "RealizationLine.h"
#include "ClassDiagramManager.h"
#include "SceneUpdateObserver.h"
#include "SceneUpdateObservable.h"

class ClassDiagramWindow : public QMainWindow, SceneUpdateObserver
{
    Q_OBJECT
public:
    explicit ClassDiagramWindow(ClassDiagramManager *classDiagramManager, SceneUpdateObservable *sceneUpdateObservable);

    /**
     * Logs scene changes for saving and undo/redo mechanisms
     */
    void logChanges() noexcept override;

private:
    // Dependencies
    ClassDiagramManager *classDiagramManager;
    SceneUpdateObservable *sceneUpdateObservable;

    int minToolboxWidth = 200;
    int toolboxItemSize = 70;

    QToolBar *taskBar;
    QToolBar *diagramTabs;
    QToolBox *toolBox;
    QGraphicsScene *classDiagramScene;
    QGraphicsView *classDiagramView;
    QWidget *classDiagramCenterWidget;
    ClassEditDialog *classEditDialog;

    // Wrapping collections
    ClassDiagram classDiagram;
    std::unordered_map<std::string, ClassNode *> storedClasses;
    std::unordered_map<Line *, Relationship *> storedRelationships;

    QToolButton *agregationToolItem;
    QToolButton *associationToolItem;
    QToolButton *compositionToolItem;
    QToolButton *generalisationToolItem;
    QToolButton *directedAssociationToolItem;
    QToolButton *realizationToolItem;
    QToolButton *classShapeToolItem;
    QToolButton *removeSelectedToolItem;
    ClassNode *firstToSelect = nullptr;
    ClassNode *secondToSelect = nullptr;
    QColor realtionShipSelectedColor = Qt::darkGreen;
    QColor nodeNormalColor = Qt::black;
    QColor nodeColor = nodeNormalColor;
    QColor nodeFirstSelectedColor = Qt::darkMagenta;
    QColor firstPhaseSelectedColor = Qt::darkCyan;
    Line *newLine;
    /**
     * Is currently edited diagram saved to persistent storage (after last update)?
     */
    bool isSaved = false;
    /**
     * Name of the file where the final diagram should be stored in (with absolute path to it)
     *
     * @par This is the file, where changes will be saved when just clicking to "Save"
     * button, not "Save as...". It is a place used for possible auto saving, etc.
     * @par When diagram is loaded from file, the source file will be used.
     */
    std::string targetFileName{};

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
    void connectNodes();
    void createNewLine(Line *line);
    void removeClassNode(ClassNode *classNode);
    void clearScene();
    void redrawClassDiagram();
private slots:
    void addClassNode();
    void removeSelectedClassNodes();
    void associationSelected();
    void nodePressed(ClassNode *node);
    void compositionSelected();
    void agregationSelected();
    void generalisationSelected();
    void directedAssociationSelected();
    void realizationSelected();
    void openButtonClicked();
    void saveButtonClicked();
    void saveAsButtonClicked();
    void undoButtonClicked();
    void redoButtonClicked();
};

#endif // CLASSDIAGRAMWINDOW_H
