/**
 * @file InvalidInputDataException.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_INVALID_INPUT_DATA_EXCEPTION_H
#define ICP_PROJECT_INVALID_INPUT_DATA_EXCEPTION_H

#include "AppException.h"

/**
 * Exception for invalid structure of data input data
 */
class InvalidInputDataException: public AppException
{
  public:
    using AppException::AppException;
};

#endif //ICP_PROJECT_INVALID_INPUT_DATA_EXCEPTION_H
