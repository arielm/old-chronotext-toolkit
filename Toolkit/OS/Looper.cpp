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
