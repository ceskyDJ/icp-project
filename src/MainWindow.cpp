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

/**
 * Class constructor
 *
 * @par Initialiezes components and prepare all QWidgets and controls.
 *
 * @param classDiagramManager Class diagram manage (dependency)
 * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
 */
MainWindow::MainWindow( // NOLINT(cppcoreguidelines-pro-type-member-init)
    ClassDiagramManager *classDiagramManager,
    SceneUpdateObservable *sceneUpdateObservable
): classDiagramManager{classDiagramManager}, sceneUpdateObservable{sceneUpdateObservable}
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
    currentScene = new ClassDiagramScene{this, classDiagramManager, sceneUpdateObservable};
    diagramView = new QGraphicsView(currentScene);

    taskBar = addToolBar("TaskBar");
    diagramTabs = new QToolBar();
    toolBox = new QToolBox;

    aggregationToolItem = new QToolButton;
    associationToolItem = new QToolButton;
    compositionToolItem = new QToolButton;
    generalisationToolItem = new QToolButton;
    realizationToolItem = new QToolButton;
    directedAssociationToolItem = new QToolButton;
    classShapeToolItem = new QToolButton;
    removeSelectedToolItem = new QToolButton;
}

/**
 * Arranges controls in layout and sets window properties.
 */
void MainWindow::setMainWindow()
{
    auto *windowLayout = new QGridLayout;
    auto *modellingLayout = new QGridLayout;

    modellingLayout->addWidget(toolBox,0,0);
    modellingLayout->addWidget(diagramView, 0, 1);

    auto *modellingSpace = new QWidget;
    modellingSpace->setLayout(modellingLayout);

    windowLayout->addWidget(modellingSpace,0,0);
    windowLayout->addWidget(diagramTabs,1,0);

    centerWidget = new QWidget;
    centerWidget->setLayout(windowLayout);

    setCentralWidget(centerWidget);
    this->setMinimumSize(800,600);
    this->setWindowTitle("UML Class Creator");
}

/**
 * Creates top taskbar (open, save, ...) and bottom taskbar with tabs for switching diagrams
 */
void MainWindow::setTaskBars()
{
    taskBar->setMovable(false);
    taskBar->addAction("Open", this, &MainWindow::openButtonClicked);
    taskBar->addAction("Save", this, &MainWindow::saveButtonClicked);
    taskBar->addAction("Save as...", this, &MainWindow::saveAsButtonClicked);
    taskBar->addAction("Undo", this, &MainWindow::undoButtonClicked);
    taskBar->addAction("Redo", this, &MainWindow::redoButtonClicked);


    // TODO: Connect to scene
    diagramTabs->addWidget(prepareDiagramTab("Unnamed class diagram"));
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
 * Creates tabs for diagrams.
 *
 * @param label QString of text which will be written on a tab
 * @return QWidget representing a diagram tab manager
 */
QWidget *MainWindow::prepareDiagramTab(const QString &label)
{
    static QIcon icon = QIcon(":/closeCross.png");
    auto newTab = new QWidget;
    auto picture = new QPushButton(icon,"");

    auto actionLayout = new QGridLayout();
    actionLayout->addWidget(new QPushButton(label),0,0);
    actionLayout->addWidget(picture,0,1);
    newTab->setLayout(actionLayout);

    return newTab;
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

    QWidget *aggregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Agregation", aggregationToolItem);
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

/**
 * Slot for handling click action on "Save" button
 */
void MainWindow::openButtonClicked()
{
    // TODO: Class diagrams --> .cls.xml, sequence diagrams --> .seq.xml
    // TODO: check if the filter is working
    QString file = QFileDialog::getOpenFileName(
        this,
        "Choose diagram to open",
        "",
        "Class diagrams (*.cls.xml);;Sequence diagrams (*.seq.xml)",
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    // TODO: for diagram type without option to open multiple diagrams stop processing here
    if (!currentScene->items().isEmpty() && !currentScene->isSaved()) {
        auto clickedButton = QMessageBox::question(
                this,
                "Diagram opening error",
                "You are trying to open new diagram before saving the edited one. Are you sure to continue?"
                " Canvas content will be replaced with loaded diagram."
        );

        if (clickedButton == QMessageBox::No) {
            // Stop here, nothing will be loaded
            return;
        }
    }

    // Remember source file
    currentScene->setTargetFile(file.toStdString());

    currentScene->loadFromFile();
}

/**
 * Slot for handling click action on "Save" button
 */
void MainWindow::saveButtonClicked() // NOLINT(misc-no-recursion)
{
    // Target file must be selected
    if (currentScene->getTargetFile().empty()) {
        QMessageBox::warning(this, "Diagram saving error", "Edited diagram wasn't loaded from"
            " any file and target file hasn't been selected. You need to select target file first.");

        // Simulate clicking on "Save as..." button, user must select the target file
        saveAsButtonClicked();

        return;
    }

    currentScene->saveToFile();
}

/**
 * Slot for handling click action on "Undo" button
 */
void MainWindow::saveAsButtonClicked() // NOLINT(misc-no-recursion)
{
    std::string currentTargetFile{currentScene->getTargetFile()};

    // TODO: Class diagrams --> .cls.xml, sequence diagrams --> .seq.xml
    // Prompt user to select the target file
    QString file = QFileDialog::getSaveFileName(
        this,
        "Choose target file for saving diagram",
        currentTargetFile.empty() ? "new-diagram.xml" : QString::fromStdString(currentTargetFile),
        "XML files (*.xml)",
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    if (file.isEmpty()) {
        // Dialog has been canceled
        return;
    }

    // Update target file
    currentScene->setTargetFile(file.toStdString());

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
