/**
 * @file FileClassDiagramRepository.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include <QFile>
#include <QDomDocument>
#include <set>
#include "FileClassDiagramRepository.h"
#include "InvalidDataStorageException.h"
#include "InvalidInputDataException.h"
#include "DirectedAssociation.h"
#include "UndirectedAssociation.h"
#include "Aggregation.h"
#include "Generalization.h"
#include "Realization.h"

/**
 * Loads diagram from defined source
 *
 * @return Loaded class diagram
 * @throw InvalidDataStorageException Invalid file
 * @throw InvalidInputDataException Invalid structure of input data
 */
ClassDiagram FileClassDiagramRepository::loadDiagram()
{
    QFile file{fileName.c_str()};

    if (fileName.empty()) {
        throw InvalidDataStorageException{"No source file set"};
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw InvalidDataStorageException{"Cannot open source file"};
    }

    // Load data from XML file
    QDomDocument xml{};
    xml.setContent(&file);
    file.close();

    QDomElement rootElement{xml.documentElement()};
    if (rootElement.tagName() != "class-diagram") {
        throw InvalidInputDataException{"Invalid root element " + rootElement.tagName().toStdString()
            + R"(, "class-diagram" expected)"};
    }

    // Prepare empty ClassDiagram
    ClassDiagram classDiagram{};

    // Process classes
    QDomNodeList classesContainerSearch{rootElement.elementsByTagName("classes")};
    if (classesContainerSearch.size() != 1 || !classesContainerSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Exactly one "classes" element must be in root element)"};
    }

    QDomElement classesContainer{classesContainerSearch.item(0).toElement()};
    QDomNodeList classes{classesContainer.elementsByTagName("class")};
    if (classes.size() < 1 || classes.item(0).toElement().isNull()) {
        // Diagram is empty
        return classDiagram;
    }

    QDomElement curr_class{classes.item(0).toElement()};
    while (!curr_class.isNull()) {
        classDiagram.addClass(loadClass(curr_class));

        curr_class = curr_class.nextSiblingElement("class");
    }

    // Process relationships
    QDomNodeList relationshipsContainerSearch{rootElement.elementsByTagName("relationships")};
    if (relationshipsContainerSearch.size() > 1) {
        throw InvalidInputDataException{R"(Root element can contain at most 1 "relationships" element)"};
    }

    QDomElement relationshipsContainer{relationshipsContainerSearch.item(0).toElement()};
    if (relationshipsContainer.isNull()) {
        // There are no relationships, only classes
        return classDiagram;
    }

    QDomElement relationship{relationshipsContainer.firstChildElement()};
    while (!relationship.isNull()) {
        classDiagram.addRelationship(loadRelationship(relationship, classDiagram));

        relationship = relationship.nextSiblingElement();
    }

    return classDiagram;
}

/**
 * Saves diagram to defined target
 *
 * @param diagram Class diagram to save
 * @throw InvalidDataStorageException Invalid file
 */
void FileClassDiagramRepository::saveDiagram([[maybe_unused]] ClassDiagram diagram)
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No target file set"};
    }

    // TODO: implement this method
}

/**
 * Loads single class from XML element
 *
 * @param xmlClass XML element with class
 * @return Loaded class
 * @throw InvalidInputDataException Invalid structure of input data
 */
