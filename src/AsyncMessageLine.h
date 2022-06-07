/**
 * @class AsyncMessageLine
 * Represents asynchronous message in sequence diagram.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ASYNCMESSAGELINE_H
#define ASYNCMESSAGELINE_H

#include "MessageLine.h"

class AsyncMessageLine : public MessageLine
{
public:
    using MessageLine::MessageLine;
};

#endif // ASYNCMESSAGELINE_H
