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
    ClassNode(Class classEntity);
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

private:
    QRectF borederRect();
    QRectF getNameBoundigRect() const;
    QRectF getWholeRect() const;
    QRectF getWholeRect(std::vector<QString> attributePrintable) const;
    const int lineIndent = 5;
    const int Padding = 10;
    Class classEntity;

    std::vector<QString> getAttributePrintable() const;
    QString modifierToString(AccessModifier mod);
    QString modifierToString(AccessModifier mod) const;


};

#endif // CLASSNODE_H
