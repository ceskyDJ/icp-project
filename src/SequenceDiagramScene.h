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
#include "MessageLine.h"

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
    SequenceDiagram *sequenceDiagram;
    ClassDiagram *classDiagram;

    // Colors
    const QColor messageSelectedColor = Qt::darkGreen;
    const QColor objectNormalColor = Qt::black;
    const QColor secondPhaseSelectedColor = Qt::darkMagenta;
    const QColor firstPhaseSelectedColor = Qt::darkCyan;

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
    /**
     * Add new actor to scene
     */
    void addActor();
    /**
     * Add new object into scene.
     */
    void addObject();
    /**
     * States for handling actions by user.
     */
    enum state{messageCreation, objectRemoving, none} currentState;
    /**
     * Checks if new line is nullptr (if no, deletes it) and insert messageline into newMessageLine
     *
     * @param line messageLine to store
     */
    void createNewMessageLine(MessageLine *line);
    /**
     * Creates new meesageLine and store it into variable newMessageLine. Also store MessageType intp newMessageType.
     *
     * @param messageLine new line
     * @param type type of message
     */
    void createNewMessageLine(MessageLine *line, MessageType type);
public slots:
    /**
     * Remove selected button was pressed. Handles an event - remove selected or change current state.
     */
    void removeObjectPressed();
private:
    QList<QGraphicsItem*> mySelectedItems;
    /**
     * MessageLine used in creation process.
     */
    MessageLine *newMessageLine = nullptr;
    /**
     * Message type used during creation process of new message.
     */
    MessageType newMessageLineType;
    /**
     * Reciever of new message
     */
    ActivationGraphicsObjectBase *reciever = nullptr;
    /**
     * Sender of new message
     */
    ActivationGraphicsObjectBase *sender = nullptr;
    /**
     * Removes single class node
     *
     * @param classNode Pointer to class node to remove
     */
    void removeObject(ActivationGraphicsObjectBase *activationObject, bool logChange);
    /**
    * Removes all selected objects.
    *
    * @param nodesForRemoval Class nodes to be removed
    */
   void removeSelectedObjects();
   /**
    * Connect messageLine by newMessageLine and newMessage
    */
   void sendMessage();
   /**
    * Handles situation when remove cobject was pressed.
    */
   void removeHandle(ActivationGraphicsObjectBase *activationItem);

   /**
    *
    *
    * @param newColor
    */
   void changeObjectsColor(QColor newColor);
   /**
    * Handles what to do if in selction mode.
    *
    * @param ivokedBy Node that was pressed on.
    */
   void selectLinesHandle(ActivationGraphicsObjectBase *ivokedBy);
private slots:
    /**
    * Function that informs this, that invokedBy, was clicked on.
    *
    * @param invokedBy sender object
    */
    void objectPressed(ActivationGraphicsObjectBase *invokedBy);
    /**
     * Edit mySelectedItems
     */
    void selectionEdit();
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_SCENE_H
