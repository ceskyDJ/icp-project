/**
 * @file FileSequenceDiagramRepository.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "FileSequenceDiagramRepository.h"
#include "InvalidDataStorageException.h"

/**
 * Loads diagram from defined source
 *
 * @return Loaded sequence diagram
 * @throw InvalidDataStorageException Invalid file
 */
SequenceDiagram FileSequenceDiagramRepository::loadDiagram()
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No source file set"};
    }

    // TODO: implement this method
}

/**
 * Saves diagram to defined target
 *
 * @param diagram Sequence diagram to save
 * @throw InvalidDataStorageException Invalid file
 */
void FileSequenceDiagramRepository::saveDiagram(SequenceDiagram diagram)
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No target file set"};
    }

    // TODO: implement this method
}
