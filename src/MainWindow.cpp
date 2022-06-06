/**
 * @file MainWindow.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "MainWindow.h"
#include "InvalidDataStorageException.h"
#include "ClassNodeEmitter.h"
#include "ClassDiagramScene.h"
#include "SequenceDiagramScene.h"

/**
 * Class constructor
 *
 * @par Initializes components and prepare all QWidgets and controls.
 *
 * @param classDiagramManager Class diagram manager (dependency)
 * @param sequenceDiagramManager Sequence diagram manager (dependency)
 * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
 */
MainWindow::MainWindow( // NOLINT(cppcoreguidelines-pro-type-member-init)
    ClassDiagramManager *classDiagramManager,
    SequenceDiagramManager *sequenceDiagramManager,
    SceneUpdateObservable *sceneUpdateObservable
): classDiagramManager{classDiagramManager}, sequenceDiagramManager{sequenceDiagramManager},
        sceneUpdateObservable{sceneUpdateObservable}
{
    // Register this observer for scene updates
    sceneUpdateObservable->registerObserver(this);

    initializeComponents();
    connectComponents();
    setToolBox();
    setTaskBars();
    setMainWindow();
}

/**
 * Logs scene changes for saving and undo/redo mechanisms
 */
void MainWindow::logChanges() noexcept
{
    currentScene->logChanges();
}

/**
 * Initializes components - creates a new instances of primary attributes.
 */
void MainWindow::initializeComponents()
{
    // Taskbars and tool boxes
    taskBar = addToolBar("TaskBar");
    tabBar = new QToolBar{};
    toolBox = new QToolBox{};
    sceneView = new QGraphicsView{};

    // Class diagram tool items
    aggregationToolItem = new QToolButton;
    associationToolItem = new QToolButton;
    compositionToolItem = new QToolButton;
    generalisationToolItem = new QToolButton;
    realizationToolItem = new QToolButton;
    directedAssociationToolItem = new QToolButton;
    classShapeToolItem = new QToolButton;
    removeSelectedToolItem = new QToolButton;

    // Drawing scene
    auto sceneData = createScene(SceneType::ClassDiagram, "", false);
    setActiveTab(std::get<1>(sceneData));
}

/**
 * Arranges controls in layout and sets window properties.
 */
void MainWindow::setMainWindow()
{
    auto *windowLayout = new QGridLayout;
    auto *modellingLayout = new QGridLayout;

    modellingLayout->addWidget(toolBox,0,0);
    modellingLayout->addWidget(sceneView, 0, 1);

    auto *modellingSpace = new QWidget;
    modellingSpace->setLayout(modellingLayout);

    windowLayout->addWidget(modellingSpace,0,0);
    windowLayout->addWidget(tabBar, 1, 0);

    centerWidget = new QWidget;
    centerWidget->setLayout(windowLayout);

    setCentralWidget(centerWidget);
    setMinimumSize(800,600);
}

/**
 * Creates top taskbar (open, save, ...) and bottom taskbar with tabs for switching diagrams
 */
void MainWindow::setTaskBars()
{
    taskBar->setMovable(false);
    taskBar->addAction("New", this, &MainWindow::newButtonClicked);
    taskBar->addAction("Open", this, &MainWindow::openButtonClicked);
    taskBar->addAction("Save", this, &MainWindow::saveButtonClicked);
    taskBar->addAction("Save as...", this, &MainWindow::saveAsButtonClicked);
    taskBar->addAction("Undo", this, &MainWindow::undoButtonClicked);
    taskBar->addAction("Redo", this, &MainWindow::redoButtonClicked);
}

/**
 * Places buttons to a layout and creates a toolbar with the layout.
 *
 * @param icon Icon that should be placed in button.
 * @param labelString String that will be under the icon.
 * @return QWidget representing a toolbar.
 */
