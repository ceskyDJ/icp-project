/**
 * @file ClassDiagramRepository.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_DIAGRAM_REPOSITORY_H
#define ICP_PROJECT_CLASS_DIAGRAM_REPOSITORY_H

#include "ClassDiagram.h"

/**
 * Base repository for class diagrams
 */
class ClassDiagramRepository
{
    /**
     * Loads diagram from defined source
     *
     * @return Loaded class diagram
     * @throw InvalidDataStorageException Invalid data storage
     */
    virtual ClassDiagram loadDiagram() = 0;

    /**
     * Saves diagram to defined target
     *
     * @param diagram Class diagram to save
     * @throw InvalidDataStorageException Invalid data storage
     */
    virtual void saveDiagram(ClassDiagram diagram) = 0;
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_REPOSITORY_H
