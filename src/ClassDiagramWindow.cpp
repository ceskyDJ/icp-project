/**
 * @file ClassDiagramWindow.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include <QPushButton>
#include <QResource>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include "ClassDiagramWindow.h"
#include "ClassAttribute.h"
#include "Aggregation.h"
#include "Composition.h"
#include "DirectedAssociation.h"
#include "Generalization.h"
#include "Realization.h"
#include "UndirectedAssociation.h"
#include "InvalidDataStorageException.h"
#include "InvalidInputDataException.h"
#include "ClassNodeEmitter.h"

/**
 * ClassDiagramWindow::ClassDiagramWindow Initialiezes components and prepare all QWidgets and controls.
 *
 * @param classDiagramManager Pointer to class diagram manager (dependency)
 */
ClassDiagramWindow::ClassDiagramWindow(
    ClassDiagramManager *classDiagramManager,
    SceneUpdateObservable *sceneUpdateObservable
): classDiagramManager{classDiagramManager}, sceneUpdateObservable{sceneUpdateObservable}, storedClasses{},
    storedRelationships{}
{
    // Register this observer for scene updates
    sceneUpdateObservable->registerObserver(this);

    newLine = nullptr;
    currentState = state::none;

    initializeComponents();
    connectComponents();
    setTooBox();
    setTaskBars();
    setMainWindow();
}

/**
 * ClassDiagramWindow::initializeComponents Initializes components - creates a new instances of primary attributes.
 */
void ClassDiagramWindow::initializeComponents()
{
    newLine = nullptr;
    classDiagramScene = new QGraphicsScene();
    classDiagramView = new QGraphicsView(classDiagramScene);

    taskBar = addToolBar("TaskBar");
    diagramTabs = new QToolBar();
    toolBox = new QToolBox;

    agregationToolItem = new QToolButton;
    associationToolItem = new QToolButton;
    compositionToolItem = new QToolButton;
    generalisationToolItem = new QToolButton;
    realizationToolItem = new QToolButton;
    directedAssociationToolItem = new QToolButton;
    classShapeToolItem     = new QToolButton;
    removeSelectedToolItem = new QToolButton;
}

/**
 * ClassDiagramWindow::setMainWindow Arranges controls in layout and sets window properties.
 */
void ClassDiagramWindow::setMainWindow()
{
    QGridLayout *windowLayout = new QGridLayout;
    QGridLayout *modellingLayout = new QGridLayout;

    modellingLayout->addWidget(toolBox,0,0);
    modellingLayout->addWidget(classDiagramView,0,1);

    QWidget *modellingSpace = new QWidget;
    modellingSpace->setLayout(modellingLayout);

    windowLayout->addWidget(modellingSpace,0,0);
    windowLayout->addWidget(diagramTabs,1,0);

    classDiagramCenterWidget = new QWidget;
    classDiagramCenterWidget->setLayout(windowLayout);

    setCentralWidget(classDiagramCenterWidget);
    this->setMinimumSize(800,600);
    this->setWindowTitle("UML Class Creator");
}

/**
 * ClassDiagramWindow::setTaskBars Sets taskbar (task as open, save) and create a place for sequence diagrams.
 */
void ClassDiagramWindow::setTaskBars()
{
    taskBar->setMovable(false);
    taskBar->addAction("Open", this, &ClassDiagramWindow::openButtonClicked);
    taskBar->addAction("Save", this, &ClassDiagramWindow::saveButtonClicked);
    taskBar->addAction("Save as...", this, &ClassDiagramWindow::saveAsButtonClicked);
    taskBar->addAction("Undo", this, &ClassDiagramWindow::undoButtonClicked);
    taskBar->addAction("Redo", this, &ClassDiagramWindow::redoButtonClicked);


    diagramTabs->addWidget(prepareSequencDiagramTab("Třídní diagram"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 1"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 2"));
}

/**
 * ClassDiagramWindow::prepareToolItem Places buttons to a layout and creates a toolbar with the layout.
 *
 * @param icon Icon that should be placed in button.
 * @param labelString String that will be under the icon.
 * @return QWidget representing a toolbar.
 */
