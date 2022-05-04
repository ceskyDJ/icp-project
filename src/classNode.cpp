#include "classNode.h"
#include "qpainter.h"
#include "QPlainTextEdit"
#include <algorithm>

ClassNode::ClassNode(Class classEntity)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    ClassNode::classEntity = classEntity;
    prepareGeometryChange();
    update();
}

QRectF ClassNode::boundingRect() const
{
    return getWholeRect();
}

void ClassNode::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
               QWidget * /*widget*/)
{
    QPen pen = QPen{Qt::black,2,Qt::SolidLine};
    painter->setPen(pen);

    QRectF nameRect = getNameBoundigRect();
    int incHeight = nameRect.height();
    std::vector<QString> attributeString = getAttributePrintable();
    QRectF wholeRect = getWholeRect(attributeString);

    int maxWidth = wholeRect.width();

    nameRect.setWidth(maxWidth);
    nameRect.setHeight(nameRect.height() + Padding);
    painter->drawRect(nameRect);
    painter->drawText(nameRect, Qt::AlignCenter, QString::fromStdString(classEntity.getName()));

    QRectF incrementalRect = nameRect;
    incrementalRect.setHeight(nameRect.height() + lineIndent);
    for(QString &atributeToPrint : attributeString)
    {
        incrementalRect.setHeight(incrementalRect.height() + incHeight);
        painter->drawText(incrementalRect, Qt::AlignBottom, atributeToPrint);
    }
    painter->drawRect(incrementalRect);
    incrementalRect.setHeight(incrementalRect.height() + lineIndent);
    painter->drawRect(incrementalRect);
    //QRectF newRect = nameRect;
    /*newRect.setHeight(newRect.height() + nameRect.height());
    painter->drawText(newRect, Qt::AlignCenter, "HAHAHA");
    newRect.setHeight(newRect.height() + nameRect.height());
    painter->drawText(newRect, Qt::AlignCenter, "HAHAHA");*/
    /*QRectF attributeRect = nameRect;

    attributeRect.setHeight(nameRect.height() * (attributeString.size()) + lineIndent);
    painter->drawRect(attributeRect);*/
    //rectangle.setBottom(rectangle.bottom() + lineIndent);

    //painter->drawRect(rectangle);

}

QRectF ClassNode::getNameBoundigRect() const
{
    QFontMetricsF metrics{qApp->font()};
    QRectF rect = metrics.boundingRect(QString::fromStdString(classEntity.getName()));
    return rect;
}

QRectF ClassNode::getWholeRect() const
{
    std::vector<QString> attributePrintable = getAttributePrintable();
    return getWholeRect(attributePrintable);
}

QRectF ClassNode::getWholeRect(std::vector<QString> attributePrintable) const
{
    QFontMetricsF metrics{qApp->font()};
    QRectF nameRect = metrics.boundingRect(QString::fromStdString(classEntity.getName()));
    int maxWidth = nameRect.width();

    for(QString &attributeStr : attributePrintable)
    {
        int a = metrics.boundingRect(attributeStr).width();
        (void)a;
        if(maxWidth < metrics.boundingRect(attributeStr).width())
            maxWidth = metrics.boundingRect(attributeStr).width();
    }
    QRectF wholeRect = nameRect;
    maxWidth += Padding * 2;
    wholeRect.setWidth(maxWidth);
    wholeRect.setHeight(nameRect.height() + 2 * lineIndent + nameRect.height() * attributePrintable.size());
    wholeRect.adjust(0, -Padding, 0, Padding);
    return wholeRect;
}

std::vector<QString> ClassNode::getAttributePrintable() const
{
    std::vector<ClassAttribute> attributes = classEntity.getAttributes();
    std::vector<QString> attributeString(attributes.size());

    QFontMetricsF metrics{qApp->font()};
    for(size_t i = 0; i < attributes.size(); i++)
    {
        QString accesModifier = modifierToString(attributes[i].getAccessModifier());
        QString attributeName = QString::fromStdString(attributes[i].getName());
        QString attributeType = QString::fromStdString(attributes[i].getDataType());

        attributeString[i] = accesModifier + attributeName + ":" + attributeType;
    }
    return attributeString;
}

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
