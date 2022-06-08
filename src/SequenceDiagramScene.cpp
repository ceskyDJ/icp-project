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
    actorItem->setPos(ActivationGraphicsObjectBase::objectPadding * actorItem->getObjectCounter(), 0);

    sequenceDiagram->addActor(actorItem->getActor());

    addItem(actorItem);
    connect(&(actorItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    sceneUpdateObservable->sceneChanged();
}

/**
 * Add new object to scene.
 */
void SequenceDiagramScene::addObject()
{
    /*if(refferedClass == nullptr && classDiagram->getClasses().size() > 0)
        refferedClass = classDiagram->getClasses()[0];
    else if (classDiagram->getClasses().size() == 0)
        refferedClass = */

    Class *refferedClass = (classDiagram->getClasses().size() > 0)? classDiagram->getClasses()[0]:nullptr;
    ClassReference *classRef; //because no constructor without params exists
    if(refferedClass)
        classRef = new ClassReference(refferedClass);
    else
        classRef = new ClassReference("UNKNOWN CLASS");

    Object *newObject = new Object(*classRef);
    delete classRef;
    ObjectGraphicsItem *objectItem = new ObjectGraphicsItem(newObject);

    objectItem->setPos(ActivationGraphicsObjectBase::objectPadding * objectItem->getObjectCounter(), 0);

    connect(&(objectItem->emitter), &ActivationObjectEmitter::objectPressed, this, &SequenceDiagramScene::objectPressed);
    connect(&(objectItem->emitter), &ActivationObjectEmitter::removeObject, this, &SequenceDiagramScene::removeObject);

    sequenceDiagram->addObject(newObject);
    addItem(objectItem);
    //user will set the dialog first
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
    MethodReference *ref;
    if(objectReciever)
    {
        std::vector<ClassMethod> methods = objectReciever->getObject()->getInstanceClass()->getMethods();
        if(methods.size() > 0)
            ref = new MethodReference(&(objectReciever->getObject()->getInstanceClass()->getMethods()[0]));
        else
            ref = new MethodReference("UNKNOWN METHOD");
    }
    else
        ref = new MethodReference("UNKNOWN METHOD");

    Message *newMessage = new Message(*ref, newMessageLineType, sender->getMessageNode(), reciever->getMessageNode(),0.0);
    delete ref;
    newMessageLine->initialize(sender, reciever, newMessage);
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
