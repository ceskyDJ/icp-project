/**
 * @file ClassDiagramScene.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ICP_PROJECT_CLASS_DIAGRAM_SCENE_H
#define ICP_PROJECT_CLASS_DIAGRAM_SCENE_H

#include <QGraphicsScene>
#include "CustomScene.h"
#include "SceneUpdateObservable.h"
#include "ClassDiagramManager.h"
#include "classNode.h"
#include "Line.h"

/**
 * Qt scene customized for class diagrams
 */
class ClassDiagramScene: public CustomScene
{
    // Dependencies
    /**
     * Pointer to class diagram manager (for backend operations)
     */
    ClassDiagramManager *classDiagramManager;
    /**
     * Pointer to observable for distributing scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;

    // Containers
    /**
     * Edited class diagram
     */
    ClassDiagram classDiagram;
    /**
     * Map of existing class nodes and names of their class entities
     */
    std::unordered_map<std::string, ClassNode *> storedClasses;
    /**
     * Map of existing relationships and their lines
     */
    std::unordered_map<Line *, Relationship *> storedRelationships;
    /**
     * Custom list of selected items in order of clicking on them
     */
    QList<QGraphicsItem *> sortedSelectionList;

    // Colors
    /**
     * Color of selected relationships
     */
    const QColor relationshipSelectedColor = Qt::darkGreen;
    /**
     * Normal color of class nodes
     */
    const QColor nodeNormalColor = Qt::black;
    /**
     * Color of first selected class node
     */
    const QColor nodeFirstSelectedColor = Qt::darkMagenta;
    /**
     * Color of classes available for selection (except the first selected one, it could be selected again)
     */
    const QColor firstPhaseSelectedColor = Qt::darkCyan;

    // States
    /**
     * Current state of tool items
     */
    enum state{lineCreation, nodeRemoving, none} currentState;
    /**
     * First selected note
     */
    ClassNode *firstToSelect = nullptr;
    /**
     * Second selected note
     */
    ClassNode *secondToSelect = nullptr;
    /**
     * New line in creation process
     */
    Line *newLine;
    /**
     * Current color used for class nodes
     */
    QColor nodeColor = nodeNormalColor;

  public:
    /**
     * Class constructor
     *
     * @param parentWindow Parent window (dependency)
     * @param classDiagramManager Class diagram manage (dependency)
     * @param sceneUpdateObservable Observable for providing information about scene changes (dependency)
     */
    ClassDiagramScene(QWidget *parentWindow, ClassDiagramManager *classDiagramManager, SceneUpdateObservable *sceneUpdateObservable);

    // States checks and modifiers
    /**
     * Logs scene changes for saving and undo/redo mechanisms
     */
    void logChanges() noexcept override;

    // Top toolbar buttons' actions
    /**
     * Loads diagram from file
     */
    void loadFromFile() override;
    /**
     * Saves diagram to already set file (or file where the diagram is loaded from)
     */
    void saveToFile() override;
    /**
     * Reverts last change
     */
    void undoLastChange() override;
    /**
     * Restores reverted change
     */
    void redoRevertedChange() override;

    // Tool box items' actions
    /**
     * Inserts new claas node into scene of class diagram Window.
     */
    void addClassNode();
    /**
     * Removes selected class node
     */
    void removeSelectedNodes();
    /**
     * To a newLine pointer creates line
     */
    void prepareUndirectedAssociation();
    /**
     * To a newLine pointer creates composition line
     */
    void prepareComposition();
    /**
     * To a newLine pointer creates aggregation line
     */
    void prepareAggregation();
    /**
     * To a newLine pointer creates generalisation line
     */
    void prepareGeneralisation();
    /**
     * To a newLine pointer creates directed association line
     */
    void prepareDirectedAssociation();
    /**
     * To a newLine pointer creates realization line
     */
    void prepareRealization();

    // Getters
    /**
     * Getter for current version of class diagram
     *
     * @warning Class diagram is changing with the time,
     * so use pointers into it carefully
     *
     * @return Pointer to class diagram
     */
    ClassDiagram *getClassDiagram();
  private:
    /**
     * Sets border color to all nodes and to nodeColor
     *
     * @param color new node color
     */
    void setAllNodesColor(const QColor &color);
    /**
     * Connects two nodes by relationship
     */
    void connectNodes();
    /**
     * Checks if new line is nullptr (if no, deletes it) and insert line into newLine
     *
     * @param line Line to create
     */
    void createNewLine(Line *line);
    /**
     * Removes single class node
     *
     * @param classNode Pointer to class node to remove
     */
    void removeClassNode(ClassNode *classNode);
    /**
     * Automatically clears the whole scene
     */
    void clearScene();
    /**
     * Redraws scene using updated class diagram
     *
     * @warning Does not clear scene. clearScene() should be called before
     */
    void redrawClassDiagram();
    /**
     * Handles situation when button for a new line was pressed.
     *
     * @param selectedOne Selected class node
     */
    void setupLineHandle(ClassNode* selectedOne);
    /**
     * Handles situation when button for remove was selected
     *
     * @param selectedOne Selected class node
     */
    void removeHandle(ClassNode* selectedOne);
    /**
     * Removes specified class nodes.
     *
     * @param nodesForRemoval Class nodes to be removed
     */
    void removeMultipleClassNodes(QList<QGraphicsItem *> &nodesForRemoval);

  private slots:
    /**
     * When selection changes and a new relationship is invoked,
     * handle adding new relationship.
     *
     * @param selectedOne Class node the mouse clicked on
     */
    void nodePressed(ClassNode *selectedOne);
    /**
     * When selection is changed, it will update sortedSelectionList
     */
    void selectionEdit();
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_SCENE_H
