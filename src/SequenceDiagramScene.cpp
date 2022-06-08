/**
 * @file SequenceDiagramScene.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include "SequenceDiagramScene.h"
#include "SyncMessageLine.h"
#include "ActorGraphicsItem.h"
#include "ObjectGraphicsItem.h"
#include "InvalidDataStorageException.h"
#include "InvalidInputDataException.h"
#include "AsyncMessageLine.h"
#include "CreateMessageLine.h"
#include "DestroyMessageLine.h"
#include "ReplyMessageLine.h"
#include <QMessageBox>

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
        sceneUpdateObservable{sceneUpdateObservable}, classDiagram{classDiagram}, newMessageLine{nullptr},
        newMessageLineType{}, newReceiver{nullptr}, newSender{nullptr}
{
    currentState = state::none;
    connect(this, &SequenceDiagramScene::selectionChanged, this, &SequenceDiagramScene::selectionEdit);
    connect(this, &SequenceDiagramScene::changed, this, &SequenceDiagramScene::objectSortSlot);
}

// States checks and modifiers ------------------------------------------------------------- States checks and modifiers
/**
 * Logs scene changes for saving and undo/redo mechanisms
 */
void SequenceDiagramScene::logChanges() noexcept
{
    saved = false;

    sequenceDiagramManager->backupDiagram(&sequenceDiagram);
}

// Top toolbar buttons' actions ----------------------------------------------------------- Top toolbar buttons' actions
/**
 * Loads diagram from file
 */
void SequenceDiagramScene::loadFromFile()
{
    try {
        SequenceDiagram loadedDiagram = sequenceDiagramManager->loadDiagram(classDiagram, targetFile.toStdString());

        // Clear canvas
        if (!items().isEmpty()) {
            clearScene();
        }

        // Draw new diagram
        sequenceDiagram = loadedDiagram;
        redrawSequenceDiagram();

        sceneUpdateObservable->sceneChanged();

        // Diagram has just been loaded from file
        saved = true;
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(parentWindow, "Sequence diagram opening error", e.what());
    } catch (InvalidInputDataException &e) {
        QMessageBox::critical(parentWindow, "Sequence diagram opening error", e.what());
    }
}

/**
 * Saves diagram to already set file (or file where the diagram is loaded from)
 */
void SequenceDiagramScene::saveToFile()
{
    try {
        sequenceDiagramManager->saveDiagram(targetFile.toStdString(), sequenceDiagram);

        // Set diagram as saved
        saved = true;
    } catch (InvalidDataStorageException &e) {
        QMessageBox::critical(parentWindow, "Sequence diagram saving error", e.what());
    }
}

/**
 * Reverts last change
 */
void SequenceDiagramScene::undoLastChange()
{
    // Clear canvas
    if (!items().isEmpty()) {
        clearScene();
    }

    sequenceDiagramManager->undoDiagramChanges(&sequenceDiagram);

    // Draw new diagram
    redrawSequenceDiagram();
}

/**
 * Restores reverted change
 */
void SequenceDiagramScene::redoRevertedChange()
{
    // Clear canvas
    if (!items().isEmpty()) {
        clearScene();
    }

    sequenceDiagramManager->redoDiagramChanges(&sequenceDiagram);

    // Draw new diagram
    redrawSequenceDiagram();
}

// Tool box items' actions --------------------------------------------------------------------- Tool box items' actions
/**
 * Add new actor to scene
 */
void SequenceDiagramScene::addActor()
{
    auto *actorItem = new ActorGraphicsItem();
    sequenceDiagram.addActor(actorItem->getActor());

    addItem(actorItem);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::moveLeft, this, &SequenceDiagramScene::moveObjectLeft);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::moveRight, this, &SequenceDiagramScene::moveObjectRight);
    sceneUpdateObservable->sceneChanged();
}

/**
 * Add new object to scene.
 */
