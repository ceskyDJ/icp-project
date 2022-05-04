/**
 * @file ClassDiagram.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_DIAGRAM_H
#define ICP_PROJECT_CLASS_DIAGRAM_H

#include "Class.h"
#include "Relationship.h"

/**
 * Entity for complete class diagram
 */
class ClassDiagram
{
    /**
     * Classes contained in class diagram
     */
    std::vector<Class> classes;
    /**
     * Relationships between classes
     */
    std::vector<Relationship> relationships;

  public:
    /**
     * Constructor for empty class diagram
     */
    ClassDiagram(): classes{}, relationships{} {};
    /**
     * Constructor for initializing class diagram with known classes and relationships
     *
     * @param classes Classes
     * @param relationships Relationships between classes
     */
    ClassDiagram(
        std::vector<Class> classes,
        std::vector<Relationship> relationships
    ): classes{classes}, relationships{relationships} {};

    /**
     * Getter for classes
     *
     * @return Vector of stored classes
     */
    std::vector<Class> &getClasses()
    {
        return classes;
    }

    /**
     * Setter for classes
     *
     * @param newClasses New vector of classes to store
     */
    void setClasses(std::vector<Class> &newClasses)
    {
        classes = newClasses;
    }

    /**
     * Adds a new class to diagram
     *
     * @param newClass New class to add
     */
    void addClass(Class &newClass)
    {
        classes.push_back(newClass);
    }

    /**
     * Getter for relationships between classes
     *
     * @return Vector of relationships
     */
    std::vector<Relationship> &getRelationships()
    {
        return relationships;
    }

    /**
     * Adds a new relationship to diagram
     *
     * @param newRelationship New relationship to add
     */
    void addRelationship(Relationship &newRelationship)
    {
        relationships.push_back(newRelationship);
    }

    /**
     * Setter for relationships between classes
     *
     * @param newRelationships New vector of relationships
     */
    void setRelationships(std::vector<Relationship> &newRelationships)
    {
        relationships = newRelationships;
    }
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_H
