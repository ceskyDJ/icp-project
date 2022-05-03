/**
 * @file ClassMember.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_MEMBER_H
#define ICP_PROJECT_CLASS_MEMBER_H

#include <string>
#include "AccessModifier.h"

/**
 * General entity for class members
 */
class ClassMember
{
    /**
     * Name of the class member
     */
    std::string name;
    /**
     * Class member's access modifier
     */
    AccessModifier accessModifier;

  public:
    /**
     * Constructor for initializing class member with known name and access modifier
     *
     * @param name Name of the class member
     * @param accessModifier Class member's access modifier
     */
    explicit ClassMember(std::string name, AccessModifier accessModifier): name{name}, accessModifier{accessModifier} {};

    /**
     * Getter for class member name
     *
     * @return Class member name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for class member name
     *
     * @param newName New class member name
     */
    void setName(const std::string &newName)
    {
        name = newName;
    }

    /**
     * Getter for class member access modifier
     *
     * @return Access modifier
     */
    AccessModifier getAccessModifier() const
    {
        return accessModifier;
    }

    /**
     * Setter for class member access modifier
     *
     * @param newAccessModifier New access modifier
     */
    void setAccessModifier(const AccessModifier newAccessModifier)
    {
        accessModifier = newAccessModifier;
    }
};

#endif //ICP_PROJECT_CLASS_MEMBER_H
