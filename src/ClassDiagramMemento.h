/**
 * @file ClassDiagramMemento.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_CLASS_DIAGRAM_MEMENTO_H
#define ICP_PROJECT_CLASS_DIAGRAM_MEMENTO_H

#include <vector>
#include "Class.h"
#include "Relationship.h"

/**
 * Memento class for class diagram
 */
class ClassDiagramMemento
{
    /**
     * Classes contained in class diagram
     *
     * @warning To access this class attribute use getter getClasses()
     */
    std::vector<Class> classes;
    /**
     * Pointers to relationships between classes
     *
     * @warning To access this class attribute use getter getRelationships()
     */
    std::vector<Relationship *> relationships;

  public:
    /**
     * Implicit non-parametric constructor
     *
     * @par Creates memento with state of empty class diagram
     */
    ClassDiagramMemento(): classes{}, relationships{} {};

private:
    friend class ClassDiagram;
    /**
     * Constructor for defining memento's state
     *
     * @param classes Current classes
     * @param relationships Current relationships
     */
    ClassDiagramMemento(
            std::vector<Class> classes,
            std::vector<Relationship *> relationships
    ): classes{classes}, relationships{relationships} {};

    /**
     * Getter for classes
     *
     * @return Remembered state of classes
     */
    std::vector<Class> getClasses()
    {
        return classes;
    }

    /**
     * Getter for relationships
     *
     * @return Remembered state of relationships
     */
    std::vector<Relationship *> getRelationships()
    {
        return relationships;
    }
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_MEMENTO_H
