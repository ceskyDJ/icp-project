/**
 * @file MainWindow.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef CLASS_DIAGRAM_WINDOW_H
#define CLASS_DIAGRAM_WINDOW_H
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
#include "CustomScene.h"

/**
 * Windows that allows user to draw diagrams.
 */
class MainWindow : public QMainWindow, SceneUpdateObserver
{
    Q_OBJECT
public:
    /**
     * Class constructor
     *
     * @par Initialiezes components and prepare all QWidgets and controls.
     *
     * @param classDiagramManager Class diagram manage (dependency)
     * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
     */
    MainWindow(ClassDiagramManager *classDiagramManager, SceneUpdateObservable *sceneUpdateObservable);

    /**
     * Logs scene changes for saving and undo/redo mechanisms
     */
    void logChanges() noexcept override;

private:
    // Dependencies
    ClassDiagramManager *classDiagramManager;
    SceneUpdateObservable *sceneUpdateObservable;

    // Containers
    std::vector<CustomScene *> scenes;

    // Settings
    const int minToolboxWidth = 200;
    const int toolboxItemSize = 70;

    // Widgets
    QToolBar *taskBar;
    QToolBar *diagramTabs;
    QToolBox *toolBox;
    CustomScene *currentScene;
    QGraphicsView *diagramView;
    QWidget *centerWidget;

    // Tool items
    QToolButton *aggregationToolItem;
    QToolButton *associationToolItem;
    QToolButton *compositionToolItem;
    QToolButton *generalisationToolItem;
    QToolButton *directedAssociationToolItem;
    QToolButton *realizationToolItem;
    QToolButton *classShapeToolItem;
    QToolButton *removeSelectedToolItem;

    // Setup
    /**
     * Initializes components - creates a new instances of primary attributes.
     */
    void initializeComponents();
    /**
     * Arranges controls in layout and sets window properties.
     */
    void setMainWindow();
    /**
     * Creates top taskbar (open, save, ...) and bottom taskbar with tabs for switching diagrams
     */
    void setTaskBars();
    /**
     * Places buttons to a layout and creates a toolbar with the layout.
     *
     * @param icon Icon that should be placed in button.
     * @param labelString String that will be under the icon.
     * @return QWidget representing a toolbar.
     */
    QWidget *prepareToolItem(const QIcon &icon, const QString &labelString, QToolButton *newToolButton);
    /**
     * Creates tabs for diagrams.
     *
     * @param label QString of text which will be written on a tab
     * @return QWidget representing a diagram tab manager
     */
    QWidget *prepareDiagramTab(const QString &label);
    /**
     * Places all demanded Widgets into a toolbar.
     */
    void setToolBox();
    /**
     * Connects all signals and slots
     */
    void connectComponents();
private slots:
    // Tool box items' actions
    void addClassNode();
    void removeSelectedClassNodes();
    void associationSelected();
    void compositionSelected();
    void aggregationSelected();
    void generalisationSelected();
    void directedAssociationSelected();
    void realizationSelected();

    // Top toolbar buttons' actions
    /**
     * Slot for handling click action on "Save" button
     */
    void openButtonClicked();
    /**
     * Slot for handling click action on "Save" button
     */
    void saveButtonClicked();
    /**
     * Slot for handling click action on "Undo" button
     */
    void saveAsButtonClicked();
    /**
     * Slot for handling click action on "Undo" button
     */
    void undoButtonClicked();
    /**
     * Slot for handling click action on "Redo" button
     */
    void redoButtonClicked();
};

#endif // CLASS_DIAGRAM_WINDOW_H
