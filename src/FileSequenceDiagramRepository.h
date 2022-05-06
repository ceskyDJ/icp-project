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
    /**
     * Name of the file to use (full relative/absolute file)
     */
    std::string fileName;

public:
    /**
     * Constructor for initialization with known class diagram
     *
     * @param classDiagram Class diagram to use as a source for classes, methods, etc.
     */
    explicit FileSequenceDiagramRepository(
        ClassDiagram classDiagram
    ): SequenceDiagramRepository{classDiagram}, fileName{} {};

    /**
     * Constructor for initialization with known name of file
     *
     * @param classDiagram Class diagram to use as a source for classes, methods, etc.
     * @param fileName Name of the file to work with (full relative/absolute path)
     */
    explicit FileSequenceDiagramRepository(
        ClassDiagram classDiagram,
        std::string fileName
    ): SequenceDiagramRepository{classDiagram}, fileName{fileName} {};

    /**
     * Virtual default destructor
     */
    virtual ~FileSequenceDiagramRepository() = default;

    /**
     * Getter for used file name
     *
     * @return Used file name (full relative/absolute path)
     */
    std::string getFileName() const
    {
        return fileName;
    }

    /**
     * Setter for used file name
     *
     * @param newFileName New file name to use (full relative/absolute path)
     */
    void setFileName(const std::string &newFileName)
    {
        fileName = newFileName;
    }

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
    void saveDiagram(SequenceDiagram diagram) override;

  private:
    /**
     * Loads single object from XML element
     *
     * @param xmlObject XML element with object
     * @return Loaded object
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Object loadObject(QDomElement &xmlObject);

    /**
     * Loads single message from XML element
     *
     * @param xmlMessage XML element with message
     * @param sequenceDiagram Sequence diagram for linking objects and actors
     * @return Loaded message
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Message loadMessage(QDomElement &xmlMessage, SequenceDiagram &sequenceDiagram);
};

#endif //ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H
