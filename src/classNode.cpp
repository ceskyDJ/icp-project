/**
 * @file classNode.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * Některé funkce byly inspirovány příklady od Petra Peringera
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include "classNode.h"
#include "qpainter.h"
#include "QPlainTextEdit"
#include <QStyleOptionGraphicsItem>
#include <iostream>
#include "ClassEditDialog.h"
#include "GeneralizationLine.h"
#include "Line.h"
#include "SceneUpdateObservable.h"
#include "AccessModifier.h"
#include "ClassNodeEmmitor.h"

/**
 * Sets a class node entity.
 *
 * @param classEntity Class which is going to be drawn
 * @param existingClasses Classes existing in diagram
 * @param sceneUpdateObservable Observable for notifying about scene changes
 */
ClassNode::ClassNode(
    Class *classEntity,
    std::unordered_map<std::string, ClassNode *> *existingClasses,
    SceneUpdateObservable *sceneUpdateObservable
): classEntity{classEntity}, existingClasses{existingClasses}, sceneUpdateObservable{sceneUpdateObservable}
{
    emitor = new ClassNodeEmmitor(nullptr, this);

    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);

    // Set initial position
    auto classCoords = classEntity->getCoordinates();
    setPos(std::get<0>(classCoords), std::get<1>(classCoords));

    prepareGeometryChange();
    update();
}

/**
 * Override method which returns bounding rect of classNode.
 *
 * @return QRectF A rectnagle around classNode.
 */
QRectF ClassNode::boundingRect() const
{
    return getWholeRect();
}

/**
 * Draws a classNode - overrride method of QGraphicsItem.
 *
 * @param painter Painter that will be used to draw node.
 */
void ClassNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget * /*widget*/)
{
    QPen pen;
    if(option->state & QStyle::State_Selected)
        pen = QPen{Qt::red,3,Qt::DotLine};
    else
        pen = QPen{borderColor, 2, Qt::SolidLine};

    if (classEntity->getClassType() == (ClassType)ClassType::ABSTRACT_CLASS)
        setFontItalic(true, painter);

    painter->setPen(pen);

    QRectF nameRect = getNameBoundigRect();
    int incHeight = nameRect.height();
    std::vector<QString> attributeVector = getAttributePrintable();
    std::vector<int> inheritedMethods(0);
    std::vector<QString> methodVector = getMethodPrintable(&inheritedMethods);
    QRectF wholeRect = getWholeRect(attributeVector, methodVector);

    int maxWidth = wholeRect.width();
    nameRect.setLeft(wholeRect.x());
    nameRect.setTop(wholeRect.y());

    nameRect.setWidth(maxWidth);
    nameRect.setHeight(nameRect.height() + Padding);
    if(classEntity->getClassType() == (ClassType)ClassType::INTERFACE)
    {
        painter->drawText(nameRect, Qt::AlignHCenter,"<<interface>>");
        nameRect.setHeight(nameRect.height() + incHeight);
    }
    painter->drawRect(nameRect);
    painter->drawText(nameRect, Qt::AlignCenter, QString::fromStdString(classEntity->getName()));

    if (classEntity->getClassType() == (ClassType)ClassType::ABSTRACT_CLASS)
        setFontItalic(false, painter);

    QRectF incrementalRect = nameRect;
    incrementalRect.setHeight(nameRect.height() + lineIndent);
    for(QString &atributeToPrint : attributeVector)
    {
        incrementalRect.setHeight(incrementalRect.height() + incHeight);
        painter->drawText(incrementalRect, Qt::AlignBottom, atributeToPrint);
    }

    painter->drawRect(incrementalRect);
    incrementalRect.setHeight(incrementalRect.height() + lineIndent);

    std::vector<ClassMethod> methodEntities = classEntity->getMethods();
    for(int i = 0; static_cast<size_t>(i) < methodVector.size(); i++)
    {
        if(methodEntities[i].getType() == (ClassMethodType)ClassMethodType::ABSTRACT)
            setFontItalic(true, painter);
        QColor penOriginColor = pen.color();
        if(std::find(inheritedMethods.begin(), inheritedMethods.end(), i) != inheritedMethods.end())//metoda je zdedena
        {
            pen.setColor(Qt::darkYellow);
            painter->setPen(pen);
        }
        incrementalRect.setHeight(incrementalRect.height() + incHeight);

        painter->drawText(incrementalRect, Qt::AlignBottom, methodVector[i]);

        pen.setColor(penOriginColor);
        painter->setPen(pen);

        if(methodEntities[i].getType() == (ClassMethodType)ClassMethodType::ABSTRACT)
            setFontItalic(false, painter);
    }
    painter->drawRect(incrementalRect);
}

