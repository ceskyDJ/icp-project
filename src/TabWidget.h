/**
 * @file TabWidget.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_TAB_WIDGET_H
#define ICP_PROJECT_TAB_WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QGridLayout>
#include <QPushButton>

/**
 * Qt widget for representing tab in bottom tab bar
 */
class TabWidget: public QWidget
{
    Q_OBJECT

    // Icons
    const QIcon closeIcon = QIcon(":/closeCross.png");

    // Properties
    /**
     * Label to show in tab bar
     */
    QString label;

    // Widgets
    /**
     * Grid layout for buttons
     */
    QGridLayout layout;

    // Buttons
    /**
     * Main button for tab switching
     */
    QPushButton tabButton;
    /**
     * Button for closing the tab
     */
    QPushButton closeButton;

  public:
    /**
     * Class constructor
     *
     * @param label Label to show in tab bar
     */
    explicit TabWidget(const QString &label);

    /**
     * Sets tab as active/inactive
     *
     * @param state Should the tab be active?
     */
    void setActive(bool state);

    /**
     * Sets tab as saved (corresponding scene is saved)
     *
     * @param state Is corresponding scene saved (set as saved)?
     */
    void setSaved(bool state);

    /**
     * Getter for tab button
     *
     * @return Pointer to button for tab switching
     */
    const QPushButton *getTabButton()
    {
        return &tabButton;
    }

    /**
     * Getter for close button
     *
     * @return Pointer to button for closing tab
     */
    const QPushButton *getCloseButton()
    {
        return &closeButton;
    }
};

#endif //ICP_PROJECT_TAB_WIDGET_H
