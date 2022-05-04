/**
 * @file AppException.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_APP_EXCEPTION_H
#define ICP_PROJECT_APP_EXCEPTION_H

#include <exception>
#include <string>
#include <stdexcept>

/**
 * Base class for this application's exceptions
 */
class AppException: public std::logic_error
{
  public:
    /**
     * Implicit constructor
     */
    AppException(): std::logic_error{"General application error"} {};

    /**
     * Constructor for exception with known message
     *
     * @param message Descriptive message about error
     */
    explicit AppException(const std::string &message) : logic_error(message) {};
};

#endif //ICP_PROJECT_APP_EXCEPTION_H