/**
 * Counts and returns boundigrect of className attribute.
 *
 * @return QRectF Rectangle of classNode.
 */
QRectF ClassNode::getNameBoundigRect() const
{
    QFontMetricsF metrics{qApp->font()};
    QRectF rect = metrics.boundingRect(QString::fromStdString(classEntity->getName()));
    return rect;
}

/**
 * Counts and returns a whole rect of ClassNode.
 *
 * @return QRectF - whole rect of ClassNode.
 */
QRectF ClassNode::getWholeRect() const
{
    std::vector<QString> attributePrintable = getAttributePrintable();
    std::vector<QString> methodPrintable = getMethodPrintable();
    return getWholeRect(attributePrintable, methodPrintable);
}

/**
 * Counts and returns a whole rect of ClassNode.
 *
 * @param attributePrintable QStrings of all class attributes
 * @return QRectF - whole rect of ClassNode.
 */
QRectF ClassNode::getWholeRect(std::vector<QString> &attributePrintable,
                               std::vector<QString> &methodPrintable) const
{
    QFontMetricsF metrics{qApp->font()};
    QRectF nameRect = metrics.boundingRect(QString::fromStdString(classEntity->getName()));

    int maxWidth = nameRect.width();
    getMaxWidth(attributePrintable, &maxWidth);
    getMaxWidth(methodPrintable, &maxWidth);
    maxWidth += Padding * 2;

    QRectF wholeRect = nameRect;
    wholeRect.setWidth(maxWidth);
    wholeRect.setHeight(nameRect.height() + 2 * lineIndent + nameRect.height() * attributePrintable.size()
                        + nameRect.height() * methodPrintable.size());
    wholeRect.adjust(0, -Padding, 0, Padding);
    if(classEntity->getClassType() == (ClassType)ClassType::INTERFACE)
        wholeRect.setHeight(wholeRect.height() + nameRect.height() );
    return wholeRect;
}

/**
 * Counts a max width of rectangle around the strings in param toCompare and saves it into maxWidth.
 *
 * @param toCompare Vector of strings which should be compared.
 * @param maxWidth A pointer to variable of type int, where will be stored max width.
 */
void ClassNode::getMaxWidth(std::vector<QString> toCompare, int *maxWidth) const
{
    QFontMetricsF metrics{qApp->font()};
    for(QString &str : toCompare)
    {
        if(*maxWidth < metrics.boundingRect(str).width())
            *maxWidth = metrics.boundingRect(str).width();
    }
}

/**
 * Makes and returns all attributes of class prepared to print (+AttName:dataType).
 *
 * @return Vector of all class attributes prepared to print.
 */
std::vector<QString> ClassNode::getAttributePrintable() const
{
    std::vector<ClassAttribute> attributes = classEntity->getAttributes();
    std::vector<QString> attributeString(attributes.size());

    for(size_t i = 0; i < attributes.size(); i++)
    {
        QString accesModifier = QString::fromStdString(std::string(attributes[i].getAccessModifier()));
        QString attributeName = QString::fromStdString(attributes[i].getName());
        QString attributeType = QString::fromStdString(attributes[i].getDataType());

        attributeString[i] = "  " + accesModifier + attributeName + ":" + attributeType;
    }
    return attributeString;
}

/**
 * Makes and returns all methods of class prepared to print ( +MethodName(params...) ).
 *
 * @return Vector of all class methods prepared to print.
 */
std::vector<QString> ClassNode::getMethodPrintable(
        std::vector<int> *inheritedIndexes) const
{
    std::vector<ClassMethod> methods = classEntity->getMethods();
    std::vector<QString> methodString(methods.size());

    for(size_t i = 0; i < methods.size(); i++)
    {
        QString accesModifier = QString::fromStdString(std::string(methods[i].getAccessModifier()));
        QString methodName = QString::fromStdString(methods[i].getName());
        QString parameterString = getMethodParametersPrintable(methods[i].getParameters());
        QString returnType = QString::fromStdString(methods[i].getReturnDataType());

        if(isMethodInherited(methodName))
            inheritedIndexes->push_back((int)i);

        methodString[i] = "  " + accesModifier + methodName + "(" + parameterString + ")" + " : " + returnType;
    }
    return methodString;
}

