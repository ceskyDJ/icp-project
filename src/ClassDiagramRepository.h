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
  protected:
    /**
     * Name of used storage (when needed)
     */
    std::string storageName;

    /**
     * Implicit constructor
     */
    ClassDiagramRepository(): storageName{} {};

    /**
     * Constructor for initializing with known storage name
     *
     * @param storageName Name of the storage to use (when type of the storage needs
     * it otherwise use implicit constructor)
     */
    explicit ClassDiagramRepository(std::string storageName): storageName{storageName} {};

    /**
     * Virtual default destructor
     */
    virtual ~ClassDiagramRepository() = default;

  public:
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
     * @return Loaded class diagram
     * @throw InvalidDataStorageException Invalid data storage
     * @throw InvalidInputDataException Invalid structure of input data
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
