#include "event.h"
#pragma once
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
    virtual std::string timeToStr() {};

public:
    void toStr() override;
    std::string getClient() const;
    unsigned int getTime() const {};
    InEvent(unsigned int tm, unsigned int type, std::string client);
};

class InSat : public InEvent
{
private:
    unsigned int table;

public:
    InSat(unsigned int tm, unsigned int type, std::string client, unsigned int table);
    void toStr() override;
    unsigned int getTable() const;
};

class InCame : public InEvent
{
public:
    InCame(unsigned int tm, unsigned int type, std::string client);
};

class InWaiting : public InEvent
{
public:
    InWaiting(unsigned int tm, unsigned int type, std::string client);
};

class InLeft : public InEvent
{
public:
    InLeft(unsigned int tm, unsigned int type, std::string client);
};
