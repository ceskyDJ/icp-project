/**
 * @file ClassMethod.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_METHOD_H
#define ICP_PROJECT_CLASS_METHOD_H

#include <vector>
#include <QUuid>
#include <set>
#include "ClassMethodType.h"
#include "MethodParameter.h"
#include "ClassMember.h"
#include "ReferenceUpdater.h"

/**
 * Entity for class method
 */
class ClassMethod: public ClassMember
{
    /**
     * Class method's UUID for unique identification between address changes, etc.
     */
    QUuid uuid;
    /**
     * Pointers to updaters of associated class method references
     */
    std::set<ReferenceUpdater *> methodReferencesUpdaters;

    /**
     * Type of method (normal, abstract)
     */
    ClassMethodType type;
    /**
     * Method's parameters
     */
    std::vector<MethodParameter> parameters;
    /**
     * Data type of return value
     */
    std::string returnDataType;

  public:
    /**
     * Constructor for initializing class with known name, parameters, return data methodType and method methodType
     *
     * @param name Name of the method
     * @param accessModifier Method's access modifier
     * @param parameters Method parameters
     * @param returnDataType Data type of return value (optional, default: void)
     * @param methodType Type of method (optional, default: normal)
     */
    ClassMethod(
        std::string name,
        AccessModifier accessModifier,
        std::vector<MethodParameter> parameters,
        const std::string &returnDataType = "void",
        ClassMethodType methodType = ClassMethodType::NORMAL
    ): ClassMember{name, accessModifier}, uuid{QUuid::createUuid()}, methodReferencesUpdaters{}, type{methodType},
            parameters{parameters}, returnDataType{returnDataType} {};


    /**
     * Class destructor
     */
    ~ClassMethod() override
    {
        // Let class references know that this class will no longer exist
        for (const auto item: methodReferencesUpdaters) {
            item->targetDeleted(getName());
        }
    }

    /**
     * Getter for class method UUID
     *
     * @return Universal unique identifier of the class method (in the whole program)
     */
    QUuid getUuid() const
    {
        return uuid;
    }

    /**
     * Adds associated class method reference
     *
     * @param methodReferenceUpdater Updater of class method reference associated with this class method
     */
    void addMethodReferenceUpdater(ReferenceUpdater *methodReferenceUpdater)
    {
        methodReferencesUpdaters.insert(methodReferenceUpdater);
    }

    /**
     * Removes associated class method reference
     *
     * @param methodReferenceUpdater Updater of class method reference associated with this class method (to be removed)
     */
    void removeMethodReferenceUpdater(ReferenceUpdater *methodReferenceUpdater)
    {
        methodReferencesUpdaters.erase(methodReferenceUpdater);
    }

    /**
     * Getter for class method reference updaters
     *
     * @return Pointers to updaters of associated class method references
     */
    std::set<ReferenceUpdater *> getMethodReferenceUpdaters()
    {
        return methodReferencesUpdaters;
    }

    /**
     * Setter for class method reference updaters
     *
     * @param newMethodReferenceUpdaters New pointers to updaters of associated class method references
     */
    void setMethodReferenceUpdaters(std::set<ReferenceUpdater *> newMethodReferenceUpdaters)
    {
        methodReferencesUpdaters = newMethodReferenceUpdaters;
    }

    /**
     * Getter for method type
     *
     * @return Method type (normal, abstract)
     */
    ClassMethodType getType() const
    {
        return type;
    }

    /**
     * Setter for method type
     *
     * @param newMethodType New method type
     */
    void setType(ClassMethodType newMethodType)
    {
        type = newMethodType;
    }

    /**
     * Getter for method parameters
     *
     * @return Method parameters
     */
    std::vector<MethodParameter> getParameters()
    {
        return parameters;
    }

    /**
     * Constant getter for method parameters
     *
     * @return Method parameters
     */
    const std::vector<MethodParameter> getParameters() const
    {
        return parameters;
    }

    /**
     * Setter for method parameters
     *
     * @param newParameters New method parameters
     */
    void setParameters(std::vector<MethodParameter> &newParameters)
    {
        parameters = newParameters;
    }

    /**
     * Getter for data type of return value
     *
     * @return Data type of return value
     */
    std::string getReturnDataType() const
    {
        return returnDataType;
    }

    /**
     * Setter for data type of return value
     *
     * @param newReturnDataType New data type of return value
     */
    void setReturnDataType(const std::string &newReturnDataType)
    {
        returnDataType = newReturnDataType;
    }

    /**
     * Equals operator for two class methods
     *
     * @param other Other class method
     * @return Are class methods equal?
     */
    bool operator==(const ClassMethod &other) const
    {
        return ClassMember::operator==(other) && type == other.type && parameters == other.parameters
            && returnDataType == other.returnDataType;
    }

    /**
     * Equals operator for class method and other class member
     *
     * @param other Other class member
     * @return Class members are of different type, so false is returned everytime
     */
    bool operator==(const ClassMember &) const override
    {
        return false;
    }

    /**
     * Not equals operator for two class methods
     *
     * @param other Other class method
     * @return Are class methods not equal?
     */
    bool operator!=(const ClassMethod &other) const
    {
        return !operator==(other);
    }

    /**
     * Not equals operator for class method and other class member
     *
     * @param other Other class member
     * @return Class members are of different type, so true is always returned
     */
    bool operator!=(const ClassMember &) const override
    {
        return true;
    }
};

#endif //ICP_PROJECT_CLASS_METHOD_H