/**
 * Joins all method's parameters to printable representation.
 *
 * @param parameters
 * @return
 */
QString ClassNode::getMethodParametersPrintable(std::vector<MethodParameter> parameters) const
{
    QString methodString = "";
    for (size_t i = 0; i < parameters.size(); i++)
    {
        methodString += QString::fromStdString(parameters[i].getName() + " : " + parameters[i].getDataType());
        if (i + 1 != parameters.size())
            methodString += ", ";
    }
    return methodString;
}

/**
 * @brief ClassNode::mouseDoubleClickEvent Handles double click event - shows eddit dialog, then changes entity.
 */
void ClassNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    Class newClassEntity{*classEntity};
    auto *classEditDialog = new ClassEditDialog(&newClassEntity);

    if (classEditDialog->exec() == QDialog::Accepted) {
        // Propagate name change to existing classes map
        if (classEntity->getName() != newClassEntity.getName()) {
            // Delete old key with this class node
            auto itemForDeletion = existingClasses->find(classEntity->getName());
            existingClasses->erase(itemForDeletion);

            // Add this class node with updated key
            existingClasses->insert({newClassEntity.getName(), this});
        }

        // Update class entity
        if (*classEntity != newClassEntity) {
            *classEntity = newClassEntity;
            update();
        }
    }
}

/**
 * Event handler for mouse release event
 *
 * @param event Event details
 */
void ClassNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    emitor->emitNodePresed();

    if (isMoved) {
        sceneUpdateObservable->sceneChanged();

        isMoved = false;
    }
}

/**
 * Event handler for mouse move event
 *
 * @param event Event details
 */
void ClassNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    isMoved = true;
}

/**
 * @brief ClassNode::setFontItalic sets font to italic or to normal
 * @param enable true = italic, false = normal
 * @param painter pointer to painter that should be eddited
 */
void ClassNode::setFontItalic(bool enable, QPainter *painter)
{
    QFont font = painter->font();
    font.setItalic(enable);
    painter->setFont(font);
}

/**
 * @brief ClassNode::addLine adds new connections
 * @param newLine line to connect
 */
void ClassNode::addLine(Line* newLine)
{
    connectedLines.insert(newLine);
}

/**
 * @brief ClassNode::removeLine removes line form connected list
 * @param oldLine line to remove
 */
void ClassNode::removeLine(Line* oldLine)
{
    connectedLines.remove(oldLine);
}

/**
 * @brief ClassNode::rePaintLines Paints a line again
 */
void ClassNode::rePaintLines()
{
    for(Line *line : connectedLines)
        line->drawLine();
}

/**
 * @brief ClassNode::itemChange When item is changed then repaint it
 * @param change GraphicsItemChange
 * @param value const QVariant
 * @return itemchange
 */
QVariant ClassNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        // Update coordinates in entity
        QPoint newPoint{value.toPoint()};
        std::tuple<int, int> newCoords{newPoint.x(), newPoint.y()};
        classEntity->setCoordinates(newCoords);

        rePaintLines();

        // FIXME: Generates too many mementos
//        sceneUpdateObservable->sceneChanged();
    }

    return QGraphicsItem::itemChange(change, value);
}

/**
 * Checks if method is inherited from another (by name)
 *
 * @param methodName Method that is being checked.
 * @return if method is inherited than returns true otherwise retrun false;
 */
bool ClassNode::isMethodInherited(QString methodName) const
{
    QVector<ClassNode *> generalisations(QVector<ClassNode *>(0));
    for (Line * relationship: connectedLines)
    {
        GeneralizationLine *temp = (GeneralizationLine *)relationship;
        if(temp && temp->getToClassNode() != this)
            generalisations.push_back(temp->getToClassNode());
    }

    for(ClassNode *node: generalisations)
    {
        if (node->getClassEntity()->findMethodByName(methodName.toStdString()) != nullptr)
            return true;
    }

    return false;
}
