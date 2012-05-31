//
//  Handler.h
//  MessagePump1
//
//  Created by Ariel Malka on 3/14/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#pragma once

#include "Message.h"
#include "MessageQueue.h"
#include "Looper.h"

class Handler
{
    Looper *looper;
    
public:
    void setLooper(Looper *looper);
    bool sendMessage(const Message &message);
    
    virtual void handleMessage(const Message &message) {}
};
