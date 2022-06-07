/**
 * @file SequenceDiagramScene.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include "SequenceDiagramScene.h"

/**
 * Class constructor
 *
 * @param parentWindow Pointer to parent window (dependency)
 * @param sequenceDiagramManager Pointer to sequence diagram manage (dependency)
 * @param sceneUpdateObservable Pointer to observable for providing information about scene changes (dependency)
 * @param classDiagram Pointer to linked class diagram (dependency)
 */
SequenceDiagramScene::SequenceDiagramScene(
    QWidget *parentWindow,
    SequenceDiagramManager *sequenceDiagramManager,
    SceneUpdateObservable *sceneUpdateObservable,
    ClassDiagram *classDiagram
): CustomScene{parentWindow}, sequenceDiagramManager{sequenceDiagramManager},
        sceneUpdateObservable{sceneUpdateObservable}, classDiagram{classDiagram} {}

/**
 * Logs scene changes for saving and undo/redo mechanisms
 */
void SequenceDiagramScene::logChanges() noexcept
{
    // TODO: implement this method
}

/**
 * Loads diagram from file
 */
void SequenceDiagramScene::loadFromFile()
{
    // TODO: implement this method
}

/**
 * Saves diagram to already set file (or file where the diagram is loaded from)
 */
void SequenceDiagramScene::saveToFile()
{
    // TODO: implement this method
}

/**
 * Reverts last change
 */
void SequenceDiagramScene::undoLastChange()
{
    // TODO: implement this method
}

/**
 * Restores reverted change
 */
void SequenceDiagramScene::redoRevertedChange()
{
    // TODO: implement this method
}
