#include "event.h"
#pragma once
enum class OutEventType
{
    LEFT,
    SAT,
    ERROR
};

class OutEvent : public Event
{
protected:
    OutEventType type;

public:
    OutEvent(unsigned int timem, OutEventType type);
};

class OutLeft : public OutEvent
{
private:
    std::string client;

public:
    OutLeft(unsigned int timem, OutEventType type, std::string client);
};

class OutSat : public OutEvent
{
private:
    unsigned int table;
    std::string client;

public:
    OutSat(unsigned int timem, OutEventType type, std::string client, unsigned int table);
};

class OutError : public OutEvent
{
private:
    std::string errStr;

public:
    OutError(unsigned int timem, OutEventType type, std::string er);
};
