#ifndef CLASSNODE_H
#define CLASSNODE_H

#include <QGraphicsItem>
#include <QSet>
#include <QApplication>
#include <QPushButton>

class ClassNode : public QGraphicsItem
{
public:
    ClassNode(QString name = "");
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

private:
    QRectF borederRect() const;
    QRectF getBoundigRect() const;
    QString className;
    const int lineIndent = 10;
};

#endif // CLASSNODE_H
