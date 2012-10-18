#pragma once

#include "chronotext/os/MessageQueue.h"

class Looper
{
public:
    MessageQueue messageQueue;

    void run();
};
