#include "classNode.h"
#include "qpainter.h"
#include "QPlainTextEdit"

ClassNode::ClassNode(QString name)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    className = name;
    prepareGeometryChange();
    update();
}



QRectF ClassNode::boundingRect() const
{
    return getBoundigRect();
}


void ClassNode::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,
               QWidget * /*widget*/)
{
    QPen pen = QPen{Qt::black,2,Qt::SolidLine};
    painter->setPen(pen);
    QRectF rectangle = getBoundigRect();

    painter->drawRect(rectangle);
    painter->drawText(rectangle, Qt::AlignCenter, className);
}

QRectF ClassNode::getBoundigRect() const
{
    const int Padding = 10;
    QFontMetricsF metrics{qApp->font()};
    QRectF rect = metrics.boundingRect(className);
    rect.setBottom(rect.bottom() + lineIndent);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}
