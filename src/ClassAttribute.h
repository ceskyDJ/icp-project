/**
 * @file ClassAttribute.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_CLASS_ATTRIBUTE_H
#define ICP_PROJECT_CLASS_ATTRIBUTE_H

#include "ClassMember.h"

/**
 * Entity for class attribute
 */
class ClassAttribute: public ClassMember
{
    /**
     * Class attribute's data type
     */
    std::string dataType;

  public:
    /**
     * Constructor for initializing with known name, access modifier and data type
     *
     * @param name Class attribute's name
     * @param accessModifier Class attribute's access modifier
     * @param dataType Data type of the attribute
     */
    ClassAttribute(
        std::string name,
        AccessModifier accessModifier,
        std::string dataType
    ): ClassMember(name, accessModifier), dataType{dataType} {};


    /**
     * Getter for data type of the class attribute
     *
     * @return Data type of the class attribute
     */
    std::string getDataType() const
    {
        return dataType;
    }

    /**
     * Setter for class attribute's data type
     *
     * @param newDataType New data type of the class attribute
     */
    void setDataType(const std::string &newDataType)
    {
        dataType = newDataType;
    }
};

#endif //ICP_PROJECT_CLASS_ATTRIBUTE_H
