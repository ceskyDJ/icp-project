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
#include <iostream>
#include "Class.h"
#include "Relationship.h"

/**
 * Memento class for class diagram
 */
class ClassDiagramMemento
{
    friend class ClassDiagram;

    /**
     * Pointers to classes contained in class diagram
     */
    const std::vector<Class *> classes;
    /**
     * Pointers to relationships between classes
     */
    const std::vector<Relationship *> relationships;

    /**
     * Private constructor for defining memento's state
     *
     * @param classes Current pointers to classes
     * @param relationships Current pointers to relationships
     */
    ClassDiagramMemento(
            std::vector<Class *> classes,
            std::vector<Relationship *> relationships
    ): classes{classes}, relationships{relationships} {};

  public:
    /**
     * Implicit non-parametric constructor
     *
     * @par Creates memento with state of empty class diagram
     */
    ClassDiagramMemento(): classes{}, relationships{} {};
};

#endif //ICP_PROJECT_CLASS_DIAGRAM_MEMENTO_H
