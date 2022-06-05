/**
 * @file CustomScene.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_CUSTOM_SCENE_H
#define ICP_PROJECT_CUSTOM_SCENE_H

#include <QGraphicsScene>

/**
 * Template for concrete custom scenes (interface for using these scenes)
 */
class CustomScene: public QGraphicsScene
{
  protected:
    // Dependencies
    QWidget *parentWindow;

    // States
    /**
     * Is currently edited diagram saved to persistent storage (after last update)?
     */
    bool saved = false;
    /**
     * Name of the file where the final diagram should be stored in (with absolute path to it)
     *
     * @par This is the file, where changes will be saved when just clicking to "Save"
     * button, not "Save as...". It is a place used for possible auto saving, etc.
     * @par When diagram is loaded from file, the source file will be used.
     */
    std::string targetFile{};

    /**
     * Protected class constructor
     *
     * @param parentWindow Pointer to parent window (dependency)
     */
    explicit CustomScene(QWidget *parentWindow): parentWindow{parentWindow} {};

  public:
    // States checks and modifiers
    /**
     * Logs scene changes for saving and undo/redo mechanisms
     */
    virtual void logChanges() noexcept = 0;
    /**
     * Getter for saved status
     *
     * @return Is current version of edited diagram saved to persistent storage?
     */
    bool isSaved();
    /**
     * Getter for target file
     *
     * @return File path where to save diagram
     */
    std::string getTargetFile();
    /**
     * Setter for target file
     *
     * @param newTargetFile New path to the file where to save diagram
     */
    void setTargetFile(std::string &newTargetFile);
    /**
     * Setter for target file
     *
     * @param newTargetFile New path to the file where to save diagram
     */
    void setTargetFile(std::string &&newTargetFile);

    // Top toolbar buttons' actions
    /**
     * Loads diagram from file
     */
    virtual void loadFromFile() = 0;
    /**
     * Saves diagram to already set file (or file where the diagram is loaded from)
     */
    virtual void saveToFile() = 0;
    /**
     * Reverts last change
     */
    virtual void undoLastChange() = 0;
    /**
     * Restores reverted change
     */
    virtual void redoRevertedChange() = 0;
};

#endif //ICP_PROJECT_CUSTOM_SCENE_H
