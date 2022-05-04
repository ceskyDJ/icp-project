/**
 * @file Class.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_H
#define ICP_PROJECT_CLASS_H

#include <utility>
#include <vector>
#include <string>
#include "ClassAttribute.h"
#include "ClassMethod.h"
#include "ClassType.h"

/**
 * Entity representing class
 */
class Class
{
    /**
     * Name of the class
     */
    std::string name;
    /**
     * Class type (normal, abstract or interface)
     */
    ClassType classType;
    /**
     * Class's attributes
     */
    std::vector<ClassAttribute> attributes;
    /**
     * Class's methods
     */
    std::vector<ClassMethod> methods;

  public:
    /**
     * Implicit class constructor
     */
    Class(): classType{ClassType::NORMAL_CLASS} {};
    /**
     * Constructor for initializing class with known name and type
     *
     * @param name Class name
     * @param type Class type (optional, default is normal)
     */
    explicit Class(const std::string name, const ClassType type = ClassType::NORMAL_CLASS): name{name}, classType{type} {};

    /**
     * Getter for class name
     *
     * @return Class name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for class name
     *
     * @param new_name New class name
     */
    void setName(const std::string &new_name)
    {
        name = new_name;
    }

    /**
     * Getter for class type
     *
     * @return Class type
     */
    ClassType getClassType() const
    {
        return classType;
    }

    /**
     * Getter for class attributes
     *
     * @return Class attributes
     */
    std::vector<ClassAttribute> &getAttributes()
    {
        return attributes;
    }

    /**
     * Setter for class attributes
     *
     * @param new_attributes New class attributes
     */
    void setAttributes(std::vector<ClassAttribute> &new_attributes)
    {
        attributes = new_attributes;
    }

    /**
     * Adds a new attribute to class
     *
     * @param attribute New attribute to add
     */
    void addAttribute(const ClassAttribute& attribute)
    {
        attributes.push_back(attribute);
    }

    /**
     * Getter for class methods
     *
     * @return Class methods
     */
    std::vector<ClassMethod> &getMethods()
    {
        return methods;
    }

    /**
     * Setter for class methods
     *
     * @param new_methods New class methods
     */
    void setMethods(std::vector<ClassMethod> &new_methods)
    {
        methods = new_methods;
    }

    /**
     * Adds a new method to class
     *
     * @param method New method to add
     */
    void addMethod(ClassMethod method)
    {
        methods.push_back(method);
    }
};

#endif //ICP_PROJECT_CLASS_H