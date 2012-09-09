#include "MessageQueue.h"
#include "Message.h"
#include "Handler.h"

Message MessageQueue::nextMessage()
{
    Message message;
    
#ifndef MESSAGE_QUEUE_LOCK_FREE
    queueMutex.lock();
#endif
    
    if (!queue.empty())
    {
        message = queue.front();
        queue.pop();
    }
    
#ifndef MESSAGE_QUEUE_LOCK_FREE
    queueMutex.unlock();
#endif

    return message;
}

bool MessageQueue::enqueueMessage(const Message &message)
{
#ifndef MESSAGE_QUEUE_LOCK_FREE
    queueMutex.lock();
#endif
    
    queue.push(message);
    
#ifndef MESSAGE_QUEUE_LOCK_FREE
    queueMutex.unlock();
#endif
    
    return true;
}
