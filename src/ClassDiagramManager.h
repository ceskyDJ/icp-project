/**
 * @file ClassDiagramManager.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_CLASS_DIAGRAM_MANAGER_H
#define ICP_PROJECT_CLASS_DIAGRAM_MANAGER_H

#include <map>
#include "ClassDiagramRepository.h"
#include "SequenceDiagramRepository.h"
#include "HistoryStack.h"

/**
 * Class for high-level managing class diagrams
 */
class ClassDiagramManager
{
    /**
     * Pointer to class diagram repository
     */
    ClassDiagramRepository *classDiagramRepository;
    /**
     * Mementos for class diagrams
     */
    std::map<ClassDiagram *, HistoryStack<ClassDiagramMemento>> mementos;

  public:
    /**
     * Constructor for initialization with known class diagram repository
     *
     * @param classDiagramRepository Pointer to class diagram repository to use
     */
    explicit ClassDiagramManager(
        ClassDiagramRepository *classDiagramRepository
    ): classDiagramRepository{classDiagramRepository} {};

    /**
     * Loads class diagram
     *
     * @param sourceName Name of preferred source (e.g. path to file for File* repositories)
     * @return Loaded class diagram
     * @throw InvalidDataStorageException Invalid source
     * @throw InvalidInputDataException Invalid data structure in given source
     */
    ClassDiagram loadDiagram(const std::string &sourceName);

    /**
     * Saves class diagram
     *
     * @param targetName Name of preferred target (e.g. path to file for File* repositories)
     * @param classDiagram Class diagram to save
     * @throw InvalidDataStorageException Invalid target
     */
    void saveDiagram(const std::string &targetName, const ClassDiagram &classDiagram);

    /**
     * Creates a backup of class diagram
     *
     * @param classDiagram Pointer to class diagram to backup
     */
    void backupDiagram(ClassDiagram *classDiagram);

    /**
     * Does undo operation for backed up class diagram
     *
     * @param classDiagram Pointer to class diagram to apply undo operation for
     */
    void undoDiagramChanges(ClassDiagram *classDiagram);

    /**
     * Does redo operation for backed up class diagram
     *
     * @param classDiagram Pointer to class diagram to apply redo operation for
     */
    void redoDiagramChanges(ClassDiagram *classDiagram);
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_MANAGER_H
