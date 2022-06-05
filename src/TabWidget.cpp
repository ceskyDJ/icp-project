/**
 * @file TabWidget.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 * @author Michal Šmahel (xsmahe01)
 */
#include <QPushButton>
#include <QGridLayout>
#include "TabWidget.h"

/**
 * Class constructor
 *
 * @param label Label to show in tab bar
 */
TabWidget::TabWidget(const QString &label): label{label}
{
    // Init buttons
    tabButton.setText(label);
    closeButton.setIcon(closeIcon);

    // Setup layout for buttons
    layout.addWidget(&tabButton,0,0);
    layout.addWidget(&closeButton, 0, 1);
    setLayout(&layout);

    // Newly created scenes aren't saved
    setSaved(false);
}

/**
 * Sets tab as active/inactive
 *
 * @param state Should the tab be active?
 */
void TabWidget::setActive(bool state)
{
    if (state) {
        // Active tab should not be activated again
        tabButton.setDisabled(true);

        return;
    }

    // Enable button so the tab could be activated again
    tabButton.setDisabled(false);
}

/**
 * Sets tab as saved (corresponding scene is saved)
 *
 * @param state Is corresponding scene saved (set as saved)?
 */
void TabWidget::setSaved(bool state)
{
    if (state) {
        tabButton.setText(label);
    } else {
        tabButton.setText(label + "*");
    }

    update();
}
