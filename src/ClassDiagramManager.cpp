/**
 * @file ClassDiagramManager.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "ClassDiagramManager.h"

/**
 * Loads class diagram
 *
 * @param sourceName Full relative/absolute path to file with diagram
 * @return Loaded class diagram
 * @throw InvalidDataStorageException Invalid file
 * @throw InvalidInputDataException Invalid data structure in given file
 */
ClassDiagram ClassDiagramManager::loadDiagram(std::string sourceName)
{
    classDiagramRepository->setStorageName(sourceName);

    return classDiagramRepository->loadDiagram();
}

/**
 * Saves class diagram
 *
 * @param targetName Name of preferred target (e.g. path to file for File* repositories)
 * @param classDiagram Class diagram to save
 * @throw InvalidDataStorageException Invalid target
 */
void ClassDiagramManager::saveDiagram(std::string targetName, ClassDiagram classDiagram)
{
    classDiagramRepository->setStorageName(targetName);

    classDiagramRepository->saveDiagram(classDiagram);
}

/**
 * Creates a backup of class diagram
 *
 * @param classDiagram Class diagram to backup
 */
void ClassDiagramManager::backupDiagram([[maybe_unused]] ClassDiagram classDiagram)
{
    // TODO: implement method
}

/**
 * Does undo operation for backed up class diagram
 *
 * @param classDiagram Class diagram to apply undo operation for
 */
void ClassDiagramManager::undoDiagramChanges([[maybe_unused]] ClassDiagram &classDiagram)
{
    // TODO: implement method
}

/**
 * Does redo operation for backed up class diagram
 *
 * @param classDiagram Class diagram to apply redo operation for
 */
void ClassDiagramManager::redoDiagramChanges([[maybe_unused]] ClassDiagram &classDiagram)
{
    // TODO: implement method
}
