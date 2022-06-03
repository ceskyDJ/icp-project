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
SequenceDiagram SequenceDiagramManager::loadDiagram(const ClassDiagram &classDiagram, const std::string &sourceName)
{
    sequenceDiagramRepository->setClassDiagram(classDiagram);
    sequenceDiagramRepository->setStorageName(sourceName);

    return sequenceDiagramRepository->loadDiagram();
}

/**
 * Saves sequence diagram
 *
 * @param targetName Name of preferred target (e.g. path to file for File* repositories)
 * @param sequenceDiagram Sequence diagram to save
 * @throw InvalidDataStorageException Invalid target
 */
void SequenceDiagramManager::saveDiagram(const std::string &targetName, const SequenceDiagram &sequenceDiagram)
{
    sequenceDiagramRepository->setStorageName(targetName);

    sequenceDiagramRepository->saveDiagram(sequenceDiagram);
}

/**
 * Creates a backup of sequence diagram
 *
 * @param sequenceDiagram Pointer to sequence diagram to backup
 */
void SequenceDiagramManager::backupDiagram(SequenceDiagram *sequenceDiagram)
{
    if (mementos.count(sequenceDiagram) == 0) {
        mementos[sequenceDiagram] = HistoryStack<SequenceDiagramMemento>{};
    }

    mementos[sequenceDiagram].addRecord(sequenceDiagram->createMemento());
}

/**
 * Does undo operation for backed up sequence diagram
 *
 * @param sequenceDiagram Pointer to sequence diagram to apply undo operation for
 */
void SequenceDiagramManager::undoDiagramChanges(SequenceDiagram *sequenceDiagram)
{
    if (mementos.count(sequenceDiagram) == 0) {
        mementos[sequenceDiagram] = HistoryStack<SequenceDiagramMemento>{};
    }

    sequenceDiagram->setMemento(mementos[sequenceDiagram].back());
}

/**
 * Does redo operation for backed up sequence diagram
 *
 * @param sequenceDiagram Pointer to sequence diagram to apply redo operation for
 */
void SequenceDiagramManager::redoDiagramChanges(SequenceDiagram *sequenceDiagram)
{
    if (mementos.count(sequenceDiagram) == 0) {
        mementos[sequenceDiagram] = HistoryStack<SequenceDiagramMemento>{};
    }

    sequenceDiagram->setMemento(mementos[sequenceDiagram].forward());
}
