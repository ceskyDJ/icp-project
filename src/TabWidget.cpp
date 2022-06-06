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
 * @param scene Connected scene
 * @param closeable Could the tab be closed?
 */
TabWidget::TabWidget(const QString &label, CustomScene *scene, bool closeable): label{label}, scene{scene}
{
    // Init buttons
    // tabButton.setText(label); This is not necessary, because updateState() sets the text, too
    closeButton.setIcon(closeIcon);

    // Setup layout for buttons
    layout.addWidget(&tabButton,0,0);
    if (closeable) {
        // Tab could be closed by clicking on this button
        layout.addWidget(&closeButton, 0, 1);
    }
    setLayout(&layout);

    // Newly created scenes aren't saved
    updateState();
}

/**
 * Sets tab as active/inactive
 *
 * @par Implicitly updates tab's state by calling updateState()
 * @see TabWidget::updateState()
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

    // Update state, because after changing tab activity state of tab is changed often, too
    updateState();
}

/**
 * Updates tab's state using information from corresponding scene
 *
 * @par The star is added after label if the scene isn't saved.
 */
void TabWidget::updateState()
{
    if (scene->isSaved()) {
        tabButton.setText(label);
    } else {
        tabButton.setText(label + "*");
    }

    update();
}

/**
 * Setter for label
 *
 * @param newLabel New label shown in tab bar
 */
void TabWidget::setLabel(const QString &newLabel)
{
    label = newLabel;

    updateState();
}
