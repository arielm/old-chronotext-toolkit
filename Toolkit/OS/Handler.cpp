#include "Handler.h"
#include "Message.h"
#include "MessageQueue.h"
#include "Looper.h"

void Handler::setLooper(Looper *looper)
{
    this->looper = looper;
}

bool Handler::sendMessage(const Message &message)
{
    if (looper)
    {
        Message tmp = message;
        tmp.target = this;

        return looper->messageQueue.enqueueMessage(tmp);
    }
    
    return false;
}
