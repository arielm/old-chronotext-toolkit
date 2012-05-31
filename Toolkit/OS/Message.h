//
//  Message.h
//  MessagePump3
//
//  Created by Ariel Malka on 3/18/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#pragma once

class Handler;

#include <boost/shared_ptr.hpp>

class Message
{
public:
    Handler *target;
    int what;
    boost::shared_ptr<void> object;
    
    Message() : target(NULL) {}
    Message(int what) : target(NULL), what(what) {}
    Message(int what, boost::shared_ptr<void> object) : target(NULL), what(what), object(object) {}
};