QWidget *ClassDiagramWindow::prepareToolItem(QIcon icon, QString labelString, QToolButton *newToolButton)
{
    newToolButton->setIcon(icon);
    newToolButton->setIconSize(QSize(toolboxItemSize, toolboxItemSize));
    newToolButton->setMaximumSize(toolboxItemSize, toolboxItemSize);
    newToolButton->setMinimumSize(toolboxItemSize, toolboxItemSize);

    QVBoxLayout *toolboxItemLayout = new QVBoxLayout();
    toolboxItemLayout->addWidget(newToolButton);
    QLabel *label = new QLabel(labelString);
    toolboxItemLayout->addWidget(label);
    toolboxItemLayout->setAlignment(newToolButton, Qt::AlignHCenter);
    toolboxItemLayout->setAlignment(label, Qt::AlignHCenter);

    QWidget* toolboxItem = new QWidget;
    toolboxItem->setLayout(toolboxItemLayout);
    return toolboxItem;
}

/**
 * ClassDiagramWindow::prepareSequencDiagramTab Creates a tabs for sequence diagrams.
 *
 * @param label QString of text which will be written on a tab.
 * @return QWidget representig a diagram tab manager.
 */
QWidget *ClassDiagramWindow::prepareSequencDiagramTab(QString label)
{
    static QIcon icon = QIcon(":/closeCross.png");
    QWidget *newTab = new QWidget;
    QPushButton *picture = new QPushButton(icon,"");

    QGridLayout *actionLayout = new QGridLayout();
    actionLayout->addWidget(new QPushButton(label),0,0);
    actionLayout->addWidget(picture,0,1);
    newTab->setLayout(actionLayout);

    return newTab;
}

/**
 * ClassDiagramWindow::setTooBox Place all demanded Widgets into a toolar.
 */
void ClassDiagramWindow::setTooBox()
{
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(minToolboxWidth);
    QGroupBox *toolboxItems = new QGroupBox;
    QGridLayout *toolboxLayout = new QGridLayout;

    QWidget *agregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Agregation", agregationToolItem);
    QWidget *fellowshipLineWidget = prepareToolItem(QIcon{":/coLine.png"}, "Composition", compositionToolItem);
    QWidget *compositionLineWidget = prepareToolItem(QIcon{":/feLine.png"}, "Association", associationToolItem);
    QWidget *generalisationLineWidget = prepareToolItem(QIcon{":/geLine.png"}, "Generalization", generalisationToolItem);
    QWidget *realizationLineWidget = prepareToolItem(QIcon{":/realization.png"}, "Realization", realizationToolItem);
    QIcon aaa = QIcon{":/realization.png"};
    (void)aaa;
    QWidget *directedLineWidget = prepareToolItem(QIcon{":/directedAssociation.png"},
                                                  "Directed association", directedAssociationToolItem);
    QWidget *classShapeWidget = prepareToolItem(QIcon{":/classShape.png"}, "Class node", classShapeToolItem);
    QWidget *removeSelectedWidget = prepareToolItem(QIcon{":/closeCross.png"}, "Remove selected", removeSelectedToolItem);

    toolboxLayout->addWidget(agregationLineWidget, 0, 0);
    toolboxLayout->addWidget(fellowshipLineWidget, 1, 0);
    toolboxLayout->addWidget(compositionLineWidget, 0, 1);
    toolboxLayout->addWidget(generalisationLineWidget, 1, 1);
    toolboxLayout->addWidget(realizationLineWidget, 2, 0);
    toolboxLayout->addWidget(directedLineWidget, 2, 1);
    toolboxLayout->addWidget(classShapeWidget, 3, 0);
    toolboxLayout->addWidget(removeSelectedWidget, 3, 1);

    toolboxItems->setLayout(toolboxLayout);
    toolboxItems->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    toolBox->addItem(toolboxItems, "Prvky třídního diagramu");
}

/**
 * Insert new claasNode into scene of class diagram Window.
 */
