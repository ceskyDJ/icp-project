/**
 * @file ClassReference.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_OBJECT_REFERENCE_H
#define ICP_PROJECT_OBJECT_REFERENCE_H

#include <cassert>
#include "Class.h"

/**
 * Smart "reference" optionally points to class, when the class exists
 *
 * @par This entity is used when pointed class hasn't to exist. When it exists,
 * this behaves like standard pointer to class. When the class doesn't exist,
 * this acts as a "fake" class with referred name.
 */
class ClassReference
{
    /**
     * Stored pointer referred class or nullptr when the class can't be pointed here (doesn't exist)
     */
    Class *referredClass;
    /**
     * Fake class used when pointer to referred class in invalid
     */
    Class fakeClass;

  public:
    /**
     * Implicit constructor used when the class exists and pointer could be saved here
     *
     * @param referredClass Pointer to referred class
     */
    ClassReference(Class *referredClass): referredClass{referredClass}, fakeClass{} // NOLINT(google-explicit-constructor)
    {
        assert(referredClass != nullptr);
    };

    /**
     * Constructor for case when the referred class doesn't exist
     *
     * @param referredClassName Name of the referred class
     */
    explicit ClassReference(
        std::string referredClassName
    ): referredClass{nullptr}, fakeClass{referredClassName, std::tuple<int, int>{}} {};

    /**
     * Checks if valid pointer to referred class is stored
     *
     * @return Is the pointer to referred class valid?
     */
    bool isValid()
    {
        return referredClass != nullptr;
    }

    /**
     * Invalidates stored pointer (referred class has been deleted, etc.)
     *
     * @param className Name of the referred class the pointer was pointed to
     */
    void invalidatePointer(std::string className)
    {
        referredClass = nullptr;
        fakeClass.setName(className);
    }

    /**
     * Replaces currently stored pointer or activates pointer to referred class for the first time
     *
     * @param pointer Pointer to referred class
     */
    void storePointer(Class *pointer)
    {
        referredClass = pointer;
    }

    /**
     * Getter for referred class name
     *
     * @return Name of the referred class
     */
    std::string getReferredClassName()
    {
        if (referredClass == nullptr) {
            return fakeClass.getName();
        }

        return referredClass->getName();
    }

    /**
     * Implicit conversion to bool operator
     *
     * @return Is the pointer to referred class valid?
     */
    operator bool() // NOLINT(google-explicit-constructor)
    {
        return isValid();
    }

    /**
     * Pointer dereference operator
     *
     * @return Referred class if it exists or fake class with the corresponding name when doesn't
     */
    Class operator *()
    {
        if (referredClass != nullptr) {
            return *referredClass;
        }

        return fakeClass;
    }

    /**
     * Arrow operator
     *
     * @return Pointer to referred class if it exists or pointer to fake class with
     * the corresponding name when doesn't
     */
    Class *operator ->()
    {
        if (referredClass != nullptr) {
            return referredClass;
        }

        return &fakeClass;
    }
};

#endif //ICP_PROJECT_OBJECT_REFERENCE_H
