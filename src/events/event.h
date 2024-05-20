#include <string>
#pragma once

class Event
{
public:
    virtual void toStr(){};
    unsigned int getTime() const;

protected:
    unsigned int timeM;
    std::string timeToStr();
};
