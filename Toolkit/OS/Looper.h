//
//  Looper.h
//  MessagePump3
//
//  Created by Ariel Malka on 3/18/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#pragma once

#include "MessageQueue.h"

class Looper
{
public:
    MessageQueue messageQueue;

    void run();
};
