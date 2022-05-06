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

  public:
    /**
     * Constructor for initialization with known class diagram
     *
     * @param classDiagram Class diagram to use as a source for classes, methods, etc.
     */
    explicit SequenceDiagramRepository(ClassDiagram classDiagram): classDiagram{classDiagram} {};

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
