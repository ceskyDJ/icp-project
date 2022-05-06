/**
 * @file FileSequenceDiagramRepository.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include <QFile>
#include <QIODevice>
#include <QDomDocument>
#include "FileSequenceDiagramRepository.h"
#include "InvalidDataStorageException.h"
#include "InvalidInputDataException.h"

/**
 * Loads diagram from defined source
 *
 * @return Loaded sequence diagram
 * @throw InvalidDataStorageException Invalid file
 * @throw InvalidInputDataException Invalid structure of input data
 */
SequenceDiagram FileSequenceDiagramRepository::loadDiagram()
{
    QFile file{fileName.c_str()};

    if (fileName.empty()) {
        throw InvalidDataStorageException{"No source file set"};
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.close();
        throw InvalidDataStorageException{"Cannot open source file"};
    }

    // Load data from XML file
    QDomDocument xml{};
    xml.setContent(&file);
    file.close();

    QDomElement rootElement{xml.documentElement()};
    if (rootElement.tagName() != "sequence-diagram") {
        throw InvalidInputDataException{"Invalid root element " + rootElement.tagName().toStdString()
            + R"(, "sequence-diagram" expected)"};
    }

    // Prepare empty ClassDiagram
    SequenceDiagram sequenceDiagram{};

    // Process actors
    QDomNodeList actorsContainerSearch{rootElement.elementsByTagName("actors")};
    if (actorsContainerSearch.size() != 1 || !actorsContainerSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element "sequence-diagram" must contain exactly 1 element "actors")"};
    }

    QDomElement actorsContainer{actorsContainerSearch.item(0).toElement()};
    QDomNodeList actors{actorsContainer.elementsByTagName("actor")};

    QDomElement xmlActor{actors.item(0).toElement()};
    while (!xmlActor.isNull()) {
        // Name
        if (xmlActor.text().isEmpty()) {
            throw InvalidInputDataException{R"(Element "actor" must contain actor's name)"};
        }

        Actor objActor{xmlActor.text().toStdString()};
        sequenceDiagram.addActor(objActor);

        xmlActor = xmlActor.nextSiblingElement("actor");
    }

    // Process objects
    QDomNodeList objectsContainerSearch{rootElement.elementsByTagName("objects")};
    if (objectsContainerSearch.size() != 1 || !objectsContainerSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element "sequence-diagram" must contain exactly 1 element "objects")"};
    }

    QDomElement objectsContainer{objectsContainerSearch.item(0).toElement()};
    QDomNodeList objects{objectsContainer.elementsByTagName("object")};

    QDomElement xmlObject{objects.item(0).toElement()};
    while (!xmlObject.isNull()) {
        sequenceDiagram.addObject(loadObject(xmlObject));

        xmlObject = xmlObject.nextSiblingElement("object");
    }

    // Process messages
    QDomNodeList messagesContainerSearch{rootElement.elementsByTagName("messages")};
    if (messagesContainerSearch.size() != 1 || !messagesContainerSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element "sequence-diagram" must contain exactly 1 element "messages")"};
    }

    QDomElement messagesContainer{messagesContainerSearch.item(0).toElement()};
    QDomNodeList messages{messagesContainer.elementsByTagName("message")};

    QDomElement xmlMessage{messages.item(0).toElement()};
    while (!xmlMessage.isNull()) {
        sequenceDiagram.addMessage(loadMessage(xmlMessage, sequenceDiagram));

        xmlMessage = xmlMessage.nextSiblingElement("message");
    }

    return sequenceDiagram;
}

/**
 * Saves diagram to defined target
 *
 * @param diagram Sequence diagram to save
 * @throw InvalidDataStorageException Invalid file
 */
void FileSequenceDiagramRepository::saveDiagram([[maybe_unused]] SequenceDiagram diagram)
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No target file set"};
    }

    // TODO: implement this method
}

/**
 * Loads single object from XML element
 *
 * @param xmlObject XML element with object
 * @return Loaded object
 * @throw InvalidInputDataException Invalid structure of input data
 */
Object FileSequenceDiagramRepository::loadObject(QDomElement &xmlObject)
{
    // Instance class
    if (!xmlObject.hasAttribute("instance-class")) {
        throw InvalidInputDataException{R"(Element "object" must have mandatory attribute "instance-class")"};
    }

    Class *instanceClass;
    try {
        instanceClass = classDiagram.findClassByName(xmlObject.attribute("instance-class").toStdString());
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException(R"(Attribute "instance-class" of element "object" must contain)"
                                        R"(name of class existing in linked class diagram)");
    }

    // Life start
    if (!xmlObject.hasAttribute("life-start")) {
        throw InvalidInputDataException{R"(Element "object" must have mandatory attribute "life-start")"};
    }

    bool lifeStartConvOk;
    double lifeStart = xmlObject.attribute("life-start").toDouble(&lifeStartConvOk);
    if (!lifeStartConvOk) {
        throw InvalidInputDataException{R"(Value of attribute "life-start" must be valid decimal)"};
    }

    // Life end
    if (!xmlObject.hasAttribute("life-length")) {
        throw InvalidInputDataException{R"(Element "object" must have mandatory attribute "life-length")"};
    }

    bool lifeLengthConvOk;
    double lifeLength = xmlObject.attribute("life-length").toDouble(&lifeLengthConvOk);
    if (!lifeLengthConvOk) {
        throw InvalidInputDataException{R"(Value of attribute "life-length" must be valid decimal)"};
    }

    // Name
    if (xmlObject.text().isEmpty()) {
        throw InvalidInputDataException{R"(Element "object" must contain object name)"};
    }

    return Object{instanceClass, lifeStart, lifeLength, xmlObject.text().toStdString()};
}

