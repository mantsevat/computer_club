#include "computer_club.h"
#include "../timeto24h.h"
#include <cmath>
#include <iostream>
#include <algorithm>

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
    incomeAtClosing();
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
    unsigned int wanted = event->getTable();

    if (clients.count(event->getClient()) < 1)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "ClientUnknown");
    }

    if (tables.at(wanted).busy)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "PlaceIsBusy");
    }

    clients[event->getClient()] = event->getTable();
    tables[wanted].busy = true;
    tables[wanted].time_sat = event->getTime();
    tables[wanted].client = event->getClient();

    return nullptr;
}

OutEvent *ComputerClub::process(InWaiting *event)
{
    unsigned int freetb = 0;

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
    if (clients.count(event->getClient()) < 1)
    {
        return new OutError(event->getTime(), OutEventType::ERROR, "ClientUnknown");
    }

    unsigned int freed_id = clients.at(event->getClient());
    Table ftable = tables.at(freed_id);

    clients.erase(event->getClient());
    unsigned int client_time = event->getTime() - ftable.time_sat;

    ftable.timeBusy += client_time;

    if (waiting.size() > 0)
    {
        std::string first = waiting.front();
        waiting.pop();

        ftable.client = first;

        clients[first] = freed_id;

        return new OutSat(event->getTime(), OutEventType::SAT, first, freed_id);
    }
    tables[freed_id] = ftable;

    return nullptr;
}

void ComputerClub::printReport() const
{
    std::cout << minto24h(settings.open) << '\n';

    for (auto iter = events.begin(); iter != events.end(); iter++)
    {
        (*iter)->toStr();
    }

    for (const auto &[tableid, table] : tables)
    {
        std::cout << tableid << " " << std::ceil((float)table.timeBusy / 60) * settings.costph << " " << minto24h(table.timeBusy) << '\n';
    }

    std::cout << minto24h(settings.close) << '\n';
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
    for (auto ev : events)
    {
        delete ev;
    }
    events.clear();
}
void ComputerClub::incomeAtClosing()
{
    std::vector<std::pair<std::string, unsigned int>> cleft(clients.begin(), clients.end());

    auto compare = [](const std::pair<std::string, unsigned int> &lp, const std::pair<std::string, unsigned int> &rp)
    {
        return lp.first > rp.first;
    };

    std::stable_sort(cleft.begin(), cleft.end(), compare);

    unsigned int freed_id;
    Table ftable;

    unsigned int client_time;

    for (const auto &ct : cleft)
    {

        events.push_back(new OutLeft(settings.close, OutEventType::LEFT, ct.first));

        freed_id = clients.at(ct.first);
        ftable = tables.at(freed_id);
        clients.erase(ct.first);
        client_time = settings.close - ftable.time_sat;
        ftable.timeBusy += client_time;
        tables[freed_id] = ftable;
    }
}