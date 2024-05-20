
#include "timeto24h.h"

std::string minto24h(unsigned int m){
    std::string t_str ="";
    unsigned int hours = (unsigned int)m / 60;
    unsigned int minutes = m - hours * 60;
    if (hours < 10)
    {
        t_str += "0";
    }
    t_str += std::to_string(hours);
    t_str += ":";
    if (minutes < 10)
    {
        t_str += "0";
    }
    t_str += std::to_string(minutes);
    
    return t_str;
}