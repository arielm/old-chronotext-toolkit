//
//  MessageQueue.cpp
//  MessagePump3
//
//  Created by Ariel Malka on 3/18/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#include "MessageQueue.h"
#include "Message.h"
#include "Handler.h"

Message MessageQueue::nextMessage()
{
    Message message;
    
    queueMutex.lock();
    
    if (!queue.empty())
    {
        message = queue.front();
        queue.pop();
    }
    
    queueMutex.unlock();
    
    return message;
}

bool MessageQueue::enqueueMessage(const Message &message)
{
    queueMutex.lock();
    queue.push(message);
    queueMutex.unlock();
    
    return true;
}
