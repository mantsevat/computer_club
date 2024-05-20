#include "event.h"

std::string Event::timeToStr()
{
    return std::to_string(timeM);
}

unsigned int Event::getTime() const
{
    return timeM;
}
