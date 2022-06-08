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
#include "AsyncMessageLine.h"
#include "CreateMessageLine.h"
#include "DestroyMessageLine.h"
#include "ReplyMessageLine.h"
#include "ActorGraphicsItem.h"
#include "ObjectGraphicsItem.h"
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
        sceneUpdateObservable{sceneUpdateObservable}, classDiagram{classDiagram},newMessageLine{nullptr}
{
    currentState = state::none;
    sequenceDiagram = new SequenceDiagram();
    connect(this, &SequenceDiagramScene::selectionChanged, this, &SequenceDiagramScene::selectionEdit);
    connect(this, &SequenceDiagramScene::changed, this, &SequenceDiagramScene::objectSortSlot);
}

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

/**
 * Add new actor to scene
 */
void SequenceDiagramScene::addActor()
{
    ActorGraphicsItem *actorItem = new ActorGraphicsItem();
    sequenceDiagram->addActor(actorItem->getActor());

    addItem(actorItem);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);
    sceneUpdateObservable->sceneChanged();
}

/**
 * Add new object to scene.
 */
void SequenceDiagramScene::addObject()
{
    Class *refferedClass = (classDiagram->getClasses().size() > 0)? classDiagram->getClasses()[0]:nullptr;
    ClassReference *classRef;
    if(refferedClass)
        classRef = new ClassReference(refferedClass);
    else
        classRef = new ClassReference("UNKNOWN CLASS");

    Object *newObject = new Object(*classRef);
    delete classRef;
    ObjectGraphicsItem *objectItem = new ObjectGraphicsItem(newObject, classDiagram);

    connect(&(objectItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    connect(&(objectItem->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);

    sequenceDiagram->addObject(newObject);
    addItem(objectItem);

    //user will set the object first
    objectItem->showEditDialog(false);
    sceneUpdateObservable->sceneChanged();
}

/**
 * Remove selected button was pressed. Handles an event - remove selected or change current state.
 */
void SequenceDiagramScene::removeObjectPressed()
{
    QList<QGraphicsItem *> selectedObjects = selectedItems();
    if(!selectedObjects.empty()) {
        removeSelectedObjects();
    } else {
        ActivationGraphicsObjectBase::setColor(firstPhaseSelectedColor);
        currentState = state::objectRemoving;
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
    for (QGraphicsItem *item : selectedObjects)
    {
        auto itemToRemove = dynamic_cast<ActivationGraphicsObjectBase*>(item);
        removeObject(itemToRemove, false);
    }

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
 * Handles what to do if in selction mode.
 *
 * @param ivokedBy Node that was pressed on.
 */
void SequenceDiagramScene::selectLinesHandle(ActivationGraphicsObjectBase *ivokedBy)
{
    if(ActivationGraphicsObjectBase::getColor() == firstPhaseSelectedColor)
    {
        sender = ivokedBy;
        ActivationGraphicsObjectBase::setColor(secondPhaseSelectedColor);
    }
    else
    {
        reciever = ivokedBy;
        ActivationGraphicsObjectBase::setColor(objectNormalColor);
        currentState = state::none;
        sendMessage();
    }
}

/**
 * Function that informs this, that invokedBy, was clicked on.
 *
 * @param invokedBy sender object
 */
void SequenceDiagramScene::objectPressed(ActivationGraphicsObjectBase *invokedBy)
{
    if (currentState == state::none)
        return;
    else if (currentState == state::objectRemoving)
        removeHandle(invokedBy);
    else if (currentState == state::messageCreation)
        selectLinesHandle(invokedBy);
}

/**
 * Removes single class node
 *
 * @param classNode Pointer to class node to remove
 */
void SequenceDiagramScene::removeObject(ActivationGraphicsObjectBase *activationObject, bool logChange)
{
    ObjectGraphicsItem *objectToRemove = dynamic_cast<ObjectGraphicsItem *>(activationObject);
    if(objectToRemove) //activationObject is Object
    {
        removeItem(objectToRemove);
        sequenceDiagram->removeObject(objectToRemove->getObject());
        delete objectToRemove;
    }
    else
    {
        ActorGraphicsItem *actorItem = dynamic_cast<ActorGraphicsItem *>(activationObject);
        removeItem(actorItem);
        sequenceDiagram->removeActor(actorItem->getActor());
        delete actorItem;
    }
    if(logChange)
        sceneUpdateObservable->sceneChanged();
}


/**
 * Checks if new line is nullptr (if no, deletes it) and insert messageline into newMessageLine
 *
 * @param line messageLine to store
 */
void SequenceDiagramScene::createNewMessageLine(MessageLine *line, MessageType type)
{
    delete newMessageLine;
    newMessageLine = line;
    newMessageLineType = type;
    //QList<QGraphicsItem *> items = selectedItems();
    if(mySelectedItems.count() == 2){
        sender = dynamic_cast<ActivationGraphicsObjectBase*>(mySelectedItems[0]);
        reciever = dynamic_cast<ActivationGraphicsObjectBase*>(mySelectedItems[1]);
        sendMessage();
    } else {
        clearSelection();
        ActivationGraphicsObjectBase::setColor(firstPhaseSelectedColor);
        currentState = state::messageCreation;
    }
}

/**
 * Connects two object by message
 */
void SequenceDiagramScene::sendMessage()
{
    // Create new messageline in scene
    ObjectGraphicsItem *objectReciever = dynamic_cast<ObjectGraphicsItem *>(reciever);
    MethodReference ref{""};
    if(objectReciever)
    {
        std::vector<ClassMethod> methods = objectReciever->getObject()->getInstanceClass()->getMethods();
        if(methods.size() > 0)
            ref = MethodReference{&(objectReciever->getObject()->getInstanceClass()->getMethods()[0])};
        else
            ref = MethodReference{"UNKNOWN METHOD"};
    }
    else
        ref = MethodReference{"UNKNOWN METHOD"};

    //check if is possible to create new line
    QString errorMsg = "";
    if(!createMessagePossible(&errorMsg, reciever, sender, newMessageLineType))
    {
        QMessageBox msgBox;
        msgBox.setText(errorMsg);
        msgBox.setWindowTitle("Creation was not succesful");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    Message *newMessage = new Message(ref, newMessageLineType, sender->getMessageNode(), reciever->getMessageNode(),0.0);

    ClassReference classRef{""};
    ObjectGraphicsItem *recieverObject = dynamic_cast<ObjectGraphicsItem *>(reciever);
    if(recieverObject)
        classRef = recieverObject->getObject()->getInstanceClass();

    newMessageLine->initialize(sender, reciever, newMessage, classRef);
    addItem(newMessageLine);

    // Store new message in squence diagram
    sequenceDiagram->addMessage(newMessage);
    sender = nullptr;
    reciever = nullptr;
    newMessageLine = nullptr;

    sceneUpdateObservable->sceneChanged();
}

/**
 * Edit my selected items
 */
void SequenceDiagramScene::selectionEdit()
{
    //adding new selected items
    QList<QGraphicsItem*> selected = selectedItems();
    for (QGraphicsItem * item: selected)
    {
        if(!mySelectedItems.contains(item))
            mySelectedItems.push_back(item);
    }

    //removing new unselected items
    for (int i = 0; i < mySelectedItems.size(); i++)
    {
        if(!selected.contains(mySelectedItems[i]))
            mySelectedItems.removeAt(i);
    }
}

/**
 * Return all activation items in scene, sorted by insertion order.
 *
 * @return QVector<ActivationGraphicsObjectBase *> all activation items in scene, sorted by insertion order.
 */
QVector<ActivationGraphicsObjectBase *> SequenceDiagramScene::activationObjectsInScene()
{
    QList<QGraphicsItem*> sceneItems = items(Qt::AscendingOrder);
    QVector<ActivationGraphicsObjectBase*> activationItems;
    for(QGraphicsItem* item : sceneItems)
    {
        ActivationGraphicsObjectBase *activationObject = dynamic_cast<ActivationGraphicsObjectBase *>(item);
        if(activationObject)
            activationItems.push_back(activationObject);
    }
    return activationItems;
}

/**
 * Sort all activation items in scene in x axis.
 */
void SequenceDiagramScene::sortActivationItems()
{
    QVector<ActivationGraphicsObjectBase *> activationItems = activationObjectsInScene();
    for(int i = 0; i < activationItems.size(); i++)
    {

        activationItems[i]->setPos( ActivationGraphicsObjectBase::objectPadding * i, 0);
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
    if (currentCount != activationObjectCount)
    {
        activationObjectCount = currentCount;
        sortActivationItems();
    }
}

/**
 * Checks if it is possible to create new message. If error occures, store message into errorMsg.
 *
 * @param errorMsg If error occurs, store error message there else errorMsg is unchanged.
 * @param reciever reciever object
 * @param messageType type of message
 * @return true if everything is ok.
 * @return false if creation is NOT possible.
 */
bool SequenceDiagramScene::createMessagePossible(QString *errorMsg,
        ActivationGraphicsObjectBase *reciever, ActivationGraphicsObjectBase *sender ,MessageType messageType)
{
    if(reciever == sender)
    {
        *errorMsg = "Reciever cannot be sender in one message!";
        return false;
    }

    ActorGraphicsItem *actor = dynamic_cast<ActorGraphicsItem*>(reciever);
    if(actor && (messageType == (MessageType)MessageType::CREATE || messageType == (MessageType)MessageType::DESTROY))
    {
        *errorMsg = "Actor cannot recieve any message of type <<create>> nor <<destroy>>!";
        return false;
    }
    else
    {
        ObjectGraphicsItem *obj = dynamic_cast<ObjectGraphicsItem *>(reciever);
        if(messageType == (MessageType)MessageType::DESTROY && obj->getDestroyMessage())
        {
            *errorMsg = "Object cannot recieve more than one destroy message!";
            return false;
        }
        else if (messageType == (MessageType)MessageType::CREATE && obj->getCreateMessage())
        {
            *errorMsg = "Object cannot recieve more than one create message!";
            return false;
        }
    }
    return true;
}
