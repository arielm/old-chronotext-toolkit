#include "Touchable.h"
#include "Shape.h"

namespace chronotext
{
    void Touchable::changeState(int state)
    {
        this->state = state;
        shape->touchStateChanged(this, state);
    }
    
    void Touchable::performAction(int action)
    {
        shape->touchActionPerformed(this, action);
    }
}
