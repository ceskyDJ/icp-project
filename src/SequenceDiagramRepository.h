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
#include "ClassDiagram.h"

/**
 * Base repository for sequence diagrams
 */
class SequenceDiagramRepository
{
  protected:
    /**
     * Class diagram used as a source for classes, methods, etc.
     */
    ClassDiagram classDiagram;

    /**
     * Name of used storage (when needed)
     */
    std::string storageName;

    /**
     * Implicit constructor
     */
    SequenceDiagramRepository(): classDiagram{}, storageName{} {};

    /**
     * Constructor for initialization with known class diagram and storage name
     *
     * @param classDiagram Class diagram to use as a source for classes, methods, etc.
     * @param storageName Name of the storage to use (when type of the storage needs
     * it otherwise use implicit constructor)
     */
    explicit SequenceDiagramRepository(
        ClassDiagram classDiagram,
        std::string storageName
    ): classDiagram{classDiagram}, storageName{storageName} {};

    /**
     * Default virtual destructor
     */
    virtual ~SequenceDiagramRepository() = default;

  public:
    /**
     * Constant getter for class diagram
     *
     * @return Class diagram used as a source for classes, methods, etc.
     */
    const ClassDiagram &getClassDiagram() const {
        return classDiagram;
    }

    /**
     * Setter for class diagram
     *
     * @param newClassDiagram Class diagram to use as a source for classes, methods, etc.
     */
    void setClassDiagram(const ClassDiagram &newClassDiagram) {
        classDiagram = newClassDiagram;
    }

    /**
     * Getter for storage name
     *
     * @return Name of the used storage (when needed, could be empty string when the source
     * type doesn't use names)
     */
    std::string getStorageName() const
    {
        return storageName;
    }

    /**
     * Setter for storage name
     *
     * @param newStorageName New name of used storage
     */
    void setStorageName(const std::string &newStorageName)
    {
        storageName = newStorageName;
    }

    /**
     * Loads diagram from defined source
     *
     * @return Loaded sequence diagram
     * @throw InvalidDataStorageException Invalid data storage
     * @throw InvalidInputDataException Invalid structure of input data
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
