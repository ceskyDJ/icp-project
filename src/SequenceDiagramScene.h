/**
 * @file SequenceDiagramScene.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
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
    /**
     * Class diagram - data source for sequence diagram.
     */
    ClassDiagram *classDiagram;

    // Containers
    /**
     * Edited sequence diagram
     */
    SequenceDiagram sequenceDiagram;
    /**
     * Custom list of selected items in order of clicking on them
     */
    QList<QGraphicsItem*> mySelectedItems;

    // Colors
    /**
     * Color of selected message
     */
    const QColor messageSelectedColor = Qt::darkGreen;
    /**
     * Normal color of object
     */
    const QColor objectNormalColor = Qt::black;
    /**
     * Color of items in the first phase of selection
     */
    const QColor firstPhaseSelectedColor = Qt::darkCyan;
    /**
     * Color of items in the second phase of selection
     */
    const QColor secondPhaseSelectedColor = Qt::darkMagenta;

    // States
    /**
     * States for handling actions by user.
     */
    enum state{messageCreation, objectRemoving, none} currentState;
    /**
     * MessageLine used in creation process.
     */
    MessageLine *newMessageLine;
    /**
     * Message type used during creation process of new message.
     */
    MessageType newMessageLineType;
    /**
     * Receiver of new message
     */
    ActivationGraphicsObjectBase *newReceiver;
    /**
     * Sender of new message
     */
    ActivationGraphicsObjectBase *newSender;

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

    // Tool box items' actions
    /**
     * Add new actor to scene
     */
    void addActor();
    /**
     * Add new object into scene.
     */
    void addObject();
    /**
     * Removes selected item or changes its current state.
     */
    void removeSelected();
    /**
     * Prepares sync message for adding (after selecting nodes)
     */
    void prepareSyncMessage();
    /**
     * Prepares async message for adding (after selecting nodes)
     */
    void prepareAsyncMessage();
    /**
     * Prepares create message for adding (after selecting nodes)
     */
    void prepareCreateMessage();
    /**
     * Prepares destroy message for adding (after selecting nodes)
     */
    void prepareDestroyMessage();
    /**
     * Prepares reply message for adding (after selecting nodes)
     */
    void prepareReplyMessage();

    // Public static methods
    /**
     * Checks if it is possible to create new message. If error occures, store message into errorMsg.
     *
     * @param errorMsg If error occurs, store error message there else errorMsg is unchanged.
     * @param receiver newReceiver object
     * @param messageType type of message
     * @return true if everything is ok.
     * @return false if creation is NOT possible.
     */
    static bool createMessagePossible(QString *errorMsg, ActivationGraphicsObjectBase *receiver,
                                      ActivationGraphicsObjectBase *sender, MessageType messageType);

  private:
    /**
     * Creates new message line and store it into variable newMessageLine. Also store MessageType intp newMessageType.
     *
     * @param messageLine new line
     * @param type type of message
     */
    void createNewMessageLine(MessageLine *line, MessageType type);

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
    * Return all activation items in scene, sorted by order attribute.
    *
    * @return QVector<ActivationGraphicsObjectBase *> all activation items in scene, sorted by insertion order.
    */
   QVector<ActivationGraphicsObjectBase *> activationObjectsInScene();
   /**
    * Sort all activation items in scene
    */
   void sortActivationItems();
   /**
    * Handles what to do if in selction mode.
    *
    * @param invokedBy Node that was pressed on.
    */
   void selectLinesHandle(ActivationGraphicsObjectBase *invokedBy);
    /**
      * Automatically clears the whole scene
      */
    void clearScene();
    /**
     * Redraws scene using updated sequence diagram
     *
     * @warning Does not clear scene. clearScene() should be called before
     */
    void redrawSequenceDiagram();

  private slots:
    /**
    * Function that informs this, that invokedBy, was clicked on.
    *
    * @param invokedBy newSender object
    */
    void objectPressed(ActivationGraphicsObjectBase *invokedBy);
    /**
     * Edit mySelectedItems
     */
    void selectionEdit();
    /**
     * Slot is used when emitted change() signal - if there is a different number of activation
     * objects, sort the objects.
     */
    void objectSortSlot(QList<QRectF>);

    /**
     * Moves recived object left.
     *
     * @param objectToMove object that will be moved left.
     */
    void moveObjectLeft(ActivationGraphicsObjectBase *objectToMove);

    /**
     * Moves recieved object to right
     *
     * @param objectToMove object that will be move right.
     */
    void moveObjectRight(ActivationGraphicsObjectBase *objectToMove);
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_SCENE_H
