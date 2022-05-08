/**
 * @file SequenceDiagramManager.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_SEQUENCE_DIAGRAM_MANAGER_H
#define ICP_PROJECT_SEQUENCE_DIAGRAM_MANAGER_H

#include <map>
#include "SequenceDiagram.h"
#include "SequenceDiagramRepository.h"
#include "HistoryStack.h"

/**
 * Class for high-level managing sequence diagrams
 */
class SequenceDiagramManager
{
    /**
     * Pointer to used sequence diagram repository
     */
    SequenceDiagramRepository *sequenceDiagramRepository;
    /**
     * Mementos for sequence diagrams
     */
    std::map<SequenceDiagram *, HistoryStack<SequenceDiagramMemento>> mementos;

  public:
    /**
     * Constructor for initializing with known sequence diagram repository
     *
     * @param sequenceDiagramRepository Sequence diagram repository to use
     */
    SequenceDiagramManager(
        SequenceDiagramRepository *sequenceDiagramRepository
    ): sequenceDiagramRepository{sequenceDiagramRepository} {};

    /**
     * Loads sequence diagram
     *
     * @param classDiagram Class diagram the sequence diagram is loaded for
     * @param sourceName Name of preferred source (e.g. path to file for File* repositories)
     * @return Loaded sequence diagram
     * @throw InvalidDataStorageException Invalid source
     * @throw InvalidInputDataException Invalid data structure in given source
     */
    SequenceDiagram loadDiagram(ClassDiagram classDiagram, std::string sourceName);

    /**
     * Saves sequence diagram
     *
     * @param targetName Name of preferred target (e.g. path to file for File* repositories)
     * @param sequenceDiagram Sequence diagram to save
     * @throw InvalidDataStorageException Invalid target
     */
    void saveDiagram(std::string targetName, SequenceDiagram sequenceDiagram);

    /**
     * Creates a backup of sequence diagram
     *
     * @param sequenceDiagram Pointer to sequence diagram to backup
     */
    void backupDiagram(SequenceDiagram *sequenceDiagram);

    /**
     * Does undo operation for backed up sequence diagram
     *
     * @param sequenceDiagram Pointer to sequence diagram to apply undo operation for
     */
    void undoDiagramChanges(SequenceDiagram *sequenceDiagram);

    /**
     * Does redo operation for backed up sequence diagram
     *
     * @param sequenceDiagram Pointer to sequence diagram to apply redo operation for
     */
    void redoDiagramChanges(SequenceDiagram *sequenceDiagram);
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_MANAGER_H
