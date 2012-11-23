#pragma once

#include <string>

class CinderSketchDelegate
{
public:
    virtual ~CinderSketchDelegate() {}
    
    virtual void receiveStringFromSketch(int what, const std::string &body) {}
    virtual void sendStringToSketch(int what, const std::string &body) {}
};
