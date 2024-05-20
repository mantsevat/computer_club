#include "event.h"

std::string Event::timeToStr()
{
    std::string t_str = "";
    unsigned int hours = (unsigned int) timeM / 60;
    unsigned int minutes = timeM - hours*60;
    if (hours < 10){
        t_str+="0";
    }
    t_str+=std::to_string(hours);
    t_str+=":";
    if (minutes < 10){
        t_str+="0";
    }
    t_str+=std::to_string(minutes);
    return t_str;
}

unsigned int Event::getTime() const
{
    return timeM;
}
