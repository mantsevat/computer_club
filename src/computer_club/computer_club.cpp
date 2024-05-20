#include "computer_club.h"
#include <cmath>
#include <iostream>

ComputerClub::ComputerClub()
{
}
void ComputerClub::setSettings(ClubSettings sets)
{
    settings = sets;
    initTableMap();
}

void ComputerClub::processEvents(std::vector<InEvent *> inevents)
{
    for (InEvent *ev : inevents)
    {
        events.push_back(ev);
        Event *res = ev->accept(*this);
        if (res)
        {
            events.push_back(res);
        }
    }
}
OutEvent *ComputerClub::process(InEvent *event)
{
    return nullptr;
}
OutEvent *ComputerClub::process(InCame *event)
{

    std::string err;
    if (settings.open > event->getTime() | settings.close < event->getTime())
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "NotOpenYet");
    }

    if (clients.count(event->getClient()) > 0)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "YouShallNotPass");
    }
    clients.insert({event->getClient(), 0});

    return nullptr;
}

OutEvent *ComputerClub::process(InSat *event)
{

    if (clients.count(event->getClient()) < 1)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "ClientUnknown");
    }

    if (tables.at(event->getTable()).busy)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "PLaceIsBusy");
    }
    clients[event->getClient()] = event->getTable();
    return nullptr;
}

OutEvent *ComputerClub::process(InWaiting *event)
{
    unsigned int freetb;

    for (const auto &[tableid, table] : tables)
    {
        if (!table.busy)
        {
            freetb++;
        }
    }
    if (freetb > 0)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "ICantWaitNoLonger");
    }

    if (waiting.size() > settings.tblc)
    {
        return new OutLeft(event->getTime(), OutEventType::LEFT, event->getClient());
    }
    waiting.push(event->getClient());

    return nullptr;
}

OutEvent *ComputerClub::process(InLeft *event)
{

    if (clients.count(event->getClient()) > 0)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "ClientUnknown");
    }

    unsigned int freed_id = clients.at(event->getClient());
    Table ftable = tables.at(freed_id);

    clients.erase(event->getClient());
    unsigned int client_time = event->getTime() - ftable.time_sat;

    ftable.timeBusy += client_time;
    ftable.income += (unsigned int)std::ceil(client_time / 60) * settings.costph;

    if (waiting.size() > 0)
    {
        std::string first = waiting.front();
        waiting.pop();
        ftable.client = first;
        clients[first] = freed_id;
        return new OutSat(event->getTime(), OutEventType::SAT, first, freed_id);
    }
    return nullptr;
}

void ComputerClub::printReport() const
{

    for (auto iter = events.begin(); iter != events.end(); iter++)
    {
        (*iter)->toStr();
    }
}
void ComputerClub::initTableMap()
{
    for (unsigned int i = 1; i <= settings.tblc; i++)
    {
        tables.insert({i, Table()});
    }
}

ComputerClub::~ComputerClub()
{
    for (auto ev: events){
        delete ev;
    }
    events.clear();
}