QWidget *MainWindow::prepareToolItem(const QIcon &icon, const QString &labelString, QToolButton *newToolButton)
{
    newToolButton->setIcon(icon);
    newToolButton->setIconSize(QSize(toolboxItemSize, toolboxItemSize));
    newToolButton->setMaximumSize(toolboxItemSize, toolboxItemSize);
    newToolButton->setMinimumSize(toolboxItemSize, toolboxItemSize);

    auto toolboxItemLayout = new QVBoxLayout();
    toolboxItemLayout->addWidget(newToolButton);
    auto label = new QLabel(labelString);
    toolboxItemLayout->addWidget(label);
    toolboxItemLayout->setAlignment(newToolButton, Qt::AlignHCenter);
    toolboxItemLayout->setAlignment(label, Qt::AlignHCenter);

    auto toolboxItem = new QWidget;
    toolboxItem->setLayout(toolboxItemLayout);
    return toolboxItem;
}

/**
 * Places all demanded Widgets into a toolbar.
 */
void MainWindow::setToolBox()
{
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(minToolboxWidth);
    auto toolboxItems = new QGroupBox;
    auto toolboxLayout = new QGridLayout;

    QWidget *aggregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Aggregation", aggregationToolItem);
    QWidget *fellowshipLineWidget = prepareToolItem(QIcon{":/coLine.png"}, "Composition", compositionToolItem);
    QWidget *compositionLineWidget = prepareToolItem(QIcon{":/feLine.png"}, "Association", associationToolItem);
    QWidget *generalisationLineWidget = prepareToolItem(QIcon{":/geLine.png"}, "Generalization", generalisationToolItem);
    QWidget *realizationLineWidget = prepareToolItem(QIcon{":/realization.png"}, "Realization", realizationToolItem);
    QWidget *directedLineWidget = prepareToolItem(QIcon{":/directedAssociation.png"},
                                                  "Directed association", directedAssociationToolItem);
    QWidget *classShapeWidget = prepareToolItem(QIcon{":/classShape.png"}, "Class node", classShapeToolItem);
    QWidget *removeSelectedWidget = prepareToolItem(QIcon{":/closeCross.png"}, "Remove selected", removeSelectedToolItem);

    toolboxLayout->addWidget(aggregationLineWidget, 0, 0);
    toolboxLayout->addWidget(fellowshipLineWidget, 1, 0);
    toolboxLayout->addWidget(compositionLineWidget, 0, 1);
    toolboxLayout->addWidget(generalisationLineWidget, 1, 1);
    toolboxLayout->addWidget(realizationLineWidget, 2, 0);
    toolboxLayout->addWidget(directedLineWidget, 2, 1);
    toolboxLayout->addWidget(classShapeWidget, 3, 0);
    toolboxLayout->addWidget(removeSelectedWidget, 3, 1);

    toolboxItems->setLayout(toolboxLayout);
    toolboxItems->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    toolBox->addItem(toolboxItems, "Class diagram elements");
}

/**
 * Connects all signals and slots
 */
void MainWindow::connectComponents()
{
    // Class diagrams
    connect(classShapeToolItem,  &QToolButton::pressed, this, &MainWindow::addClassNode);
    connect(removeSelectedToolItem,  &QToolButton::pressed, this, &MainWindow::removeSelectedClassNodes);
    connect(associationToolItem, &QToolButton::pressed, this, &MainWindow::associationSelected);
    connect(compositionToolItem, &QToolButton::pressed, this, &MainWindow::compositionSelected);
    connect(aggregationToolItem, &QToolButton::pressed, this, &MainWindow::aggregationSelected);
    connect(generalisationToolItem, &QToolButton::pressed, this, &MainWindow::generalisationSelected);
    connect(directedAssociationToolItem, &QToolButton::pressed, this, &MainWindow::directedAssociationSelected);
    connect(realizationToolItem, &QToolButton::pressed, this, &MainWindow::realizationSelected);
}

/**
 * Creates a new scene
 *
 * @param type Scene type
 * @param name Scene name (optional)
 * @param closeable Could the scene be closed? (optional, default: true)
 * @return Pointer to created scene and pointer to corresponding tab
 */
