#pragma once

#include <boost/shared_ptr.hpp>

class Handler;

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
