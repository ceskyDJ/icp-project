#ifndef OBJECTGRAPHICSITEMEDITDIALOG_H
#define OBJECTGRAPHICSITEMEDITDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QAbstractSpinBox>
#include <QPushButton>
#include <QComboBox>

class ObjectGraphicsItemEditDialog : public QDialog
{
public:
    ObjectGraphicsItemEditDialog(QString objectName, QString className);
    const static int canceled = -1;

    /**
     * Getter for class name.
     *
     * @return selected class name
     */
    QString getClassName()
    {
        return className;
    }

    /**
     * Getter for object. Get new name of object.
     *
     * @return new name of object
     */
    QString getObjectName()
    {
        return objectName;
    }
private:
    QString objectName;
    QString className;
    QPushButton acceptButton;
    QPushButton cancelButton;
    QPushButton removeButton;
    QLineEdit objectNameLineEdit;
    QComboBox classNameCombo;
    QVBoxLayout mainLayout;
    QHBoxLayout buttonLayout;
    QFormLayout propertyLayout;


    void connectComponents();
    void setAllLayouts();
    void setOneButton(QPushButton *button ,QIcon icon, QString text, bool setDefault);
    void setAllButtons();
    void setButtonLayout();
    void setPropertyLayout();
private slots:
   void objectNameChanged(QString newName);
   void newClassSelected(QString newText);
   void acceptButtonPressed();
   void cancelButtonPressed();
   void removeButtonPressed();
};

#endif // OBJECTGRAPHICSITEMEDITDIALOG_H
