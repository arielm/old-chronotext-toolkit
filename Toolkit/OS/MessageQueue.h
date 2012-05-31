//
//  MessageQueue.h
//  MessagePump3
//
//  Created by Ariel Malka on 3/18/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#pragma once

class Message;

#include <boost/thread/mutex.hpp>

#include <queue>

class MessageQueue
{
    std::queue<Message> queue;
    boost::mutex queueMutex;
    
public:
    Message nextMessage();
    bool enqueueMessage(const Message &message);
};
