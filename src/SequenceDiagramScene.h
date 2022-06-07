/**
 * @file SequenceDiagramScene.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_SEQUENCE_DIAGRAM_SCENE_H
#define ICP_PROJECT_SEQUENCE_DIAGRAM_SCENE_H

#include "CustomScene.h"
#include "SequenceDiagramManager.h"
#include "SceneUpdateObservable.h"

/**
 * Qt scene customized for sequence diagrams
 */
class SequenceDiagramScene: public CustomScene
{
    // Dependencies
    /**
     * Pointer to sequence diagram manager (for backend operations)
     */
    SequenceDiagramManager *sequenceDiagramManager;
    /**
     * Pointer to observable for distributing scene changes
     */
    SceneUpdateObservable *sceneUpdateObservable;
    /**
     * Pointer to linked class diagram
     */
    ClassDiagram *classDiagram;

  public:
    /**
     * Class constructor
     *
     * @param parentWindow Pointer to parent window (dependency)
     * @param sequenceDiagramManager Pointer to sequence diagram manage (dependency)
     * @param sceneUpdateObservable Pointer to observable for providing information about scene changes (dependency)
     * @param classDiagram Pointer to linked class diagram (dependency)
     */
    SequenceDiagramScene(
        QWidget *parentWindow,
        SequenceDiagramManager *sequenceDiagramManager,
        SceneUpdateObservable *sceneUpdateObservable,
        ClassDiagram *classDiagram
    );

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
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_SCENE_H
