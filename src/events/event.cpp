#include "event.h"
#include "../timeto24h.h"
std::string Event::timeToStr()
{
    return minto24h(timeM);
}

unsigned int Event::getTime() const
{
    return timeM;
}
