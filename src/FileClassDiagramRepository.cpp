/**
 * @file FileClassDiagramRepository.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "FileClassDiagramRepository.h"
#include "InvalidDataStorageException.h"

/**
 * Loads diagram from defined source
 *
 * @return Loaded class diagram
 * @throw InvalidDataStorageException Invalid file
 */
ClassDiagram FileClassDiagramRepository::loadDiagram()
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No source file set"};
    }

    // TODO: implement this method
}

/**
 * Saves diagram to defined target
 *
 * @param diagram Class diagram to save
 * @throw InvalidDataStorageException Invalid file
 */
void FileClassDiagramRepository::saveDiagram(ClassDiagram diagram)
{
    if (fileName.empty()) {
        throw InvalidDataStorageException{"No target file set"};
    }

    // TODO: implement this method
}
