#include <string>
#pragma once

class Event
{
public:
    virtual void toStr()= 0;
    unsigned int getTime() const;

protected:
    unsigned int timeM;
    std::string timeToStr();
};