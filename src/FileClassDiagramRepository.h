/**
 * @file FileClassDiagramRepository.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_FILE_CLASS_DIAGRAM_REPOSITORY_H
#define ICP_PROJECT_FILE_CLASS_DIAGRAM_REPOSITORY_H


#include <QDomElement>
#include "ClassDiagramRepository.h"

/**
 * File repository for class diagrams
 */
class FileClassDiagramRepository: public ClassDiagramRepository
{
    /**
     * Name of the file to use (full relative/absolute file)
     */
    std::string fileName;

  public:
    /**
     * Implicit constructor
     */
    FileClassDiagramRepository(): fileName{} {};

    /**
     * Constructor for initialization with known name of file
     *
     * @param fileName Name of the file to work with (full relative/absolute path)
     */
    explicit FileClassDiagramRepository(std::string fileName): fileName{fileName} {};

    /**
     * Virtual default destructor
     */
    virtual ~FileClassDiagramRepository() = default;

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
     * @return Loaded class diagram
     * @throw InvalidDataStorageException Invalid file
     * @throw InvalidInputDataException Invalid structure of input data
     */
    ClassDiagram loadDiagram() override;

    /**
     * Saves diagram to defined target
     *
     * @param diagram Class diagram to save
     * @throw InvalidDataStorageException Invalid file
     */
    void saveDiagram(ClassDiagram diagram) override;

  private:
    /**
     * Loads single class from XML element
     *
     * @param xmlClass XML element with class
     * @return Loaded class
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Class loadClass(QDomElement &xmlClass);

    /**
     * Loads single class attribute from XML element
     *
     * @param xmlAttribute XML element with attribute
     * @return Loaded class attribute
     * @throw InvalidInputDataException Invalid structure of input data
     */
    ClassAttribute loadAttribute(QDomElement &xmlAttribute);

    /**
     * Loads single class method from XML element
     *
     * @param xmlMethod XML element with method
     * @return Loaded class method
     * @throw InvalidInputDataException Invalid structure of input data
     */
    ClassMethod loadMethod(QDomElement &xmlMethod);

    /**
     * Loads single relationship from XML element
     *
     * @param xmlRelationship XML element with relationship
     * @param classDiagram Class diagram with classes (of course without relationships)
     * @return Pointer to loaded relationship
     * @throw InvalidInputDataException Invalid structure of input data
     */
    Relationship *loadRelationship(QDomElement &xmlRelationship, ClassDiagram &classDiagram);
};

#endif //ICP_PROJECT_FILE_CLASS_DIAGRAM_REPOSITORY_H
