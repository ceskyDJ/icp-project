/**
 * @file FileSequenceDiagramRepository.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H
#define ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H

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
     * Implicit constructor
     */
    FileSequenceDiagramRepository(): fileName{} {};

    /**
     * Constructor for initialization with known name of file
     *
     * @param fileName Name of the file to work with (full relative/absolute path)
     */
    explicit FileSequenceDiagramRepository(std::string fileName): fileName{fileName} {};

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
     */
    SequenceDiagram loadDiagram() override;

    /**
     * Saves diagram to defined target
     *
     * @param diagram Sequence diagram to save
     * @throw InvalidDataStorageException Invalid file
     */
    void saveDiagram(SequenceDiagram diagram) override;
};

#endif //ICP_PROJECT_FILE_SEQUENCE_DIAGRAM_REPOSITORY_H
