/**
 * @file CustomScene.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include "CustomScene.h"

/**
 * Getter for saved status
 *
 * @return Is current version of edited diagram saved to persistent storage?
 */
bool CustomScene::isSaved()
{
    return saved;
}

/**
 * Getter for target file
 *
 * @return File path where to save diagram
 */
std::string CustomScene::getTargetFile()
{
    return targetFile;
}

/**
 * Setter for target file
 *
 * @param newTargetFile New path to the file where to save diagram
 */
void CustomScene::setTargetFile(std::string &newTargetFile)
{
    targetFile = newTargetFile;
}

/**
 * Setter for target file
 *
 * @param newTargetFile New path to the file where to save diagram
 */
void CustomScene::setTargetFile(std::string &&newTargetFile)
{
    setTargetFile(newTargetFile);
}
