/**
 * @file ClassMethodType.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_METHODTYPE_H
#define ICP_PROJECT_CLASS_METHODTYPE_H

/**
 * Enumeration for class method type
 */
enum class ClassMethodType
{
    /**
     * Classic method
     */
    NORMAL,
    /**
     * Abstract method (without implementation/body)
     */
    ABSTRACT
};

#endif //ICP_PROJECT_CLASS_METHODTYPE_H