std::tuple<CustomScene *, TabWidget *> MainWindow::createScene(
    const SceneType &type,
    const QString &name,
    bool closeable
) {
    // Numbering for unique names
    static unsigned int classDiagramNumber = 1;
    static unsigned int sequenceDiagramNumber = 1;

    // Create new scene instance
    CustomScene *newScene{};
    QString defaultName{};
    switch (type) {
        case SceneType::ClassDiagram:
            newScene = new ClassDiagramScene{this, classDiagramManager, sceneUpdateObservable};
            defaultName = "New class diagram " + QString::number(classDiagramNumber++);
            break;
        case SceneType::SequenceDiagram:
            newScene = new SequenceDiagramScene{this, sequenceDiagramManager, sceneUpdateObservable};
            defaultName = "New sequence diagram " + QString::number(sequenceDiagramNumber++);
            break;
    }

    scenes.push_back(newScene);

    // Create tab for scene
    auto newTab = new TabWidget{(name.isEmpty() ? defaultName : name), newScene, closeable};
    tabs.push_back(newTab);

    QAction *action = tabBar->addWidget(newTab);
    tabBarActions.insert({newTab, action});

    // Connect signals from tab buttons
    connect(newTab->getTabButton(), &QPushButton::pressed, this, &MainWindow::selectTab);
    connect(newTab->getCloseButton(), &QPushButton::pressed, this, &MainWindow::closeTab);

    return {newScene, newTab};
}

// Manipulators ------------------------------------------------------------------------------------------- Manipulators
/**
 * Switch active tab to specified one
 *
 * @par Of course switches corresponding scene, too.
 *
 * @param tab Tab to set as active
 */
void MainWindow::setActiveTab(TabWidget *tab)
{
    // Switch scene
    currentScene = tab->getScene();
    sceneView->setScene(currentScene);

    // Switch tab
    for (auto item: tabs) {
        item->setActive(false);
    }
    tab->setActive(true);

    currentTab = tab;

    updateTab(tab);
}

/**
 * Updates specified tab
 *
 * @par Normally tab's state and displayed label are updated.
 * If the tab is active, window title is updated, too.
 *
 * @param tab Tab to be updates
 */
void MainWindow::updateTab(TabWidget *tab)
{
    // Update tab's state
    tab->updateState();

    // Update main window title
    if (tab == currentTab) {
        this->setWindowTitle(mainWindowTitle + " - " + tab->getLabel());
    }

    update();
}

// Helper methods --------------------------------------------------------------------------------------- Helper methods
/**
 * Finds and returns class diagram scene from opened scenes
 *
 * @return Pointer to class diagram scene or nullptr when there is no class diagram scene
 */
ClassDiagramScene *MainWindow::getClassDiagramScene()
{
    for (auto item: scenes) {
        if (typeid(*item) == typeid(ClassDiagramScene)) {
            auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(item);

            return classDiagramScene;
        }
    }

    throw std::logic_error{"There is no class diagram scene"};
}

/**
 * Checks if specified file is used by some scene
 *
 * @param fileName Name of the file to check (its full path)
 * @return Is the file used by some scene?
 */
bool MainWindow::isFileUsedBySomeScene(QString &fileName)
{
    for (const auto item: scenes) {
        if (item->getTargetFile() == fileName) {
            return true;
        }
    }

    return false;
}

// Slots ========================================================================================================= Slots
// Tool box items' actions --------------------------------------------------------------------- Tool box items' actions
/**
 * Slot for handling click on button for adding new class node
 */
void MainWindow::addClassNode()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->addClassNode();
}

/**
 * Slot is invoked when class node remove button was pressed.
 */
void MainWindow::removeSelectedClassNodes()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->removeSelectedNodes();
}

/**
 * Slot for handling click on button for selecting association relationship
 */
void MainWindow::associationSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareUndirectedAssociation();
}

/**
 * Slot for handling click on button for selecting composition relationship
 */
void MainWindow::compositionSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareComposition();
}

/**
 * Slot for handling click on button for selecting aggregation relationship
 */
void MainWindow::aggregationSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareAggregation();
}

/**
 * Slot for handling click on button for selecting generalization relationship
 */
void MainWindow::generalisationSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareGeneralisation();
}

/**
 * Slot for handling click on button for selecting directed association relationship
 */