void SequenceDiagramScene::addObject()
{
    Class *referredClass = (!classDiagram->getClasses().empty()) ? classDiagram->getClasses()[0] : nullptr;
    ClassReference classRef{"UNKNOWN CLASS"};
    if (referredClass) {
        classRef.storePointer(referredClass);
    }

    auto *newObject = new Object(classRef);
    auto *objectItem = new ObjectGraphicsItem(newObject, classDiagram);

    connect(&(objectItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    connect(&(objectItem->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);
    connect(&(objectItem->emitter), &ActivationObjectEmitter::moveLeft, this, &SequenceDiagramScene::moveObjectLeft);
    connect(&(objectItem->emitter), &ActivationObjectEmitter::moveRight, this, &SequenceDiagramScene::moveObjectRight);

    sequenceDiagram.addObject(newObject);
    addItem(objectItem);

    //user will set the object first
    objectItem->showEditDialog(false);
    sceneUpdateObservable->sceneChanged();
}

/**
 * Remove selected button was pressed. Handles an event - remove selected or change current state.
 */
void SequenceDiagramScene::removeSelected()
{
    QList<QGraphicsItem *> selectedObjects = selectedItems();
    if (!selectedObjects.empty()) {
        removeSelectedObjects();
    } else {
        ActivationGraphicsObjectBase::setColor(firstPhaseSelectedColor);
        currentState = state::objectRemoving;
    }
}

/**
 * Prepares sync message for adding (after selecting nodes)
 */
void SequenceDiagramScene::prepareSyncMessage()
{
    createNewMessageLine(new SyncMessageLine{&sequenceDiagram}, MessageType::SYNC);
}

/**
 * Prepares async message for adding (after selecting nodes)
 */
void SequenceDiagramScene::prepareAsyncMessage()
{
    createNewMessageLine(new AsyncMessageLine{&sequenceDiagram}, MessageType::ASYNC);
}

/**
 * Prepares create message for adding (after selecting nodes)
 */
void SequenceDiagramScene::prepareCreateMessage()
{
    createNewMessageLine(new CreateMessageLine{&sequenceDiagram}, MessageType::CREATE);
}

/**
 * Prepares destroy message for adding (after selecting nodes)
 */
void SequenceDiagramScene::prepareDestroyMessage()
{
    createNewMessageLine(new DestroyMessageLine{&sequenceDiagram}, MessageType::DESTROY);
}

/**
 * Prepares reply message for adding (after selecting nodes)
 */
void SequenceDiagramScene::prepareReplyMessage()
{
    createNewMessageLine(new ReplyMessageLine{&sequenceDiagram}, MessageType::REPLY);
}

// Public static methods ------------------------------------------------------------------------- Public static methods
/**
 * Checks if it is possible to create new message. If error occurs, store message into errorMsg.
 *
 * @param errorMsg If error occurs, store error message there else errorMsg is unchanged.
 * @param receiver newReceiver object
 * @param messageType type of message
 * @return true if everything is ok.
 * @return false if creation is NOT possible.
 */
bool SequenceDiagramScene::createMessagePossible(QString *errorMsg, ActivationGraphicsObjectBase *receiver,
                                                 ActivationGraphicsObjectBase *sender , MessageType messageType)
{
    if (receiver == sender) {
        *errorMsg = "Receiver cannot be newSender in one message!";

        return false;
    }

    auto *actor = dynamic_cast<ActorGraphicsItem*>(receiver);
    if (actor && (messageType == (MessageType)MessageType::CREATE || messageType == (MessageType)MessageType::DESTROY)) {
        *errorMsg = "Actor cannot recieve any message of type <<create>> nor <<destroy>>!";
        return false;
    } else {
        auto *obj = dynamic_cast<ObjectGraphicsItem *>(receiver);
        if(messageType == (MessageType)MessageType::DESTROY && obj->getDestroyMessage()) {
            *errorMsg = "Object cannot recieve more than one destroy message!";
            return false;
        } else if (messageType == (MessageType)MessageType::CREATE && obj->getCreateMessage()) {
            *errorMsg = "Object cannot recieve more than one create message!";
            return false;
        }
    }

    return true;
}

// Private methods ------------------------------------------------------------------------------------- Private methods
/**
 * Checks if new line is nullptr (if no, deletes it) and insert message line into newMessageLine
 *
 * @param line messageLine to store
 */
void SequenceDiagramScene::createNewMessageLine(MessageLine *line, MessageType type)
{
    delete newMessageLine;
    newMessageLine = line;
    newMessageLineType = type;
    if (mySelectedItems.count() == 2) {
        newSender = dynamic_cast<ActivationGraphicsObjectBase*>(mySelectedItems[0]);
        newReceiver = dynamic_cast<ActivationGraphicsObjectBase*>(mySelectedItems[1]);
        sendMessage();
    } else {
        clearSelection();
        ActivationGraphicsObjectBase::setColor(firstPhaseSelectedColor);
        currentState = state::messageCreation;
    }
}

/**
 * Removes single class node
 *
 * @param classNode Pointer to class node to remove
 */
void SequenceDiagramScene::removeObject(ActivationGraphicsObjectBase *activationObject, bool logChange)
{
    auto *objectToRemove = dynamic_cast<ObjectGraphicsItem *>(activationObject);
    if (objectToRemove) {
        // ActivationObject is Object
        removeItem(objectToRemove);
        sequenceDiagram.removeObject(objectToRemove->getObject());
        delete objectToRemove;
    } else {
        auto *actorItem = dynamic_cast<ActorGraphicsItem *>(activationObject);
        removeItem(actorItem);
        sequenceDiagram.removeActor(actorItem->getActor());
        delete actorItem;
    }

    if (logChange) {
        sceneUpdateObservable->sceneChanged();
    }
}

/**
 * Removes all selected objects.
 *
 * @param nodesForRemoval Class nodes to be removed
 */
void SequenceDiagramScene::removeSelectedObjects()
{
    QList<QGraphicsItem *> selectedObjects = selectedItems();
    for (QGraphicsItem *item : selectedObjects) {
        auto itemToRemove = dynamic_cast<ActivationGraphicsObjectBase*>(item);
        removeObject(itemToRemove, false);
    }

    sceneUpdateObservable->sceneChanged();
}

/**
 * Connects two object by message
 */
void SequenceDiagramScene::sendMessage()
{
    // Create new message line in scene
    auto *objectReceiver = dynamic_cast<ObjectGraphicsItem *>(newReceiver);
    MethodReference ref{"UNKNOWN METHOD"};
    if (objectReceiver) {
        std::vector<ClassMethod> methods = objectReceiver->getObject()->getInstanceClass()->getMethods();
        if (!methods.empty()) {
            ref = MethodReference{&(objectReceiver->getObject()->getInstanceClass()->getMethods()[0])};
        }
    }

    //check if is possible to create new line
    QString errorMsg = "";
    if (!createMessagePossible(&errorMsg, newReceiver, newSender, newMessageLineType)) {
        QMessageBox msgBox;
        msgBox.setText(errorMsg);
        msgBox.setWindowTitle("Creation was not successful");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    auto *newMessage = new Message(
        ref,
        newMessageLineType,
        newSender->getMessageNode(),
        newReceiver->getMessageNode(),
        0.0
    );

    auto *receiverObject = dynamic_cast<ObjectGraphicsItem *>(newReceiver);
    ClassReference classRef = receiverObject->getObject()->getInstanceClass();

    newMessageLine->initialize(newSender, newReceiver, newMessage, classRef);
    addItem(newMessageLine);

    // Store new message in sequence diagram
    sequenceDiagram.addMessage(newMessage);
    newSender = nullptr;
    newReceiver = nullptr;
    newMessageLine = nullptr;

    sceneUpdateObservable->sceneChanged();
}

/**
 * Remove pressed object and set current state to none.
 *
 * @param activationItem to remove
 */
void SequenceDiagramScene::removeHandle(ActivationGraphicsObjectBase *activationItem)
{
    ActivationGraphicsObjectBase::setColor(objectNormalColor);
    currentState = state::none;
    removeObject(activationItem, true);
}

/**
 * Return all activation items in scene, sorted by order attribute.
 *
 * @return QVector<ActivationGraphicsObjectBase *> all activation items in scene, sorted by insertion order.
 */
QVector<ActivationGraphicsObjectBase *> SequenceDiagramScene::activationObjectsInScene()
{
    QList<QGraphicsItem*> sceneItems = items(Qt::AscendingOrder);
    QVector<ActivationGraphicsObjectBase*> activationItems;
    for (QGraphicsItem* item : sceneItems) {
        auto *activationObject = dynamic_cast<ActivationGraphicsObjectBase *>(item);
        if (activationObject) {
            activationItems.push_back(activationObject);
        }
    }

    //sort items by order
    std::sort(activationItems.begin(), activationItems.end(),
              [](ActivationGraphicsObjectBase * first, ActivationGraphicsObjectBase *second)
    {
       return first->order < second->order;
    });
    return activationItems;
}

/**
 * Sort all activation items in scene in x axis.
 */
void SequenceDiagramScene::sortActivationItems()
{
    QVector<ActivationGraphicsObjectBase *> activationItems = activationObjectsInScene();
    for (int i = 0; i < activationItems.size(); i++) {
        activationItems[i]->setPos( ActivationGraphicsObjectBase::objectPadding * i, 0);
    }
}

/**
 * Handles what to do if in selection mode.
 *
 * @param invokedBy Node that was pressed on.
 */
void SequenceDiagramScene::selectLinesHandle(ActivationGraphicsObjectBase *invokedBy)
{
    if(ActivationGraphicsObjectBase::getColor() == firstPhaseSelectedColor) {
        newSender = invokedBy;
        ActivationGraphicsObjectBase::setColor(secondPhaseSelectedColor);
    } else {
        newReceiver = invokedBy;
        ActivationGraphicsObjectBase::setColor(objectNormalColor);
        currentState = state::none;
        sendMessage();
    }
}

/**
  * Automatically clears the whole scene
  */
void SequenceDiagramScene::clearScene()
{
    for (const auto item: items()) {
        item->setSelected(true);
    }

    removeSelectedObjects();
}

/**
 * Redraws scene using updated sequence diagram
 *
 * @warning Does not clear scene. clearScene() should be called before
 */
void SequenceDiagramScene::redrawSequenceDiagram()
{
    std::unordered_map<Actor *, ActorGraphicsItem *> loadedActors;
    std::unordered_map<Object *, ObjectGraphicsItem *> loadedObjects;

    // Load actors
    for (const auto objActor: sequenceDiagram.getActors()) {
        auto *guiActor = new ActorGraphicsItem(objActor);

        connect(&(guiActor->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
        connect(&(guiActor->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);

        addItem(guiActor);
        loadedActors.insert({objActor, guiActor});
    }

    // Load objects
    for (const auto objObject: sequenceDiagram.getObjects()) {
        auto *guiObject = new ObjectGraphicsItem(objObject, classDiagram);

        connect(&(guiObject->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
        connect(&(guiObject->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);

        addItem(guiObject);
        loadedObjects.insert({objObject, guiObject});
    }

    // Load messages
    for (const auto objMessage: sequenceDiagram.getMessages()) {
        // Message sender
        MessageNode *messageSender = objMessage->getMessageSender();
        ActivationGraphicsObjectBase *senderGuiItem;
        if (typeid(*messageSender) == typeid(Actor)) {
            auto actor = dynamic_cast<Actor *>(messageSender);
            senderGuiItem = dynamic_cast<ActivationGraphicsObjectBase *>(loadedActors.find(actor)->second);
        } else if (typeid(*messageSender) == typeid(Object)) {
            auto object = dynamic_cast<Object *>(messageSender);
            senderGuiItem = dynamic_cast<ActivationGraphicsObjectBase *>(loadedObjects.find(object)->second);
        } else {
            throw std::logic_error{"Unknown message sender type"};
        }

        // Message recipient
        MessageNode *messageRecipient = objMessage->getMessageRecipient();
        ActivationGraphicsObjectBase *recipientGuiItem;
        ClassReference calleeClassReference{"ACTOR"};
        if (typeid(*messageRecipient) == typeid(Actor)) {
            auto actor = dynamic_cast<Actor *>(messageRecipient);
            recipientGuiItem = dynamic_cast<ActivationGraphicsObjectBase *>(loadedActors.find(actor)->second);
        } else if (typeid(*messageRecipient) == typeid(Object)) {
            auto object = dynamic_cast<Object *>(messageRecipient);
            recipientGuiItem = dynamic_cast<ActivationGraphicsObjectBase *>(loadedObjects.find(object)->second);

            calleeClassReference = object->getInstanceClass();
        } else {
            throw std::logic_error{"Unknown message recipient type"};
        }

        // Create and allocate message
        switch (objMessage->getType()) {
            case MessageType::SYNC:
                newMessageLine = new SyncMessageLine{&sequenceDiagram};
                break;
            case MessageType::ASYNC:
                newMessageLine = new AsyncMessageLine{&sequenceDiagram};
                break;
            case MessageType::CREATE:
                newMessageLine = new CreateMessageLine{&sequenceDiagram};
                break;
            case MessageType::DESTROY:
                newMessageLine = new DestroyMessageLine{&sequenceDiagram};
                break;
            case MessageType::REPLY:
                newMessageLine = new ReplyMessageLine{&sequenceDiagram};
                break;
        }

        newMessageLine->initialize(senderGuiItem, recipientGuiItem, objMessage, calleeClassReference);
        addItem(newMessageLine);
    }

    sceneUpdateObservable->sceneChanged();
}

/**
 * Moves recived object left.
 *
 * @param objectToMove object that will be moved left.
 */
void SequenceDiagramScene::moveObjectLeft(ActivationGraphicsObjectBase *objectToMove)
{
    QVector<ActivationGraphicsObjectBase *> activationItems = activationObjectsInScene();
    int index = activationItems.indexOf(objectToMove);
    if(index > 0)
    {
        int tempOrder = activationItems[index]->order;
        activationItems[index]->order = activationItems[index - 1]->order;
        activationItems[index - 1]->order = tempOrder;
        sortActivationItems();
    }

}

/**
 * Moves recieved object to right
 *
 * @param objectToMove object that will be move right.
 */
void SequenceDiagramScene::moveObjectRight(ActivationGraphicsObjectBase *objectToMove)
{
    QVector<ActivationGraphicsObjectBase *> activationItems = activationObjectsInScene();
    int index = activationItems.indexOf(objectToMove);
    if(index < activationItems.size() - 1)
    {
        int tempOrder = activationItems[index]->order;
        activationItems[index]->order = activationItems[index + 1]->order;
        activationItems[index + 1]->order = tempOrder;
        sortActivationItems();
    }
}

// Slots --------------------------------------------------------------------------------------------------------- Slots
/**
 * Function that informs this, that invokedBy, was clicked on.
 *
 * @param invokedBy newSender object
 */
void SequenceDiagramScene::objectPressed(ActivationGraphicsObjectBase *invokedBy)
{
    if (currentState == state::none) {
        return;
    } else if (currentState == state::objectRemoving) {
        removeHandle(invokedBy);
    } else if (currentState == state::messageCreation) {
        selectLinesHandle(invokedBy);
    }
}

/**
 * Edit my selected items
 */
void SequenceDiagramScene::selectionEdit()
{
    //adding new selected items
    QList<QGraphicsItem*> selected = selectedItems();
    for (QGraphicsItem * item: selected) {
        if (!mySelectedItems.contains(item)) {
            mySelectedItems.push_back(item);
        }
    }

    //removing new unselected items
    for (int i = 0; i < mySelectedItems.size(); i++) {
        if (!selected.contains(mySelectedItems[i])) {
            mySelectedItems.removeAt(i);
        }
    }
}

/**
 * Slot is used when emitted change() signal - if there is a different number of activation
 * objects, sort the objects.
 */
void SequenceDiagramScene::objectSortSlot(QList<QRectF>)
{
    static int activationObjectCount = 0;
    int currentCount = activationObjectsInScene().size();
    if (currentCount != activationObjectCount) {
        activationObjectCount = currentCount;
        sortActivationItems();
    }
}
