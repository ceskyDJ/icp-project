/**
 * @file FileSequenceDiagramRepository.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H
#define ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H

#include <QDomElement>
#include "SequenceDiagramRepository.h"

/**
 * File repository for sequence diagrams
 */
class FileSequenceDiagramRepository: public SequenceDiagramRepository
{
  public:
    /**
     * Implicit contructor
     */
    explicit FileSequenceDiagramRepository(): SequenceDiagramRepository{} {};

    /**
     * Constructor for initialization with known name of file
     *
     * @param classDiagram Pointer to class diagram to use as a source for classes, methods, etc.
     * @param fileName Name of the file to work with (full relative/absolute path)
     */
    explicit FileSequenceDiagramRepository(
        const ClassDiagram *classDiagram,
        const std::string &fileName
    ): SequenceDiagramRepository{classDiagram, fileName} {};

    /**
     * Loads diagram from defined source
     *
     * @return Loaded sequence diagram
     * @throw InvalidDataStorageException Invalid file
     * @throw InvalidInputDataException Invalid structure of input data
     */
    SequenceDiagram loadDiagram() override;

    /**
     * Saves diagram to defined target
     *
     * @param diagram Sequence diagram to save
     * @throw InvalidDataStorageException Invalid file
     */
    void saveDiagram(const SequenceDiagram &diagram) override;

  private:
    /**
     * Loads single object from XML element
     *
     * @param xmlObject XML element with object
     * @return Pointer to loaded object
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Object *loadObject(QDomElement &xmlObject);

    /**
     * Loads single message from XML element
     *
     * @param xmlMessage XML element with message
     * @param sequenceDiagram Sequence diagram for linking objects and actors
     * @return Pointer to loaded message
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Message *loadMessage(QDomElement &xmlMessage, SequenceDiagram &sequenceDiagram);
};

#endif //ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H
