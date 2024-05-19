#include <vector>
#include <queue>
#include "club_settings.h"
#include "./events/in_events.h"

class ComputerClub
{
public:
    ComputerClub();
    void setSettings(ClubSettings sets);
    void printReport();
    void processEvents(std::vector<Event *>);

private:
    ClubSettings settings;
    std::vector<Event *> events;
    std::vector<bool> tables;
    std::queue<std::string> waiting;

    void process(InCame *event);
    void process(InSat *event);
    void process(InWaiting *event);
    void process(InLeft *event);

    
};