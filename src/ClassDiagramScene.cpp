/**
 * @file ClassDiagramScene.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 * @author Jakub Dvořák (xdvora3q)
 */
#include <QMessageBox>
#include "ClassDiagramScene.h"
#include "GeneralizationLine.h"
#include "LineWithArrow.h"
#include "CompositionLine.h"
#include "AgregationLine.h"
#include "AssociationLine.h"
#include "DirectedAssociationLine.h"
#include "RealizationLine.h"
#include "InvalidDataStorageException.h"
#include "InvalidInputDataException.h"

/**
 * Class constructor
 *
 * @param parentWindow Parent window (dependency)
 * @param classDiagramManager Class diagram manage (dependency)
 * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
 */
ClassDiagramScene::ClassDiagramScene(
    QWidget *parentWindow,
    ClassDiagramManager *classDiagramManager,
    SceneUpdateObservable *sceneUpdateObservable
): CustomScene{parentWindow}, classDiagramManager{classDiagramManager}, sceneUpdateObservable{sceneUpdateObservable},
        storedClasses{}, storedRelationships{}
{
    newLine = nullptr;
    currentState = state::none;
}

// States checks and modifiers ------------------------------------------------------------- States checks and modifiers
/**
 * Logs scene changes for saving and undo/redo mechanisms
 */
void ClassDiagramScene::logChanges() noexcept
{
    saved = false;

    classDiagramManager->backupDiagram(&classDiagram);
}

// Top toolbar buttons' actions ----------------------------------------------------------- Top toolbar buttons' actions
/**
 * Loads diagram from file
 */
void ClassDiagramScene::loadFromFile()
{
    try {
        ClassDiagram loadedDiagram = classDiagramManager->loadDiagram(targetFile);

        // Clear canvas
        if (!items().isEmpty()) {
            clearScene();
        }

        // Draw new diagram
        classDiagram = loadedDiagram;
        redrawClassDiagram();

        // Diagram has just been loaded from file
        saved = true;

        sceneUpdateObservable->sceneChanged();
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(parentWindow, "Class diagram opening error", e.what());
    } catch (InvalidInputDataException &e) {
        QMessageBox::critical(parentWindow, "Class diagram opening error", e.what());
    }
}

/**
 * Saves diagram to already set file (or file where the diagram is loaded from)
 */
void ClassDiagramScene::saveToFile()
{
    try {
        classDiagramManager->saveDiagram(targetFile, classDiagram);

        // Set diagram as saved
        saved = true;
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(parentWindow, "Class diagram saving error", e.what());
    }
}

/**
 * Reverts last change
 */
void ClassDiagramScene::undoLastChange()
{
    // Clear canvas
    if (!items().isEmpty()) {
        clearScene();
    }

    classDiagramManager->undoDiagramChanges(&classDiagram);

    // Draw new diagram
    redrawClassDiagram();
}

/**
 * Restores reverted change
 */
void ClassDiagramScene::redoRevertedChange()
{
    // Clear canvas
    if (!items().isEmpty()) {
        clearScene();
    }

    classDiagramManager->redoDiagramChanges(&classDiagram);

    // Draw new diagram
    redrawClassDiagram();
}

// Tool box items' actions --------------------------------------------------------------------- Tool box items' actions
/**
 * Inserts new claas node into scene of class diagram Window.
 */
void ClassDiagramScene::addClassNode()
{
    // Numbering and positioning unique names
    static unsigned int classNumber = 1;
    static const unsigned int nodeSpace = 50;

    // Create new class in class diagram
    auto newClass = new Class{"New class " + std::to_string(classNumber++), std::make_tuple(0, 0)};

    classDiagram.addClass(newClass);

    // Create new GUI class node
    auto *newClassNode = new ClassNode(newClass, &storedClasses, sceneUpdateObservable);
    newClassNode->setPos(
        (newClassNode->boundingRect().width() + nodeSpace) * (classNumber % 5),
        (newClassNode->boundingRect().height() + nodeSpace) * (classNumber / 5) // NOLINT(bugprone-integer-division)
     );

    connect(&(newClassNode->emitter), &ClassNodeEmitter::nodePressed, this, &ClassDiagramScene::nodePressed);
    addItem(newClassNode);
    storedClasses.insert({newClass->getName(), newClassNode});

    sceneUpdateObservable->sceneChanged();
}

