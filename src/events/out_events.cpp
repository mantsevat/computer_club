#include "out_events.h"
#include <iostream>
OutEvent::OutEvent(unsigned int timem, OutEventType type)
{
    timeM = timem;
    this->type = type;
}
OutLeft::OutLeft(unsigned int timem, OutEventType type, std::string client) : OutEvent(timem, type)
{
    this->client = client;
}
OutError::OutError(unsigned int timem, OutEventType type, std::string er) : OutEvent(timem, type)
{
    errStr = er;
}
OutSat::OutSat(unsigned int timem, OutEventType type, std::string client, unsigned int table) : OutEvent(timem, type)
{
    this->client = client;
    this->table = table;
}
void OutError::toStr()
{
    std::cout << timeToStr() << " " << static_cast<unsigned int>(type)+11 << " " << errStr << '\n';
}
void OutLeft::toStr()
{
    std::cout << timeToStr() << " " << static_cast<unsigned int>(type)+11 << " " << client << '\n';
}
void OutSat::toStr()
{
    std::cout << timeToStr() << " " << static_cast<unsigned int>(type)+11 << " " << client << " " << table << '\n';
}