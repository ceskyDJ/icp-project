/**
 * @file Object.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_OBJECT_H
#define ICP_PROJECT_OBJECT_H

#include <memory>
#include "Class.h"
#include "MessageNode.h"
#include "ClassReference.h"

/**
 * Entity representing Object from sequence diagram
 */
class Object: public MessageNode
{
    /**
     * Pointer to instance class of this object
     */
    ClassReference instanceClass;
    /**
     * Start position of lifeline of the object at timeline (normalized => number in interval \<0; 1\>)
     */
    double lifeStart;
    /**
     * Length of lifeline of the object at timeline (normalized => number in interval \<0; 1\>)
     */
    double lifeLength;

  public:
    /**
     * Constructor for initializing with known name, instance class and lifeline position
     *
     * @param instanceClass Pointer to the class the object is created from
     * @param lifeStart Start position (offset) of lifeline at timeline (normalized, in interval \<0; 1\>)
     * @param lifeLength Length of lifeline at timeline (normalized, in interval \<0; 1\>)
     * @param name Name of the object (optional)
     */
    explicit Object(
            ClassReference instanceClass,
            double lifeStart = 0.0,
            double lifeLength = 0.3,
            const std::string name = ""
    ): MessageNode{name}, instanceClass{instanceClass}, lifeStart{lifeStart}, lifeLength{lifeLength} {};

    /**
     * Getter for instance class
     *
     * @return Pointer to instance class (the class object is created from)
     */
    ClassReference getInstanceClass()
    {
        return instanceClass;
    }

    /**
     * Constant getter for instance class
     *
     * @return Pointer to instance class (the class object is created from)
     */
    ClassReference getInstanceClass() const
    {
        return instanceClass;
    }

    /**
     * Setter for instance class
     *
     * @param newClassInstance Pointer to new instance class
     */
    void setInstanceClass(ClassReference newInstanceClass)
    {
        instanceClass = newInstanceClass;
    }

    /**
     * Getter for object's lifeline start
     *
     * @return Lifeline start at timeline in normalized form (interval \<0; 1\>)
     */
    double getLifeStart() const
    {
        return lifeStart;
    }

    /**
     * Setter for object's lifeline start
     *
     * @param newLifeStart New lifeline start at timeline in normalized form (interval \<0; 1\>)
     */
    void setLifeStart(double newLifeStart)
    {
        lifeStart = newLifeStart;
    }

    /**
     * Getter for object's lifeline length
     *
     * @return Length of lifeline at timeline in normalized form (interval \<0; 1\>)
     */
    double getLifeLength() const
    {
        return lifeLength;
    }

    /**
     * Setter for object's lifeline length
     *
     * @param newLifeLength New length of lifeline in normalized form (interval \<0; 1\>)
     */
    void setLifeLength(double newLifeLength)
    {
        lifeLength = newLifeLength;
    }
};

#endif //ICP_PROJECT_OBJECT_H