Class FileClassDiagramRepository::loadClass(QDomElement &xmlClass)
{
    // Class name
    if (!xmlClass.hasAttribute("name")) {
        throw InvalidInputDataException{R"("class" element must have mandatory attribute "name")"};
    }

    // Class coordinates
    if (!xmlClass.hasAttribute("x-coord") || !xmlClass.hasAttribute("y-coord")) {
        throw InvalidInputDataException{R"("class" element must have mandatory attributes "x-coord" and "y-coord")"};
    }

    bool xCoordConvOk;
    bool yCoordConvOk;
    std::tuple<int, int> coords{
        xmlClass.attribute("x-coord").toInt(&xCoordConvOk),
        xmlClass.attribute("y-coord").toInt(&yCoordConvOk)
    };

    if (!xCoordConvOk || !yCoordConvOk) {
        throw InvalidInputDataException{R"("x-coord" and "y-coord" attributes must contain valid integers)"};
    }

    // Class type
    ClassType classType{ClassType::NORMAL_CLASS};
    if (xmlClass.hasAttribute("type")) {
        // Class type is optional, default is NORMAL_CLASS
        try {
            classType = ClassType::deserialize(xmlClass.attribute("type").toStdString());
        } catch (std::invalid_argument &e) {
            throw InvalidInputDataException{R"(Invalid attribute "type" for element "class": )"
                                            + xmlClass.attribute("type").toStdString()};
        }
    }

    Class obj_class{xmlClass.attribute("name").toStdString(), coords, classType};

    // Class attributes
    QDomNodeList attributesContainerSearch{xmlClass.elementsByTagName("attributes")};
    if (attributesContainerSearch.size() > 1) {
        throw InvalidInputDataException{R"("class" element can have only one "attributes" element)"};
    }

    if (attributesContainerSearch.size() == 1 && attributesContainerSearch.item(0).isElement()) {
        // There could be some attributes to process
        QDomElement attributesContainer{attributesContainerSearch.item(0).toElement()};
        QDomNodeList attributes{attributesContainer.elementsByTagName("attribute")};
        if (attributes.size() > 0 && !attributes.item(0).isNull()) {
            QDomElement xml_attribute{attributes.item(0).toElement()};
            while (!xml_attribute.isNull()) {
                obj_class.addAttribute(loadAttribute(xml_attribute));

                xml_attribute = xml_attribute.nextSiblingElement("attribute");
            }
        }
    }

    // Class methods
    QDomNodeList methodsContainerSearch{xmlClass.elementsByTagName("methods")};
    if (methodsContainerSearch.size() > 1) {
        throw InvalidInputDataException{R"("class" element can have only one "methods" element)"};
    }

    if (methodsContainerSearch.size() == 1 && methodsContainerSearch.item(0).isElement()) {
        // There could be some methods to process
        QDomElement methodsContainer{methodsContainerSearch.item(0).toElement()};
        QDomNodeList methods{methodsContainer.elementsByTagName("method")};
        if (methods.size() > 0 && !methods.item(0).isNull()) {
            QDomElement xml_method{methods.item(0).toElement()};
            while (!xml_method.isNull()) {
                obj_class.addMethod(loadMethod(xml_method));

                xml_method = xml_method.nextSiblingElement("method");
            }
        }
    }

    return obj_class;
}

/**
 * Loads single class attribute from XML element
 *
 * @param xmlAttribute XML element with attribute
 * @return Loaded class attribute
 * @throw InvalidInputDataException Invalid structure of input data
 */
ClassAttribute FileClassDiagramRepository::loadAttribute(QDomElement &xmlAttribute)
{
    // Access modifier
    if (!xmlAttribute.hasAttribute("access-modifier")) {
        throw InvalidInputDataException{R"(Element "attribute" must have "access-modifier" attribute")"};
    }

    std::string accessModifierString{xmlAttribute.attribute("access-modifier").toStdString()};
    AccessModifier accessModifier{};
    try {
        accessModifier = AccessModifier::deserialize(accessModifierString);
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException{R"(Invalid value for attribute "access-modifier" of element
            "attribute": )" + accessModifierString};
    }

    // Data type
    if (!xmlAttribute.hasAttribute("data-type")) {
        throw InvalidInputDataException{R"(Element "attribute" must have "data-type" attribute)"};
    }

    std::string dataType{xmlAttribute.attribute("data-type").toStdString()};

    // Name
    if (xmlAttribute.text().isEmpty()) {
        throw InvalidInputDataException{R"(Element "attribute" must contain name of attribute)"};
    }

    std::string name{xmlAttribute.text().toStdString()};

    return ClassAttribute{name, accessModifier, dataType};
}

/**
 * Loads single class method from XML element
 *
 * @param xmlMethod XML element with method
 * @return Loaded class method
 * @throw InvalidInputDataException Invalid structure of input data
 */
ClassMethod FileClassDiagramRepository::loadMethod(QDomElement &xmlMethod) {
    // Name
    if (!xmlMethod.hasAttribute("name")) {
        throw InvalidInputDataException{R"(Element "method" must have "name" attribute)"};
    }

    // Access modifier
    if (!xmlMethod.hasAttribute("access-modifier")) {
        throw InvalidInputDataException{R"(Element "method" must have "access-modifier" attribute")"};
    }

    std::string accessModifierString{xmlMethod.attribute("access-modifier").toStdString()};
    AccessModifier accessModifier{};
    try {
        accessModifier = AccessModifier::deserialize(accessModifierString);
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException{R"(Invalid value for attribute "access-modifier" of element
            "method": )" + accessModifierString};
    }

    // Return data type
    std::string returnType{"void"};
    if (xmlMethod.hasAttribute("return-type")) {
        returnType = xmlMethod.attribute("return-type").toStdString();
    }

    // Type
    ClassMethodType methodType{ClassMethodType::NORMAL};
    if (xmlMethod.hasAttribute("type")) {
        std::string methodTypeString{xmlMethod.attribute("type").toStdString()};
        try {
            methodType = ClassMethodType::deserialize(methodTypeString);
        } catch (std::invalid_argument &e) {
            throw InvalidInputDataException{R"(Invalid value for attribute "type" of element "method:")"
                                            + methodTypeString};
        }
    }

    // Parameters
    QDomElement xmlParameter{xmlMethod.firstChildElement("parameter")};
    std::vector<MethodParameter> objParams{};
    while (!xmlParameter.isNull()) {
        // Parameter data type
        if (!xmlParameter.hasAttribute("data-type")) {
            throw InvalidInputDataException{R"(Element "parameter" must have "data-type" attribute)"};
        }

        std::string paramDataType{xmlParameter.attribute("data-type").toStdString()};

        // Parameter name
        if (xmlParameter.text().isEmpty()) {
            throw InvalidInputDataException{R"(Element "parameter" must contain name of parameter)"};
        }

        std::string paramName{xmlParameter.text().toStdString()};

        objParams.emplace_back(paramName, paramDataType);

        xmlParameter = xmlParameter.nextSiblingElement("parameter");
    }

    return ClassMethod{
            xmlMethod.attribute("name").toStdString(),
            accessModifier,
            objParams,
            returnType,
            methodType
    };
}

