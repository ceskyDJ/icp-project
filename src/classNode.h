#ifndef CLASSNODE_H
#define CLASSNODE_H

#include <QGraphicsItem>
#include <QSet>
#include <QApplication>
#include <QPushButton>
#include "ClassAttribute.h"
#include "Class.h"
#include "ClassAttribute.h"
#include "ClassMethod.h"

class ClassNode : public QGraphicsItem
{
public:
    ClassNode(Class classEntity = Class{"Nová třída", std::make_tuple(1, 1)});
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
    void setName(QString newName)
    {
        classEntity.setName(newName.toStdString());
        update();
    }

    void addAtribute(ClassAttribute newAtribute)
    {
        classEntity.addAttribute(newAtribute);
        update();
    }

    void addMethod(ClassMethod newMethod)
    {
        classEntity.addMethod(newMethod);
        update();
    }

    QString getName()
    {
        return QString::fromStdString(classEntity.getName());
    }

    std::vector<ClassAttribute> getAtributes()
    {
        return classEntity.getAttributes();
    }

    std::vector<ClassMethod> getMethods()
    {
        return classEntity.getMethods();
    }

    void setAtributes(std::vector<ClassAttribute> atributes)
    {
        classEntity.setAttributes(atributes);
        update();
    }

    void setMethods(std::vector<ClassMethod> methods)
    {
        classEntity.setMethods(methods);
        update();
    }

    void setEntity(Class newEntity)
    {
        classEntity = newEntity;
        update();
    }

    Class getClassEntity()
    {
        return classEntity;
    }

    void setBorderColor(QColor color)
    {
        borderColor = color;
        update();
    }
private:
    QRectF borederRect();
    QRectF getNameBoundigRect() const;
    QRectF getWholeRect() const;
    QRectF getWholeRect(std::vector<QString> attributePrintable, std::vector<QString> methodPrintable) const;
    const int lineIndent = 5;
    const int Padding = 10;
    Class classEntity;
    QColor borderColor = Qt::black;

    std::vector<QString> getAttributePrintable() const;
    std::vector<QString> getMethodPrintable() const;
    QString getMethodParametersPrintable(std::vector<MethodParameter> parameters) const;
    QString modifierToString(AccessModifier mod);
    QString modifierToString(AccessModifier mod) const;
    void getMaxWidth(std::vector<QString> toCompare, int *maxWidth) const;
    void setFontItalic(bool enable, QPainter *painter);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CLASSNODE_H