void MainWindow::directedAssociationSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareDirectedAssociation();
}

/**
 * Slot for handling click on button for selecting realization relationship
 */
void MainWindow::realizationSelected()
{
    if (typeid(*currentScene) != typeid(ClassDiagramScene)) {
        return;
    }

    auto classDiagramScene = dynamic_cast<ClassDiagramScene *>(currentScene);
    classDiagramScene->prepareRealization();
}

// Top toolbar buttons' actions ----------------------------------------------------------- Top toolbar buttons' actions
/**
 * Slot for handling click action on "New" button
 */
void MainWindow::newButtonClicked()
{
    // Create new scene and tab for sequence diagram
    auto sceneData = createScene(SceneType::SequenceDiagram);
    setActiveTab(std::get<1>(sceneData));
}

/**
 * Slot for handling click action on "Save" button
 */
void MainWindow::openButtonClicked()
{
    QString file = QFileDialog::getOpenFileName(
        this,
        "Choose diagram to open",
        "",
        "Class diagrams (*.cls.xml);;Sequence diagrams (*.seq.xml)",
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    // Get short file name (end of path)
    QFileInfo fileInfo{file};
    QString shortFileName{fileInfo.fileName()};

    if (file.endsWith(".cls.xml")) {
        // Class diagram
        ClassDiagramScene *classDiagramScene = getClassDiagramScene();

        if (!classDiagramScene->items().isEmpty() && !classDiagramScene->isSaved()) {
            auto clickedButton = QMessageBox::question(
                this,
                "Unsaved class diagram",
                "You are trying to open new class diagram before saving the edited one. Are you sure to"
                " continue? Canvas content will be replaced with loaded diagram."
            );

            if (clickedButton == QMessageBox::No) {
                // Stop here, nothing will be loaded
                return;
            }
        }

        // Switch to class diagram scene
        // Class diagram is always in the first tab
        tabs[0]->setLabel(shortFileName);
        setActiveTab(tabs[0]);
    } else if (file.endsWith(".seq.xml")) {
        // Sequence diagram

        // One file can be used only in one scene
        if (isFileUsedBySomeScene(file)) {
            QMessageBox::critical(
                    this,
                    "Diagram opening error",
                    "Selected file is already used by some of diagrams you are editing. Select different file or close"
                    " edited diagram from the file before opening again."
            );

            // Stop here, nothing will be loaded
            return;
        }

        // Add new scene for diagram to be loaded and switch to it
        auto sceneData = createScene(SceneType::SequenceDiagram, shortFileName);
        setActiveTab(std::get<1>(sceneData));
    } else {
        // File with bad extension --> stop processing
        QMessageBox::critical(this, "Diagram opening error", "Selected file has bad extension.");

        return;
    }

    // Remember source file
    currentScene->setTargetFile(file);

    // Load diagram from file
    currentScene->loadFromFile();

    // Update tab
    updateTab(currentTab);
}

/**
 * Slot for handling click action on "Save" button
 */
void MainWindow::saveButtonClicked() // NOLINT(misc-no-recursion)
{
    // Target file must be selected
    if (currentScene->getTargetFile().isEmpty()) {
        QMessageBox::warning(this, "Diagram saving error", "Edited diagram wasn't loaded from"
            " any file and target file hasn't been selected. You need to select target file first.");

        // Simulate clicking on "Save as..." button, user must select the target file
        saveAsButtonClicked();

        return;
    }

    // Save diagram to file
    currentScene->saveToFile();

    // Update tab
    updateTab(currentTab);
}

/**
 * Slot for handling click action on "Undo" button
 */
void MainWindow::saveAsButtonClicked() // NOLINT(misc-no-recursion)
{
    QString currentTargetFile{currentScene->getTargetFile()};

    // Choose filter by diagram type
    QString filter{};
    QString defaultFileName{};
    if (typeid(*currentScene) == typeid(ClassDiagramScene)) {
        // Class diagram
        filter = "Class diagrams (*.cls.xml)";
        defaultFileName = "new-class-diagram.cls.xml";
    } else {
        // Sequence diagram
        filter = "Sequence diagrams (*.seq.xml)";
        defaultFileName = "new-sequence-diagram.seq.xml";
    }

    // Prompt user to select the target file
    QString file = QFileDialog::getSaveFileName(
        this,
        "Choose target file for saving diagram",
        currentTargetFile.isEmpty() ? defaultFileName : currentTargetFile,
        filter,
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    if (file.isEmpty()) {
        // Dialog has been canceled
        return;
    }

    // Check for extension validity
    if (typeid(*currentScene) == typeid(ClassDiagramScene) && !file.endsWith(".cls.xml")) {
        // Class diagram
        QMessageBox::critical(
            this,
            "Class diagram saving error",
            "Your file has invalid extension. Class diagrams must be saved with name like: \"*.cls.xml\" (without"
            " quotes)."
        );

        // Stop here, nothing will be saved
        return;
    } else if(typeid(*currentScene) == typeid(SequenceDiagramScene) && !file.endsWith(".seq.xml")) {
        // Sequence diagram
        QMessageBox::critical(
            this,
            "Sequence diagram saving error",
            "Your file has invalid extension. Sequence diagrams must be saved with name like: \"*.seq.xml\""
            " (without quotes)."
        );

        // Stop here, nothing will be saved
        return;
    }

    // File used by some scene cannot be rewritten
    if (isFileUsedBySomeScene(file) && currentTargetFile != file) {
        QMessageBox::critical(
            this,
            "Diagram saving error",
            "Selected file is used as a target for saving one of edited diagrams. Choose different file for saving"
            " the diagram, please."
            );

        // Stop here, nothing will be saved
        return;
    }

    // Update target file
    currentScene->setTargetFile(file);

    // Get short file name (end of path)
    QFileInfo fileInfo{file};
    QString shortFileName{fileInfo.fileName()};

    // Update tab label
    currentTab->setLabel(shortFileName);

    // Now just save diagram into selected file
    saveButtonClicked();
}

/**
 * Slot for handling click action on "Undo" button
 */
void MainWindow::undoButtonClicked()
{
    currentScene->undoLastChange();
}

/**
 * Slot for handling click action on "Redo" button
 */
void MainWindow::redoButtonClicked()
{
    currentScene->redoRevertedChange();
}

// Bottom tab bar tab's actions ----------------------------------------------------------- Bottom tab bar tab's actions
/**
 * Slot for handling click action on some select tab button
 */
void MainWindow::selectTab()
{
    auto button = qobject_cast<QPushButton *>(sender());
    auto tab = qobject_cast<TabWidget *>(button->parentWidget());

    setActiveTab(tab);
}

/**
 * Slot for handling click action on some close tab button
 */
void MainWindow::closeTab()
{
    auto button = qobject_cast<QPushButton *>(sender());
    auto tab = qobject_cast<TabWidget *>(button->parentWidget());
    CustomScene *scene = tab->getScene();

    // Check for closing unsaved scene
    if (!scene->items().empty() && !scene->isSaved()) {
        auto clickedButton = QMessageBox::question(
                this,
                "Unsaved class diagram",
                "You are trying to close diagram before saving it. Are you sure to continue? All your unsaved"
                " changes will be lost."
        );

        if (clickedButton == QMessageBox::No) {
            // Stop here, tab won't be closed
            return;
        }
    }

    // Switch to class diagram tab when active tab will be closed
    if (tab == currentTab) {
        setActiveTab(tabs[0]);
    }

    // Remove tab from tab bar
    tabBar->removeAction(tabBarActions.find(tab)->second);
    tabBarActions.erase(tab);

    // Remove tab from the list and memory
    for (auto iterator = tabs.begin(); iterator < tabs.end(); iterator++) {
        if (*iterator == tab) {
            tabs.erase(iterator);

            delete tab;
            break;
        }
    }

    // Remove scene from existing scenes
    for (auto iterator = scenes.begin(); iterator < scenes.end(); iterator++) {
        if (*iterator == scene) {
            scenes.erase(iterator);

            delete scene;
            return;
        }
    }
}