/**
 * Loads single relationship from XML element
 *
 * @param xmlRelationship XML element with relationship
 * @param classDiagram Class diagram with classes (of course without relationships)
 * @return Pointer to loaded relationship (due to more sizes of result objects)
 * @throw InvalidInputDataException Invalid structure of input data
 */
Relationship *FileClassDiagramRepository::loadRelationship(QDomElement &xmlRelationship, ClassDiagram &classDiagram)
{
    static std::set<std::string> validRelationships{
        "aggregation",
        "composition",
        "directed-association",
        "generalization",
        "realization",
        "undirected-association"
    };

    // Check relationship name
    auto foundRelationship{validRelationships.find(xmlRelationship.tagName().toStdString())};
    if (foundRelationship == validRelationships.end()) {
        throw InvalidInputDataException{
            R"(Element "relationships" can contains only elements: "directed-association", )"
            R"(undirected-association", "aggregation", "composition", "generalization", "realization)"};
    }

    // Name
    std::string name{};
    if (xmlRelationship.hasAttribute("name")) {
        name = xmlRelationship.attribute("name").toStdString();
    }

    // First class
    QDomNodeList firstClassSearch{xmlRelationship.elementsByTagName("first-class")};
    if (firstClassSearch.size() != 1 || !firstClassSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element ")" + name + R"(" must contain exactly 1 element "first-class")"};
    }

    QDomElement xmlFirstClass{firstClassSearch.item(0).toElement()};
    Class *objFirstClass;
    try {
        objFirstClass = classDiagram.findClassByName(xmlFirstClass.text().toStdString());
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException{R"(Attribute "first-class" must contain name of some class from class)"
            "diagram"};
    }

    // Second class
    QDomNodeList secondClassSearch{xmlRelationship.elementsByTagName("second-class")};
    if (secondClassSearch.size() != 1 || !secondClassSearch.item(0).isElement()) {
        throw InvalidInputDataException{R"(Element ")" + name + R"(" must contain exactly 1 element "second-class")"};
    }

    QDomElement xmlSecondClass{secondClassSearch.item(0).toElement()};
    Class *objSecondClass;
    try {
        objSecondClass = classDiagram.findClassByName(xmlSecondClass.text().toStdString());
    } catch (std::invalid_argument &e) {
        throw InvalidInputDataException{R"(Attribute "second-class" must contain name of some class from class)"
            "diagram"};
    }

    // Prepare cardinalities for undirected association
    std::string firstClassCardinality{};
    std::string secondClassCardinality{};

    // Construct the corresponding relationship
    switch (std::distance(validRelationships.begin(), foundRelationship)) {
        case 0:
            // Directed association
            return new DirectedAssociation{objFirstClass, objSecondClass, name};
        case 1:
            // Undirected association

            // First class's cardinality
            if (xmlFirstClass.hasAttribute("cardinality")) {
                firstClassCardinality = xmlFirstClass.attribute("cardinality").toStdString();
            }

            // Second class's cardinality
            if (xmlSecondClass.hasAttribute("cardinality")) {
                secondClassCardinality = xmlSecondClass.attribute("cardinality").toStdString();
            }

            return new UndirectedAssociation{
                objFirstClass,
                objSecondClass,
                name,
                firstClassCardinality,
                secondClassCardinality
            };
        case 2:
            // Aggregation
            return new Aggregation{objFirstClass, objSecondClass, name};
        case 3:
            // Composition
            return new Composition{objFirstClass, objSecondClass, name};
        case 4:
            // Generalization
            return new Generalization{objFirstClass, objSecondClass, name};
        case 5:
            // Realization
            return new Realization{objFirstClass, objSecondClass, name};
    }

    // Should be dead code but compiler needs to have return or thrown here
    throw InvalidInputDataException{};
}
