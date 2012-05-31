//
//  Looper.cpp
//  MessagePump3
//
//  Created by Ariel Malka on 3/18/12.
//  Copyright (c) 2012 chronotext.com. All rights reserved.
//

#include "Looper.h"
#include "Message.h"
#include "Handler.h"

void Looper::run()
{
    while (true)
    {
        Message message = messageQueue.nextMessage();
        
        if (message.target)
        {
            message.target->handleMessage(message);
        }
        else
        {
            break;
        }
    }
}
