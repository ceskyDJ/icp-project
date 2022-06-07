/**
 * @file MethodReference.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_METHOD_REFERENCE_H
#define ICP_PROJECT_METHOD_REFERENCE_H

#include <cassert>
#include "ClassMethod.h"

/**
 * Smart "reference" optionally points to class method, when the class method exists
 *
 * @par This entity is used when pointed class method hasn't to exist. When it exists,
 * this behaves like standard pointer to class method. When the class method doesn't exist,
 * this acts as a "fake" class method with referred name.
 */
class MethodReference
{
    /**
     * Stored pointer referred class method or nullptr when the class method can't be pointed here (doesn't exist)
     */
    ClassMethod *referredMethod;
    /**
     * Fake class method used when pointer to referred class method is invalid
     */
    ClassMethod fakeMethod;
    /**
     * Updater for the method reference for getting information about reference target changes
     */
    ReferenceUpdater updater{
            [&](const std::string &foo) { invalidatePointer(foo); },
            [&](void *bar) { storePointer(static_cast<ClassMethod *>(bar)); }
    };

  public:
    /**
     * Implicit constructor used when the class method exists and pointer could be saved here
     *
     * @param referredClass Pointer to referred class method
     */
    MethodReference( // NOLINT(google-explicit-constructor)
        ClassMethod *referredMethod
    ): referredMethod{referredMethod}, fakeMethod{"", AccessModifier::PUBLIC, std::vector<MethodParameter>{}}
    {
        assert(referredMethod != nullptr);

        referredMethod->addMethodReferenceUpdater(&updater);
    };

    /**
     * Constructor for case when the referred class method doesn't exist
     *
     * @param referredMethodName Name of the referred class method
     */
    explicit MethodReference(
            const std::string &referredMethodName
    ): referredMethod{nullptr}, fakeMethod{referredMethodName, AccessModifier::PUBLIC, std::vector<MethodParameter>{}} {};

    /**
     * Class destructor
     */
    ~MethodReference()
    {
        // Remove updater for non-existing class method reference
        if (referredMethod != nullptr) {
            referredMethod->removeMethodReferenceUpdater(&updater);
        }
    }

    /**
     * Checks if valid pointer to referred class method is stored
     *
     * @return Is the pointer to referred class method valid?
     */
    bool isValid()
    {
        return referredMethod != nullptr;
    }

    /**
     * Invalidates stored pointer (referred class method has been deleted, etc.)
     *
     * @param methodName Name of the referred class method the pointer was pointed to
     */
    void invalidatePointer(const std::string &methodName)
    {
        referredMethod = nullptr;
        fakeMethod.setName(methodName);
    }

    /**
     * Replaces currently stored pointer or activates pointer to referred class method for the first time
     *
     * @param pointer Pointer to referred class method
     */
    void storePointer(ClassMethod *pointer)
    {
        referredMethod = pointer;

        // For cases referenced class method was added lately
        referredMethod->addMethodReferenceUpdater(&updater);
    }

    /**
     * Getter for referred method name
     *
     * @return Name of the referred method
     */
    std::string getReferredMethodName()
    {
        if (referredMethod == nullptr) {
            return fakeMethod.getName();
        }

        return referredMethod->getName();
    }

    /**
     * Implicit conversion to bool operator
     *
     * @return Is the pointer to referred class method valid?
     */
    operator bool() // NOLINT(google-explicit-constructor)
    {
        return isValid();
    }

    /**
     * Pointer dereference operator
     *
     * @return Referred class method if it exists or fake class method with the corresponding name when doesn't
     */
    ClassMethod operator *()
    {
        if (referredMethod != nullptr) {
            return *referredMethod;
        }

        return fakeMethod;
    }

    /**
     * Arrow operator
     *
     * @return Pointer to referred class method if it exists or pointer to fake class method with
     * the corresponding name when doesn't
     */
    ClassMethod *operator ->()
    {
        if (referredMethod != nullptr) {
            return referredMethod;
        }

        return &fakeMethod;
    }
};

#endif //ICP_PROJECT_METHOD_REFERENCE_H
