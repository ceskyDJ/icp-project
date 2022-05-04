/**
 * @file SequenceDiagramRepository.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_SEQUENCE_DIAGRAM_REPOSITORY_H
#define ICP_PROJECT_SEQUENCE_DIAGRAM_REPOSITORY_H

#include "SequenceDiagram.h"

/**
 * Base repository for sequence diagrams
 */
class SequenceDiagramRepository
{
    /**
     * Loads diagram from defined source
     *
     * @return Loaded sequence diagram
     * @throw InvalidDataStorageException Invalid data storage
     */
    virtual SequenceDiagram loadDiagram() = 0;

    /**
     * Saves diagram to defined target
     *
     * @param diagram Sequence diagram to save
     * @throw InvalidDataStorageException Invalid data storage
     */
    virtual void saveDiagram(SequenceDiagram diagram) = 0;
};

#endif //ICP_PROJECT_SEQUENCE_DIAGRAM_REPOSITORY_H