/**
 * Loads single message from XML element
 *
 * @param xmlMessage XML element with message
 * @param sequenceDiagram Sequence diagram for linking objects and actors
 * @return Loaded message
 * @throw InvalidInputDataException Invalid structure of input data
 */
Message FileSequenceDiagramRepository::loadMessage(QDomElement &xmlMessage, SequenceDiagram &sequenceDiagram)
{
    // Name
    if (!xmlMessage.hasAttribute("name")) {
        throw InvalidInputDataException{R"(Element "message" must have mandatory attribute "name")"};
    }

    std::string name{xmlMessage.attribute("name").toStdString()};

    // Message type
    if (!xmlMessage.hasAttribute("type")) {
        throw InvalidInputDataException{R"(Element "message" must have mandatory attribute "type")"};
    }

    MessageType type;
    try {
        type = MessageType::deserialize(xmlMessage.attribute("type").toStdString());
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException{R"(Attribute "type" of element "message" must be one of: )"
            "SYNC, ASYNC, CREATE, DESTROY, REPLY"};
    }

    // Sending time
    if (!xmlMessage.hasAttribute("sending-time")) {
        throw InvalidInputDataException{R"(Element "message" must have mandatory attribute "sending-time")"};
    }

    bool convOk;
    double sendingTime = xmlMessage.attribute("sending-time").toDouble(&convOk);
    if (!convOk) {
        throw InvalidInputDataException{R"(Attribute "sending-time" of element "message" must be valid decimal)"};
    }

    // Message sender
    QDomNodeList senderSearch{xmlMessage.elementsByTagName("sender")};
    if (senderSearch.size() != 1 || !senderSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element "message" must contain exactly 1 element "sender")"};
    }

    QDomElement sender{senderSearch.item(0).toElement()};
    if (!sender.hasAttribute("type")) {
        throw InvalidInputDataException{R"(Element "sender" must have mandatory attribute "type")"};
    }

    if (sender.text().isEmpty()) {
        throw InvalidInputDataException{R"(Element "sender" must contain name of sending actor/object)"};
    }

    std::string senderName{sender.text().toStdString()};

    std::string senderType{sender.attribute("type").toStdString()};
    MessageNode *messageSender;
    if (senderType == "ACTOR") {
        messageSender = sequenceDiagram.findActorByName(senderName);
    } else if (senderType == "OBJECT") {
        messageSender = sequenceDiagram.findObjectByName(senderName);
    } else {
        throw InvalidInputDataException{R"(Attribute "type" of element "sender" must be one of: ACTOR, OBJECT)"};
    }

    // Message recipient
    QDomNodeList recipientSearch{xmlMessage.elementsByTagName("recipient")};
    if (recipientSearch.size() != 1 || !recipientSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element "message" must contain exactly 1 element "recipient")"};
    }

    QDomElement recipient{recipientSearch.item(0).toElement()};
    if (!recipient.hasAttribute("type")) {
        throw InvalidInputDataException{R"(Element "recipient" must have mandatory attribute "type")"};
    }

    if (recipient.text().isEmpty()) {
        throw InvalidInputDataException{R"(Element "recipient" must contain name of receiving actor/object)"};
    }

    std::string recipientName{recipient.text().toStdString()};

    std::string recipientType{recipient.attribute("type").toStdString()};
    MessageNode *messageRecipient;
    if (recipientType == "ACTOR") {
        messageRecipient = sequenceDiagram.findActorByName(recipientName);
    } else if (recipientType == "OBJECT") {
        messageRecipient = sequenceDiagram.findObjectByName(recipientName);
    } else {
        throw InvalidInputDataException{R"(Attribute "type" of element "recipient" must be one of: ACTOR, OBJECT)"};
    }

    if (typeid(*messageSender) == typeid(Actor) && typeid(*messageRecipient) == typeid(Object)) {
        return Message{name, type, dynamic_cast<Actor *>(messageSender), dynamic_cast<Object *>(messageRecipient), sendingTime};
    } else if (typeid(*messageSender) == typeid(Object) && typeid(*messageRecipient) == typeid(Object)) {
        return Message{name, type, dynamic_cast<Object *>(messageSender), dynamic_cast<Object *>(messageRecipient), sendingTime};
    } else if (typeid(*messageSender) == typeid(Object) && typeid(*messageRecipient) == typeid(Actor)) {
        return Message{name, type, dynamic_cast<Object *>(messageSender), dynamic_cast<Actor *>(messageRecipient), sendingTime};
    } else {
        throw InvalidInputDataException{R"(Invalid combination of types of message sender and message recipient)"};
    }
}
