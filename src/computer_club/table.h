#include <string>
#pragma once
struct Table
{
    bool busy = false;
    std::string client = "";
    unsigned int timeBusy = 0;
    unsigned int time_sat = 0;
};
