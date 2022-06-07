/**
 * @file ReferenceUpdater.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_REFERENCE_UPDATER_H
#define ICP_PROJECT_REFERENCE_UPDATER_H

#include <functional>
#include <string>

class Class;

/**
 * Updater for "smart" references for "safe" pointers (e.g. ClassReference, MethodReference)
 */
class ReferenceUpdater
{
    /**
     * @typedef Function called when the reference target was deleted
     */
    using TargetDeletedFunction = std::function<void (const std::string &)>;
    /**
     * @typedef Function called when the reference target was changed
     */
    using TargetChangedFunction = std::function<void (void *)>;

    /**
     * Callback to call when the reference target was deleted
     */
    TargetDeletedFunction targetDeletedCallback;
    /**
     * Callback to call when the reference target was changed
     */
    TargetChangedFunction targetChangedCallback;

  public:
    /**
     * Class constructor
     *
     * @param targetDeleted Function to call when the reference target was deleted
     * @param targetChanged Function to call when the reference target was changed
     */
    ReferenceUpdater(
        TargetDeletedFunction targetDeleted,
        TargetChangedFunction targetChanged
    ): targetDeletedCallback{targetDeleted}, targetChangedCallback{targetChanged} {};

    /**
     * Notifies that the reference target was deleted
     *
     * @param targetName Name of the deleted target
     */
    void targetDeleted(const std::string &targetName)
    {
        targetDeletedCallback(targetName);
    }

    /**
     * Notifies that the reference target was changed
     *
     * @param newTargetPointer New pointer to the target
     */
    void targetChanged(void *newTargetPointer)
    {
        targetChangedCallback(newTargetPointer);
    }
};

#endif //ICP_PROJECT_REFERENCE_UPDATER_H
