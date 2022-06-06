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
#include "CustomScene.h"

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
    /**
     * Scene connected to this tab
     */
    CustomScene *scene;

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
     * @param scene Connected scene
     * @param closeable Could the tab be closed?
     */
    explicit TabWidget(const QString &label, CustomScene *scene, bool closeable = true);

    /**
     * Sets tab as active/inactive
     *
     * @param state Should the tab be active?
     */
    void setActive(bool state);

    /**
     * Updates tab's state using information from corresponding scene
     *
     * @par The star is added after label if the scene isn't saved.
     */
    void updateState();

    /**
     * Setter for label
     *
     * @param newLabel New label shown in tab bar
     */
    void setLabel(const QString &newLabel);

    /**
     * Getter for label
     *
     * @return Label shown in tab bar
     */
    QString getLabel()
    {
        return label;
    }

    /**
     * Getter for connected scene
     *
     * @return Pointer to connected scene
     */
    CustomScene *getScene()
    {
        return scene;
    }

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
