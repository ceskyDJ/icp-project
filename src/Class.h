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
#include <set>
#include <string>
#include <tuple>
#include <QUuid>
#include "ClassAttribute.h"
#include "ClassMethod.h"
#include "ClassType.h"
#include "ReferenceUpdater.h"

/**
 * Entity representing class
 */
class Class
{
    /**
     * Class's UUID for unique identification between address changes, etc.
     */
    QUuid uuid;
    /**
     * Pointers to updaters of associated class references
     */
    std::set<ReferenceUpdater *> classReferencesUpdaters;

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
    Class(): uuid{QUuid::createUuid()}, classReferencesUpdaters{}, classType{ClassType::NORMAL_CLASS} {};
    /**
     * Constructor for initializing class with known name and type
     *
     * @param name Class name
     * @param coordinates Coordinates in canvas (x, y)
     * @param type Class type (optional, default is normal)
     */
    explicit Class(
        const std::string &name,
        const std::tuple<int, int> coordinates,
        const ClassType type = ClassType::NORMAL_CLASS
    ): uuid{QUuid::createUuid()}, classReferencesUpdaters{}, name{name}, coordinates{coordinates}, classType{type} {};

    /**
     * Class destructor
     */
    ~Class()
    {
        // Let class references know that this class will no longer exist
        for (const auto item: classReferencesUpdaters) {
            item->targetDeleted(name);
        }
    }

    /**
     * Getter for class UUID
     *
     * @return Universal unique identifier of the class
     */
    QUuid getUuid() const
    {
        return uuid;
    }

    /**
     * Adds associated class reference
     *
     * @param classReferenceUpdater Updater of class reference associated with this class
     */
    void addClassReferenceUpdater(ReferenceUpdater *classReferenceUpdater)
    {
        classReferencesUpdaters.insert(classReferenceUpdater);
    }

    /**
     * Removes associated class reference
     *
     * @param classReferenceUpdater Updater of class reference associated with this class (to be removed)
     */
    void removeClassReferenceUpdater(ReferenceUpdater *classReferenceUpdater)
    {
        classReferencesUpdaters.erase(classReferenceUpdater);
    }

    /**
     * Getter for class reference updaters
     *
     * @return Pointers to updaters of associated class references
     */
    std::set<ReferenceUpdater *> getClassReferenceUpdaters()
    {
        return classReferencesUpdaters;
    }

    /**
     * Setter for class reference updaters
     *
     * @param newClassReferenceUpdaters New pointers to updaters of associated class references
     */
    void setClassReferenceUpdaters(std::set<ReferenceUpdater *> newClassReferenceUpdaters)
    {
        classReferencesUpdaters = newClassReferenceUpdaters;
    }

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
     * @param newName New class name
     */
    void setName(const std::string &newName)
    {
        name = newName;
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
     * @param newClassType New class type
     */
    void setClassType(ClassType newClassType)
    {
        classType = newClassType;
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
     * @param newAttributes New class attributes
     */
    void setAttributes(std::vector<ClassAttribute> &newAttributes)
    {
        attributes = newAttributes;
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
    void addMethod(ClassMethod &method)
    {
        methods.push_back(method);
    }

    /**
     * Adds a new method to class
     *
     * @param method New method to add
     */
    void addMethod(ClassMethod &&method)
    {
        addMethod(method);
    }

    /**
     * Finds class method by its name
     *
     * @param nameToFind Name of the class method search for
     * @return Pointer to found class method or nullptr when method with searched name isn't in this class
     */
    ClassMethod *findMethodByName(const std::string &nameToFind);

    /**
     * Equals operator
     *
     * @param other Class to compare with
     * @return Are classes equal?
     */
    bool operator==(const Class &other) const
    {
        return name == other.name && coordinates == other.coordinates && classType == other.classType
            && attributes == other.attributes && methods == other.methods;
    }

    /**
     * Not equals operator
     *
     * @param other Class to compare with
     * @return Are classes not equal?
     */
    bool operator!=(const Class &other) const
    {
        return !operator==(other);
    }
};

#endif //ICP_PROJECT_CLASS_H
