/**
 * @file InvalidDataStorageException.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_INVALID_DATA_STORAGE_EXCEPTION_H
#define ICP_PROJECT_INVALID_DATA_STORAGE_EXCEPTION_H

#include "AppException.h"

/**
 * Exception for invalid (not set, not existing, not working, etc.) data storage (e.g. file)
 */
class InvalidDataStorageException: public AppException
{
  public:
    using AppException::AppException;
};

#endif //ICP_PROJECT_INVALID_DATA_STORAGE_EXCEPTION_H
