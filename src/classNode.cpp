#include "classNode.h"
#include "qpainter.h"
#include "QPlainTextEdit"
#include <QStyleOptionGraphicsItem>
#include "ClassEditDialog.h"

/**
 * Sets a class node entity.
 *
 * @param classEntity Class which is going to be drawn.
 */
ClassNode::ClassNode(Class classEntity)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    ClassNode::classEntity = classEntity;
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
        pen = QPen{Qt::red,2,Qt::DotLine};

    else
        pen = QPen{Qt::black,1,Qt::SolidLine};
    painter->setPen(pen);

    QRectF nameRect = getNameBoundigRect();
    int incHeight = nameRect.height();
    std::vector<QString> attributeVector = getAttributePrintable();
    std::vector<QString> methodVector = getMethodPrintable();
    QRectF wholeRect = getWholeRect(attributeVector, methodVector);

    int maxWidth = wholeRect.width();

    nameRect.setWidth(maxWidth);
    nameRect.setHeight(nameRect.height() + Padding);
    painter->drawRect(nameRect);
    painter->drawText(nameRect, Qt::AlignCenter, QString::fromStdString(classEntity.getName()));

    QRectF incrementalRect = nameRect;
    incrementalRect.setHeight(nameRect.height() + lineIndent);
    for(QString &atributeToPrint : attributeVector)
    {
        incrementalRect.setHeight(incrementalRect.height() + incHeight);
        painter->drawText(incrementalRect, Qt::AlignBottom, atributeToPrint);
    }

    painter->drawRect(incrementalRect);
    incrementalRect.setHeight(incrementalRect.height() + lineIndent);

    for(QString &methodToPrint : methodVector)
    {
        incrementalRect.setHeight(incrementalRect.height() + incHeight);
        painter->drawText(incrementalRect, Qt::AlignBottom, methodToPrint);
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
    QRectF rect = metrics.boundingRect(QString::fromStdString(classEntity.getName()));
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
QRectF ClassNode::getWholeRect(std::vector<QString> attributePrintable,
                               std::vector<QString> methodPrintable) const
{
    QFontMetricsF metrics{qApp->font()};
    QRectF nameRect = metrics.boundingRect(QString::fromStdString(classEntity.getName()));

    int maxWidth = nameRect.width();
    getMaxWidth(attributePrintable, &maxWidth);
    getMaxWidth(methodPrintable, &maxWidth);
    maxWidth += Padding * 2;

    QRectF wholeRect = nameRect;
    wholeRect.setWidth(maxWidth);
    wholeRect.setHeight(nameRect.height() + 2 * lineIndent + nameRect.height() * attributePrintable.size()
                        + nameRect.height() * methodPrintable.size());
    wholeRect.adjust(0, -Padding, 0, Padding);
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
    std::vector<ClassAttribute> attributes = classEntity.getAttributes();
    std::vector<QString> attributeString(attributes.size());

    for(size_t i = 0; i < attributes.size(); i++)
    {
        QString accesModifier = modifierToString(attributes[i].getAccessModifier());
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
std::vector<QString> ClassNode::getMethodPrintable() const
{
    std::vector<ClassMethod> methods = classEntity.getMethods();
    std::vector<QString> methodString(methods.size());

    for(size_t i = 0; i < methods.size(); i++)
    {
        QString accesModifier = modifierToString(methods[i].getAccessModifier());
        QString methodName = QString::fromStdString(methods[i].getName());
        QString parameterString = getMethodParametersPrintable(methods[i].getParameters());

        methodString[i] = "  " + accesModifier + methodName + "(" + parameterString + ")";
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
 * Converts AccessModifier to string representation.
 *
 * @param mod AccessModifier which should be modified.
 * @return QString representation of AccessModifier.
 */
QString ClassNode::modifierToString(AccessModifier mod) const
{
    switch (mod) {
    case AccessModifier::PUBLIC:
        return "+";
    case AccessModifier::PRIVATE:
        return "-";
    case AccessModifier::PROTECTED:
        return "#";
    case AccessModifier::PACKAGE_PRIVATE:
        return "~";
    default:
        return "";
    }
}

void ClassNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    ClassEditDialog *classEditDialog = new ClassEditDialog(this->getClassEntity());
    if(classEditDialog->exec() == QDialog::Accepted)
    {
        this->setEntity(classEditDialog->getClassEntity());
        update();
    }
}
