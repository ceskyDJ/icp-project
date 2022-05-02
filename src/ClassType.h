/**
 * @file
 * Enumeration class with class types
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASSTYPE_H
#define ICP_PROJECT_CLASSTYPE_H

/**
 * Type of the "class" from class diagram
 */
enum class ClassType {
    /**
     * Classic class without abstract methods, etc.
     */
    NORMAL_CLASS,
    /**
     * Abstract class with at least one abstract method. No instance could be created from it
     */
    ABSTRACT_CLASS,
    /**
     * Not a class but something like special type of it. Definition of interface (required public methods) for classes
     */
    INTERFACE
};

#endif //ICP_PROJECT_CLASSTYPE_H
