/**
 * @file MethodParameter.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_METHOD_PARAMETER_H
#define ICP_PROJECT_METHOD_PARAMETER_H

#include <string>

/**
 * Entity for method parameter
 */
class MethodParameter
{
    /**
     * Name of the parameter
     */
    std::string name;
    /**
     * Parameter's data type
     */
    std::string dataType;

  public:
    /**
     * Constructor for initialization with known name and data type
     *
     * @param name Parameter's name
     * @param dataType Parameter's data type
     */
    MethodParameter(std::string name, std::string dataType): name{name}, dataType{dataType} {};

    /**
     * Getter for parameter name
     *
     * @return Parameter name
     */
    std::string getName() const
    {
        return const_cast<std::string &>(name);
    }

    /**
     * Setter for parameter name
     *
     * @param newName New parameter name
     */
    void setName(std::string newName)
    {
        name = newName;
    }

    /**
     * Setter for parameter data type
     *
     * @return Parameter data type
     */
    std::string getDataType() const
    {
        return const_cast<std::string &>(dataType);
    }

    /**
     * Setter for parameter data type
     *
     * @param newDataType New parameter data type
     */
    void setDataType(std::string newDataType)
    {
        dataType = newDataType;
    }
};

#endif //ICP_PROJECT_METHOD_PARAMETER_H