/**
 * Removes selected class node
 */
void ClassDiagramScene::removeSelectedNodes()
{
    QList<QGraphicsItem *> selectedClassNodes = selectedItems();
    if(!selectedClassNodes.empty()) {
        removeMultipleClassNodes(selectedClassNodes);
    } else {
        setAllNodesColor(Qt::red);
        currentState = state::nodeRemoving;
    }
}

/**
 * To a newLine pointer creates line
 */
void ClassDiagramScene::prepareUndirectedAssociation()
{
    createNewLine(new AssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates composition line
 */
void ClassDiagramScene::prepareComposition()
{
    createNewLine(new CompositionLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates agregation line
 */
void ClassDiagramScene::prepareAggregation()
{
    createNewLine(new AgregationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates generalisation line
 */
void ClassDiagramScene::prepareGeneralisation()
{
    createNewLine(new GeneralizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates directed association line
 */
void ClassDiagramScene::prepareDirectedAssociation()
{
    createNewLine(new DirectedAssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

/**
 * To a newLine pointer creates realization line
 */
void ClassDiagramScene::prepareRealization()
{
    createNewLine(new RealizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable});
}

// Private methods ------------------------------------------------------------------------------------- Private methods
/**
 * Sets border color to all nodes and to nodeColor
 *
 * @param color new node color
 */
void ClassDiagramScene::setAllNodesColor(const QColor &color)
{
    nodeColor = color;
    QList<QGraphicsItem *> allNodes = items();
    for(QGraphicsItem *maybeNode : allNodes)
    {
        auto *definitelyNode = dynamic_cast<ClassNode *>(maybeNode);
        if(definitelyNode)
            definitelyNode->setBorderColor(nodeColor);
    }
}

/**
 * Connects two nodes by relationship
 */
void ClassDiagramScene::connectNodes()
{
    // Create new line in scene
    newLine->initialize(firstToSelect, secondToSelect, firstToSelect == secondToSelect);
    addItem(newLine);
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
        auto *directedAssociationLine = dynamic_cast<DirectedAssociationLine *>(newLine);

        relationship = new DirectedAssociation{
                firstToSelect->getClassEntity(),
                secondToSelect->getClassEntity(),
                directedAssociationLine->getName().toStdString()
        };
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
 *
 * @param line Line to create
 */
void ClassDiagramScene::createNewLine(Line *line)
{
    delete newLine;

    QList<QGraphicsItem *> items = selectedItems();
    if(items.count() == 2) {
        newLine = line;
        firstToSelect = dynamic_cast<ClassNode*>(items[0]);
        secondToSelect = dynamic_cast<ClassNode*>(items[1]);
        connectNodes();
    } else {
        clearSelection();
        setAllNodesColor(relationshipSelectedColor);
        newLine = line;
        currentState = state::lineCreation;
    }
}

/**
 * Removes single class node
 *
 * @param classNode Pointer to class node to remove
 */
void ClassDiagramScene::removeClassNode(ClassNode *classNode)
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
        removeItem(connection);
        delete connection;
    }

    // Get corresponding class (entity)
    Class *classEntity = classNode->getClassEntity();

    // Delete from scene and memory
    removeItem(classNode);
    delete classNode;

    // Delete from stored classes
    storedClasses.erase(storedClasses.find(classEntity->getName()));

    // Delete class from diagram and memory
    classDiagram.removeClass(classEntity);
    delete classEntity;
}

/**
 * Automatically clears the whole scene
 */
void ClassDiagramScene::clearScene()
{
    std::vector<ClassNode *> nodesForRemoval{};
    for (auto item: items()) {
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
void ClassDiagramScene::redrawClassDiagram()
{
    // Add classes
    for (const auto &item: classDiagram.getClasses()) {
        auto classNode = new ClassNode(item, &storedClasses, sceneUpdateObservable);

        connect(&(classNode->emitter), &ClassNodeEmitter::nodePressed, this, &ClassDiagramScene::nodePressed);
        addItem(classNode);
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
            auto *directedAssociationLine = dynamic_cast<DirectedAssociationLine *>(line);

            // Add name
            auto name = QString::fromStdString(item->getName());

            directedAssociationLine->setName(name);
        } else if (relationshipType == typeid(Generalization)) {
            line = new GeneralizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(Realization)) {
            line = new RealizationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
        } else if (relationshipType == typeid(UndirectedAssociation)) {
            line = new AssociationLine{&storedRelationships, &classDiagram, sceneUpdateObservable};
            auto *associationLine = dynamic_cast<AssociationLine *>(line);

            // Add name and cardinalities
            auto *undirectedAssociation = dynamic_cast<UndirectedAssociation *>(item);
            auto name = QString::fromStdString(undirectedAssociation->getName());
            auto firstCardinality = QString::fromStdString(undirectedAssociation->getFirstClassCardinality());
            auto secondCardinality = QString::fromStdString(undirectedAssociation->getSecondClassCardinality());

            associationLine->setName(name);
            associationLine->setFirstCardinality(firstCardinality);
            associationLine->setSecondCardinality(secondCardinality);
        } else {
            throw std::logic_error{"Unknown relationship"};
        }

        // Add to stored relationships
        storedRelationships.insert({line, item});

        // Add to scene
        line->initialize(firstClassNode, secondClassNode, firstClassNode == secondClassNode);
        addItem(line);
        firstClassNode->addLine(line);
        secondClassNode->addLine(line);
    }
}

/**
 * Handles situation when button for a new line was pressed.
 *
 * @param selectedOne Selected class node
 */
void ClassDiagramScene::setupLineHandle(ClassNode* selectedOne)
{
    if (nodeColor == relationshipSelectedColor && firstToSelect == nullptr) {
        firstToSelect = selectedOne;
        if(firstToSelect) {
            setAllNodesColor(firstPhaseSelectedColor);
            firstToSelect->setBorderColor(nodeFirstSelectedColor);
        }
    } else if (nodeColor == firstPhaseSelectedColor && firstToSelect != nullptr) {
        // First node selected and still in selection mode
        secondToSelect = selectedOne;
        if (secondToSelect) {
            setAllNodesColor(nodeNormalColor);
            clearSelection();
            connectNodes();
            currentState = state::none;
        }
    }
    clearSelection();
}

/**
 * Handles situation when button for remove was selected
 *
 * @param selectedOne Selected class node
 */
void ClassDiagramScene::removeHandle(ClassNode* selectedOne)
{
    QList<QGraphicsItem *> selectedItems{selectedOne};
    removeMultipleClassNodes(selectedItems);
    currentState = state::none;
    setAllNodesColor(nodeNormalColor);
}

/**
 * Removes specified class nodes.
 *
 * @param nodesForRemoval Class nodes to be removed
 */
void ClassDiagramScene::removeMultipleClassNodes(QList<QGraphicsItem *> &nodesForRemoval)
{
    for (QGraphicsItem *item : nodesForRemoval)
    {
        auto node = dynamic_cast<ClassNode *>(item);
        if(node) {
            removeClassNode(node);
        }
    }

    sceneUpdateObservable->sceneChanged();
}

// Slots --------------------------------------------------------------------------------------------------------- Slots
/**
 * When selection changes and a new relationship is invoked,
 * handle adding new relationship.
 *
 * @param selectedOne Class node the mouse clicked on
 */
void ClassDiagramScene::nodePressed(ClassNode *selectedOne)
{
    if(currentState == state::lineCreation)
        setupLineHandle(selectedOne);
    else if (currentState == state::nodeRemoving)
        removeHandle(selectedOne);
}