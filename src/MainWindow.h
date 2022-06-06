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
#include "ClassDiagramScene.h"
#include "SequenceDiagramManager.h"
#include "TabWidget.h"

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
     * @par Initializes components and prepare all QWidgets and controls.
     *
     * @param classDiagramManager Class diagram manager (dependency)
     * @param sequenceDiagramManager Sequence diagram manager (dependency)
     * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
     */
    MainWindow(
        ClassDiagramManager *classDiagramManager,
        SequenceDiagramManager *sequenceDiagramManager,
        SceneUpdateObservable *sceneUpdateObservable
   );

    /**
     * Logs scene changes for saving and undo/redo mechanisms
     */
    void logChanges() noexcept override;

private:
    // Dependencies
    /**
     * Class diagram manager (for backend operations)
     */
    ClassDiagramManager *classDiagramManager;
    /**
     * Sequence diagram manager (for backend operations)
     */
    SequenceDiagramManager *sequenceDiagramManager;
    /**
     * Observable for distributing information about scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;

    // Type definitions
    /**
     * @typedef Type of scene (what implement class of CustomScene to choose)
     */
    enum class SceneType {ClassDiagram, SequenceDiagram};

    // Containers
    /**
     * Active (loaded/created) scenes
     */
    std::vector<CustomScene *> scenes;
    /**
     * Tabs in bottom tab bar
     */
    std::vector<TabWidget *> tabs;

    // Settings
    /**
     * Title of main window
     */
    const QString mainWindowTitle = "UML Class Creator";
    /**
     * Minimum width of toolbox
     */
    const int minToolboxWidth = 200;
    /**
     * Static size of toolbox item
     */
    const int toolboxItemSize = 70;

    // Widgets
    /**
     * Top task bar menu
     */
    QToolBar *taskBar;
    /**
     * Bottom tab bar
     */
    QToolBar *diagramTabs;
    /**
     * Left toolbox with buttons for modifying scene
     */
    QToolBox *toolBox;
    /**
     * Widget wrapper for current scene (for displaying its content)
     */
    QGraphicsView *sceneView;
    /**
     * TODO: add doc comment
     */
    QWidget *centerWidget;
    /**
     * Currently edited scene
     */
    CustomScene *currentScene;
    /**
     * Currently opened tab
     */
    TabWidget *currentTab;

    // Tool items
    /**
     * Button for choosing aggregation relationship for creation process
     */
    QToolButton *aggregationToolItem;
    /**
     * Button for choosing undirected association relationship for creation process
     */
    QToolButton *associationToolItem;
    /**
     * Button for choosing composition relationship for creation process
     */
    QToolButton *compositionToolItem;
    /**
     * Button for choosing generalization relationship for creation process
     */
    QToolButton *generalisationToolItem;
    /**
     * Button for choosing directed association relationship for creation process
     */
    QToolButton *directedAssociationToolItem;
    /**
     * Button for choosing realization relationship for creation process
     */
    QToolButton *realizationToolItem;
    /**
     * Button for creating new class node
     */
    QToolButton *classShapeToolItem;
    /**
     * Button for removing class nodes
     */
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
     * Places all demanded Widgets into a toolbar.
     */
    void setToolBox();
    /**
     * Connects all signals and slots
     */
    void connectComponents();
    /**
     * Creates a new scene
     *
     * @param type Scene type
     * @param name Scene name (optional)
     * @param closeable Could the scene be closed? (optional, default: true)
     * @return Pointer to created scene and pointer to corresponding tab
     */
    std::tuple<CustomScene *, TabWidget *> createScene(
        const SceneType &type,
        const QString &name = "",
        bool closeable = true
   );

    // Manipulators
    /**
     * Switch active tab to specified one
     *
     * @par Of course switches corresponding scene, too.
     *
     * @param tab Tab to set as active
     */
    void setActiveTab(TabWidget *tab);

    /**
     * Updates specified tab
     *
     * @par Normally tab's state and displayed label are updated.
     * If the tab is active, window title is updated, too.
     *
     * @param tab Tab to be updates
     */
    void updateTab(TabWidget *tab);

    // Helper methods
    /**
     * Finds and returns class diagram scene from opened scenes
     *
     * @return Pointer to class diagram scene
     */
    ClassDiagramScene *getClassDiagramScene();
    /**
     * Checks if specified file is used by some scene
     *
     * @param fileName Name of the file to check (its full path)
     * @return Is the file used by some scene?
     */
    bool isFileUsedBySomeScene(QString &fileName);
private slots:
    // Tool box items' actions
    /**
     * Slot for handling click on button for adding new class node
     */
    void addClassNode();
    /**
     * Slot is invoked when class node remove button was pressed.
     */
    void removeSelectedClassNodes();
    /**
     * Slot for handling click on button for selecting association relationship
     */
    void associationSelected();
    /**
     * Slot for handling click on button for selecting composition relationship
     */
    void compositionSelected();
    /**
     * Slot for handling click on button for selecting aggregation relationship
     */
    void aggregationSelected();
    /**
     * Slot for handling click on button for selecting generalization relationship
     */
    void generalisationSelected();
    /**
     * Slot for handling click on button for selecting directed association relationship
     */
    void directedAssociationSelected();
    /**
     * Slot for handling click on button for selecting realization relationship
     */
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

    // Bottom tab bar tab's actions
    /**
     * Slot for handling click action on some select tab button
     */
    void selectTab();
    /**
     * Slot for handling click action on some close tab button
     */
    void closeTab();
};

#endif // CLASS_DIAGRAM_WINDOW_H
