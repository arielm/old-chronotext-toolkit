#pragma once

#include "Message.h"
#include "MessageQueue.h"
#include "Looper.h"

class Handler
{
    Looper *looper;
    
public:
    Handler(Looper *looper) : looper(looper) {}
    
    bool sendMessage(const Message &message);
    virtual void handleMessage(const Message &message) {}
};
