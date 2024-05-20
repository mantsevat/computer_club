#include "event.h"
#ifndef OUT_EVENTS_H
#define OUT_EVENTS_H
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
    virtual void toStr()=0;
    OutEvent(unsigned int timem, OutEventType type);
};

class OutLeft : public OutEvent
{
private:
    std::string client;

public:
    OutLeft(unsigned int timem, OutEventType type, std::string client);
    void toStr();
};

class OutSat : public OutEvent
{
private:
    unsigned int table;
    std::string client;

public:
    OutSat(unsigned int timem, OutEventType type, std::string client, unsigned int table);
    void toStr();
};

class OutError : public OutEvent
{
private:
    std::string errStr;

public:
    OutError(unsigned int timem, OutEventType type, std::string er);
    void toStr();
};
#endif
