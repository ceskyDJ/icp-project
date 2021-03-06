/**
 * @file AsyncMessageLine.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#ifndef ASYNCMESSAGELINE_H
#define ASYNCMESSAGELINE_H

#include "MessageLine.h"

/**
 * Represents asynchronous message in sequence diagram.
 */
class AsyncMessageLine : public MessageLine
{
public:
    using MessageLine::MessageLine;
};

#endif // ASYNCMESSAGELINE_H
