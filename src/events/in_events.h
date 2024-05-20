#ifndef IN_EVENTS_H
#define IN_EVENTS_H

#include "event.h"
class ComputerClub;
#include "../computer_club/computer_club.h"


enum class InEventType
{
    CAME,
    SAT,
    WAITING,
    LEFT
};

class InEvent : public Event
{
protected:
    InEventType type;
    std::string client;

public:
    virtual void toStr();
    virtual Event* accept(ComputerClub &cc) = 0;
    std::string getClient() const;
    InEvent(unsigned int tm, unsigned int type, std::string client);
};

class InSat : public InEvent
{
private:
    unsigned int table;

public:
    InSat(unsigned int tm, unsigned int type, std::string client, unsigned int table);
    void toStr() override;
    Event* accept(ComputerClub &cc);
    unsigned int getTable() const;
};

class InCame : public InEvent
{
public:
    Event* accept(ComputerClub &cc);
    InCame(unsigned int tm, unsigned int type, std::string client);
};

class InWaiting : public InEvent
{
public:
    Event* accept(ComputerClub &cc);
    InWaiting(unsigned int tm, unsigned int type, std::string client);
};

class InLeft : public InEvent
{
public:
    Event* accept(ComputerClub &cc);
    InLeft(unsigned int tm, unsigned int type, std::string client);
};
#endif
