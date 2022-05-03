/**
 * @file AccessModifier.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_ACCESS_MODIFIER_H
#define ICP_PROJECT_ACCESS_MODIFIER_H

/**
 * Enumeration for access modifier for methods and class attributes (used in class diagram)
 */
enum class AccessModifier
{
    /**
     * Completely public, everyone see it
     */
    PUBLIC,
    /**
     * Completely private, only owning class see it
     */
    PRIVATE,
    /**
     * Private for owning class and its children
     */
    PROTECTED,
    /**
     * Public in the same package/module
     */
    PACKAGE_PRIVATE
};

#endif //ICP_PROJECT_ACCESS_MODIFIER_H
