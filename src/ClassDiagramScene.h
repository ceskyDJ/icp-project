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
    ClassDiagramManager *classDiagramManager;
    SceneUpdateObservable *sceneUpdateObservable;

    // Containers
    ClassDiagram classDiagram;
    std::unordered_map<std::string, ClassNode *> storedClasses;
    std::unordered_map<Line *, Relationship *> storedRelationships;

    // Colors
    const QColor relationshipSelectedColor = Qt::darkGreen;
    const QColor nodeNormalColor = Qt::black;
    const QColor nodeFirstSelectedColor = Qt::darkMagenta;
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
     * To a newLine pointer creates agregation line
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
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_SCENE_H
