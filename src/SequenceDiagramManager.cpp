/**
 * @file SequenceDiagramManager.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "SequenceDiagramManager.h"

/**
 * Loads sequence diagram
 *
 * @param classDiagram Class diagram the sequence diagram is loaded for
 * @param sourceName Name of preferred source (e.g. path to file for File* repositories)
 * @return Loaded sequence diagram
 * @throw InvalidDataStorageException Invalid source
 * @throw InvalidInputDataException Invalid data structure in given source
 */
SequenceDiagram SequenceDiagramManager::loadDiagram([[maybe_unused]] ClassDiagram classDiagram, [[maybe_unused]] std::string sourceName)
{
    // TODO: implement method
    return SequenceDiagram{};
}

/**
 * Saves sequence diagram
 *
 * @param targetName Name of preferred target (e.g. path to file for File* repositories)
 * @param sequenceDiagram Sequence diagram to save
 * @throw InvalidDataStorageException Invalid target
 */
void SequenceDiagramManager::saveDiagram([[maybe_unused]] std::string targetName, [[maybe_unused]] SequenceDiagram sequenceDiagram)
{
    // TODO: implement method
}

/**
 * Creates a backup of sequence diagram
 *
 * @param sequenceDiagram Sequence diagram to backup
 */
void SequenceDiagramManager::backupDiagram([[maybe_unused]] SequenceDiagram sequenceDiagram)
{
    // TODO: implement method
}

/**
 * Does undo operation for backed up sequence diagram
 *
 * @param sequenceDiagram Sequence diagram to apply undo operation for
 */
void SequenceDiagramManager::undoDiagramChanges([[maybe_unused]] SequenceDiagram &sequenceDiagram)
{
    // TODO: implement method
}

/**
 * Does redo operation for backed up sequence diagram
 *
 * @param sequenceDiagram Sequence diagram to apply redo operation for
 */
void SequenceDiagramManager::redoDiagramChanges([[maybe_unused]] SequenceDiagram &sequenceDiagram)
{
    // TODO: implement method
}
