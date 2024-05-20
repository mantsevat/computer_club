#include <iostream>
#include "in_events.h"

InEvent::InEvent(unsigned int tm, unsigned int type, std::string client)
{
    timeM = tm;
    this->type = static_cast<InEventType>(type);
    this->client = client;
}
void InEvent::toStr()
{
    std::cout <<timeToStr()<<" "<< static_cast<unsigned int>(type)<< " " <<client<<'\n';
}

void InSat::toStr()
{
    std::cout <<timeToStr()<<" "<< static_cast<unsigned int>(type)<<" "<<client<<" "<<table<<'\n';
}

std::string InEvent::getClient() const
{
    return client;
}

unsigned int InSat::getTable() const
{
    return table;
}

InSat::InSat(unsigned int tm, unsigned int type, std::string client, unsigned int table) : InEvent(tm, type, client)
{
    this->table = table;
}

InCame::InCame(unsigned int tm, unsigned int type, std::string client) : InEvent(tm, type, client)
{
}

InLeft::InLeft(unsigned int tm, unsigned int type, std::string client) : InEvent(tm, type, client)
{
}

InWaiting::InWaiting(unsigned int tm, unsigned int type, std::string client) : InEvent(tm, type, client)
{
}

Event* InSat::accept(ComputerClub &cc){
    return cc.process(this);
}

Event* InLeft::accept(ComputerClub &cc){
    return cc.process(this);
}
Event* InCame::accept(ComputerClub &cc){
    return cc.process(this);
}
Event* InWaiting::accept(ComputerClub &cc){
    return cc.process(this);
}