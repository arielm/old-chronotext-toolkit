#pragma once

#include "MessageQueue.h"

class Looper
{
public:
    MessageQueue messageQueue;

    void run();
};
