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
#include <tuple>
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
     * Position in canvas
     */
    std::tuple<int, int> coordinates;
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
     * @param coordinates Coordinates in canvas (x, y)
     * @param type Class type (optional, default is normal)
     */
    explicit Class(
        const std::string name,
        const std::tuple<int, int> coordinates,
        const ClassType type = ClassType::NORMAL_CLASS
    ): name{name}, coordinates{coordinates}, classType{type} {};

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
     * Getter for coordinates
     *
     * @return Coordinates in a canvas (x, y)
     */
    std::tuple<int, int> &getCoordinates() {
        return coordinates;
    }

    /**
     * Constant getter for coordinates
     *
     * @return Coordinates in a canvas (x, y)
     */
    const std::tuple<int, int> &getCoordinates() const {
        return coordinates;
    }

    /**
     * Setter for coordinates
     *
     * @param newCoordinates New coordinates to set (x, y) on canvas
     */
    void setCoordinates(const std::tuple<int, int> &newCoordinates) {
        coordinates = newCoordinates;
    }

    /**
     * Setter for class type
     *
     * @param Class type
     */
    void setClassType(ClassType newClasstype)
    {
        classType = newClasstype;
    }

    /**
     * Getter for class type
     *
     * @return Class type
     */
    ClassType getClassType()
    {
        return classType;
    }

    /**
     * Constant getter for class type
     *
     * @return Class type
     */
    const ClassType getClassType() const
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
     * Constant getter for class attributes
     *
     * @return Class attributes
     */
    const std::vector<ClassAttribute> &getAttributes() const
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
     * Constant getter for class methods
     *
     * @return Class methods
     */
    const std::vector<ClassMethod> &getMethods() const
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

    /**
     * Finds class method by its name
     *
     * @param nameToFind Name of the class method search for
     * @return Pointer to found class method
     * @throw std::invalid_argument Non-existing class method with searched name in this class
     */
    ClassMethod *findMethodByName(std::string nameToFind);

    /**
     * Equals operator
     *
     * @param other Class to compare with
     * @return Are classes equal?
     */
    bool operator==(const Class &other)
    {
        return name == other.name;
    }

    /**
     * Not equals operator
     *
     * @param other Class to compare with
     * @return Are classes not equal?
     */
    bool operator!=(const Class &other)
    {
        return name != other.name;
    }
};

#endif //ICP_PROJECT_CLASS_H