void ClassDiagramWindow::addClassNode()
{
    // Numbering and positioning unique names
    static unsigned int classNumber = 1;
    static const unsigned int nodeSpace = 50;

    // Create new class in class diagram
    Class *newClass = new Class{"New class " + std::to_string(classNumber++), std::make_tuple(0, 0)};

    classDiagram.addClass(newClass);

    // Create new GUI class node
    auto *newClassNode = new ClassNode(newClass, &storedClasses, sceneUpdateObservable);
    newClassNode->setPos((newClassNode->boundingRect().width() + nodeSpace) * (classNumber % 5),
                         (newClassNode->boundingRect().height() + nodeSpace) * (classNumber / 5));

    connect(&(newClassNode->emitter), &ClassNodeEmitter::nodePressed, this, &ClassDiagramWindow::nodePressed);
    classDiagramScene->addItem(newClassNode);
    storedClasses.insert({newClass->getName(), newClassNode});

    sceneUpdateObservable->sceneChanged();
}

/**
 * Removes all selected class nodes.
 */
void ClassDiagramWindow::removeClassNodes(QList<QGraphicsItem *> selectedItems)
{
    for (QGraphicsItem *item : selectedItems)
    {
        auto node = dynamic_cast<ClassNode *>(item);
        if(node) {
            removeClassNode(node);
        }
    }

    sceneUpdateObservable->sceneChanged();
}

/**
 * Removes single class node
 *
 * @param classNode Pointer to class node to remove
 */
void ClassDiagramWindow::removeClassNode(ClassNode *classNode)
{
    // One connection could have the same class node at its both ends
    // One line (connection) could be deleted only once, so these class nodes'
    // connections must be filtered for duplicates (set contains only unique items)
    QVector<Line *> allConnections = classNode->getConnections();
    QSet<Line *> uniqueConnections{allConnections.begin(), allConnections.end()};
    for(Line *connection: uniqueConnections) {
        // Delete corresponding relationship from class diagram and memory
        Relationship *relationship = storedRelationships.find(connection)->second;

        classDiagram.removeRelationship(relationship);
        delete relationship;

        // Delete from stored relationships
        storedRelationships.erase(connection);

        // Delete from scene and memory
        classDiagramScene->removeItem(connection);
        delete connection;
    }

    // Get corresponding class (entity)
    Class *classEntity = classNode->getClassEntity();

    // Delete from scene and memory
    classDiagramScene->removeItem(classNode);
    delete classNode;

    // Delete from stored classes
    storedClasses.erase(storedClasses.find(classEntity->getName()));

    // Delete class from diagram and memory
    classDiagram.removeClass(classEntity);
    delete classEntity;
}

/**
 * ClassDiagramWindow::connectComponents Connets all signals and slots
 */
void ClassDiagramWindow::connectComponents()
{
    connect(classShapeToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::addClassNode);
    connect(removeSelectedToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::removeSelected);
    connect(associationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::associationSelected);

    connect(compositionToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::compositionSelected);
    connect(agregationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::agregationSelected);
    connect(generalisationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::generalisationSelected);
    connect(directedAssociationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::directedAssociationSelected);
    connect(realizationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::realizationSelected);
}

/**
 * ClassDiagramWindow::setAllNodesColor Sets border color to all nodes and to nodeColor
 * @param color new node color
 */
void ClassDiagramWindow::setAllNodesColor(QColor color)
{
    nodeColor = color;
    QList<QGraphicsItem *> allNodes = classDiagramScene->items();
    for(QGraphicsItem *maybeNode : allNodes)
    {
        ClassNode *definetlyNode = dynamic_cast<ClassNode *>(maybeNode);
        if(definetlyNode)
            definetlyNode->setBorderColor(nodeColor);
    }
}

/**
 * To a newLine pointer creates line
 */
void ClassDiagramWindow::associationSelected()
{
    createNewLine(new AssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates composition line
 */
void ClassDiagramWindow::compositionSelected()
{
    createNewLine(new CompositionLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates agregation line
 */
void ClassDiagramWindow::agregationSelected()
{
    createNewLine(new AgregationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates generalisation line
 */
void ClassDiagramWindow::generalisationSelected()
{
    createNewLine(new GeneralizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates directed association line
 */
void ClassDiagramWindow::directedAssociationSelected()
{
    createNewLine(new DirectedAssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates realization line
 */
void ClassDiagramWindow::realizationSelected()
{
    createNewLine(new RealizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * When selection changes and a new relationship is invoked,
 * handle adding new relationship.
 */
void ClassDiagramWindow::nodePressed(ClassNode *selectedOne)
{
    if(currentState == state::lineCreation)
        setupLineHandle(selectedOne);
    else if (currentState == state::nodeRemoving)
        removeHandle(selectedOne);
}

/**
 * ClassDiagramWindow::connectNodes Connect two nodes by relationship
 */
void ClassDiagramWindow::connectNodes()
{
    // Create new line in scene
    newLine->initialize(firstToSelect, secondToSelect, firstToSelect == secondToSelect);
    classDiagramScene->addItem(newLine);
    firstToSelect->addLine(newLine);
    if(firstToSelect != secondToSelect)
        secondToSelect->addLine(newLine);

    // Create new relationship in class diagram
    Relationship *relationship;
    const std::type_info &relationshipType = typeid(*newLine);
    if (relationshipType == typeid(AgregationLine)) {
        relationship = new Aggregation{firstToSelect->getClassEntity(), secondToSelect->getClassEntity()};
    } else if (relationshipType == typeid(CompositionLine)) {
        relationship = new Composition{firstToSelect->getClassEntity(), secondToSelect->getClassEntity()};
    } else if (relationshipType == typeid(DirectedAssociationLine)) {
        relationship = new DirectedAssociation{firstToSelect->getClassEntity(), secondToSelect->getClassEntity()};
    } else if (relationshipType == typeid(GeneralizationLine)) {
        relationship = new Generalization{firstToSelect->getClassEntity(), secondToSelect->getClassEntity()};
    } else if (relationshipType == typeid(RealizationLine)) {
        relationship = new Realization{firstToSelect->getClassEntity(), secondToSelect->getClassEntity()};
    } else if (relationshipType == typeid(AssociationLine)) {
        auto *associationLine = dynamic_cast<AssociationLine *>(newLine);

        relationship = new UndirectedAssociation{
            firstToSelect->getClassEntity(),
            secondToSelect->getClassEntity(),
            associationLine->getName().toStdString(),
            associationLine->getFirstCardinality().toStdString(),
            associationLine->getSecondCardinality().toStdString()
        };
    } else {
        throw std::logic_error{"Unknown type of the line"};
    }

    classDiagram.addRelationship(relationship);
    storedRelationships.insert({newLine, relationship});

    firstToSelect = nullptr;
    secondToSelect = nullptr;
    newLine = nullptr;

    sceneUpdateObservable->sceneChanged();
}

/**
 * Checks if new line is nullptr (if no, deletes it) and insert line into newLine
 */
void ClassDiagramWindow::createNewLine(Line *line)
{
    if (newLine != nullptr)
        delete newLine;
    QList<QGraphicsItem *> items = classDiagramScene->selectedItems();
    if(items.count() == 2)
    {
        newLine = line;
        firstToSelect = dynamic_cast<ClassNode*>(items[0]);
        secondToSelect = dynamic_cast<ClassNode*>(items[1]);
        connectNodes();
    }
    else
    {
        classDiagramScene->clearSelection();
        setAllNodesColor(realtionShipSelectedColor);
        newLine = line;
        currentState = state::lineCreation;
    }
}

/**
 * Handles situation when button for a new line was pressed.
 */
void ClassDiagramWindow::setupLineHandle(ClassNode* selectedOne)
{
    if(nodeColor == realtionShipSelectedColor && firstToSelect == nullptr)
    {
        firstToSelect = selectedOne;
        if(firstToSelect)
        {
            setAllNodesColor(firstPhaseSelectedColor);
            firstToSelect->setBorderColor(nodeFirstSelectedColor);
        }
    }
    else if(nodeColor == firstPhaseSelectedColor && firstToSelect != nullptr) //first node selected and still in selctionMode
    {
        secondToSelect = selectedOne;
        if(secondToSelect)
        {
            setAllNodesColor(nodeNormalColor);
            classDiagramScene->clearSelection();
            connectNodes();
            currentState = state::none;
        }
    }
    classDiagramScene->clearSelection();
}

/**
 * Handles situation when button for remove was selected
 */
void ClassDiagramWindow::removeHandle(ClassNode* selectedOne)
{
    removeClassNodes(QList<QGraphicsItem *> {selectedOne});
    currentState = state::none;
    setAllNodesColor(nodeNormalColor);
}

/**
 * Slot is invoked when removeButton was pressed.
 */
void ClassDiagramWindow::removeSelected()
{
    QList<QGraphicsItem *> selectedItems = classDiagramScene->selectedItems();
    if(selectedItems.size() > 0)
        removeClassNodes(selectedItems);
    else
    {
        setAllNodesColor(Qt::red);
        currentState = state::nodeRemoving;
    }
}

/**
 * Automatically clears the whole scene
 */
void ClassDiagramWindow::clearScene()
{
    std::vector<ClassNode *> nodesForRemoval{};
    for (auto item: classDiagramScene->items()) {
        if (typeid(*item) == typeid(ClassNode)) {
            auto classNode = dynamic_cast<ClassNode *>(item);

            nodesForRemoval.push_back(classNode);
        }
    }

    for (auto &classNode: nodesForRemoval) {
        removeClassNode(classNode);
    }
}

/**
 * Redraws scene using updated class diagram
 *
 * @warning Does not clear scene. clearScene() should be called before
 */
void ClassDiagramWindow::redrawClassDiagram()
{
    // Add classes
    for (const auto &item: classDiagram.getClasses()) {
        auto classNode = new ClassNode(item, &storedClasses, sceneUpdateObservable);

        connect(&(classNode->emitter), &ClassNodeEmitter::nodePressed, this, &ClassDiagramWindow::nodePressed);
        classDiagramScene->addItem(classNode);
        storedClasses.insert({item->getName(), classNode});
    }

    // Add relationships
    for (auto item: classDiagram.getRelationships()) {
        std::string firstClassName{item->getFirstClass()->getName()};
        std::string secondClassName{item->getSecondClass()->getName()};

        ClassNode *firstClassNode = storedClasses.find(firstClassName)->second;
        ClassNode *secondClassNode = storedClasses.find(secondClassName)->second;

        Line *line;
        const std::type_info &relationshipType = typeid(*item);
        if (relationshipType == typeid(Aggregation)) {
            line = new AgregationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(Composition)) {
            line = new CompositionLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(DirectedAssociation)) {
            line = new DirectedAssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(Generalization)) {
            line = new GeneralizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(Realization)) {
            line = new RealizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(UndirectedAssociation)) {
            line = new AssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
            auto *associationLine = dynamic_cast<AssociationLine *>(line);

            // Add cardinalities
            auto *undirectedAssociation = dynamic_cast<UndirectedAssociation *>(item);
            auto firstCardinality = QString::fromStdString(undirectedAssociation->getFirstClassCardinality());
            auto secondCardinality = QString::fromStdString(undirectedAssociation->getSecondClassCardinality());

            associationLine->setFirstCardinality(firstCardinality);
            associationLine->setSecondCardinality(secondCardinality);
        } else {
            throw std::logic_error{"Unknown relationship"};
        }

        // Add to stored relationships
        storedRelationships.insert({line, item});

        // Add to scene
        line->initialize(firstClassNode, secondClassNode, firstClassNode == secondClassNode);
        classDiagramScene->addItem(line);
        firstClassNode->addLine(line);
        secondClassNode->addLine(line);
    }
}

/**
 * Slot for handling click action on "Open" button
 */
void ClassDiagramWindow::openButtonClicked()
{
    if (!classDiagramScene->items().isEmpty() && !isSaved) {
        auto clickedButton = QMessageBox::question(
            this,
            "Class diagram opening collision",
            "You are trying to open new class diagram before saving the edited one. Are you sure to continue?"
            " Canvas content will be replaced with loaded diagram."
        );

        if (clickedButton == QMessageBox::No) {
            // Stop here, nothing will be loaded
            return;
        }
    }

    QString file = QFileDialog::getOpenFileName(
        this,
        "Choose diagram to open",
        "",
        "XML files (*.xml)",
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    try {
        ClassDiagram loadedDiagram = classDiagramManager->loadDiagram(file.toStdString());

        // Remember source file
        targetFileName = file.toStdString();

        // Clear canvas
        if (!classDiagramScene->items().isEmpty()) {
            clearScene();
        }

        // Draw new diagram
        classDiagram = loadedDiagram;
        redrawClassDiagram();

        // Diagram has just been loaded from file
        isSaved = true;

        sceneUpdateObservable->sceneChanged();
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(this, "Class diagram opening error", e.what());
    } catch (InvalidInputDataException &e) {
        QMessageBox::critical(this, "Class diagram opening error", e.what());
    }
}

/**
 * Slot for handling click action on "Save" button
 */
void ClassDiagramWindow::saveButtonClicked()
{
    // Target file must be selected
    if (targetFileName.empty()) {
        QMessageBox::warning(this, "Class diagram saving error", "Edited diagram wasn't loaded from"
            " any file and target file hasn't been selected. You need to select target file first.");

        // Simulate clicking on "Save as..." button, user must select the target file
        saveAsButtonClicked();

        return;
    }

    try {
        classDiagramManager->saveDiagram(targetFileName, classDiagram);

        // Set diagram as saved
        isSaved = true;
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(this, "Class diagram saving error", e.what());
    }
}

/**
 * Slot for handling click action on "Save as..." button
 */
void ClassDiagramWindow::saveAsButtonClicked()
{
    // Prompt user to select the target file
    QString file = QFileDialog::getSaveFileName(
        this,
        "Choose target file for saving diagram",
        targetFileName.empty() ? "class-diagram.xml" : QString::fromStdString(targetFileName),
        "XML files (*.xml)",
        nullptr,
        QFileDialog::HideNameFilterDetails
    );

    if (file.isEmpty()) {
        // Dialog has been canceled
        return;
    }

    // Update target file
    targetFileName = file.toStdString();

    // Now just save diagram into selected file
    saveButtonClicked();
}

/**
 * Slot for handling click action on "Undo" button
 */
void ClassDiagramWindow::undoButtonClicked()
{
    // Clear canvas
    if (!classDiagramScene->items().isEmpty()) {
        clearScene();
    }

    classDiagramManager->undoDiagramChanges(&classDiagram);

    std::cerr << "State to undo:\n";
    std::cerr << "\tClasses:\n";
    for (const auto &item: classDiagram.getClasses()) {
        std::cerr << "\t\t- " << item->getName() << "\n";
    }
    std::cerr << "\tRelationships:\n";
    for (const auto &item: classDiagram.getRelationships()) {
        std::cerr << "\t\t- " << typeid(*item).name() << ": " << item->getFirstClass()->getName() << " <-> "
                  << item->getSecondClass()->getName() << "\n";
    }

    // Draw new diagram
    redrawClassDiagram();

//        sceneUpdateObservable->sceneChanged();
}

/**
 * Slot for handling click action on "Redo" button
 */
void ClassDiagramWindow::redoButtonClicked()
{
    // Clear canvas
    if (!classDiagramScene->items().isEmpty()) {
        clearScene();
    }

    classDiagramManager->redoDiagramChanges(&classDiagram);

    std::cerr << "State to redo:\n";
    std::cerr << "\tClasses:\n";
    for (const auto &item: classDiagram.getClasses()) {
        std::cerr << "\t\t- " << item->getName() << "\n";
    }
    std::cerr << "\tRelationships:\n";
    for (const auto &item: classDiagram.getRelationships()) {
        std::cerr << "\t\t- " << typeid(*item).name() << ": " << item->getFirstClass()->getName() << " <-> "
                  << item->getSecondClass()->getName() << "\n";
    }

    // Draw new diagram
    redrawClassDiagram();

//        sceneUpdateObservable->sceneChanged();
}

/**
 * Logs scene changes for saving and undo/redo mechanisms
 */
void ClassDiagramWindow::logChanges() noexcept
{
    isSaved = false;

    classDiagramManager->backupDiagram(&classDiagram);

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << "Scene changed: " << std::ctime(&time);

    std::cerr << "Current state:\n";
    std::cerr << "\tClasses:\n";
    for (const auto &item: classDiagram.getClasses()) {
        std::cerr << "\t\t- " << item->getName() << "\n";
    }
    std::cerr << "\tRelationships:\n";
    for (const auto &item: classDiagram.getRelationships()) {
        std::cerr << "\t\t- " << typeid(*item).name() << ": " << item->getFirstClass()->getName() << " <-> "
            << item->getSecondClass()->getName() << "\n";
    }
}
