#include <vector>
#include <queue>
#include <map>
#include "club_settings.h"
#include "table.h"
#include "../events/in_events.h"
#include "../events/out_events.h"

class ComputerClub
{
public:
    ComputerClub();
    void setSettings(ClubSettings sets);
    void processEvents(std::vector<InEvent *>);
    void printReport() const;

private:
    ClubSettings settings;
    std::map<unsigned int, Table> tables;
    std::vector<Event *> events;
    std::map<std::string, unsigned int> clients;
    std::queue<std::string> waiting;

    OutEvent *process(InEvent *event);
    OutEvent *process(InCame *event);
    OutEvent *process(InSat *event);
    OutEvent *process(InWaiting *event);
    OutEvent *process(InLeft *event);
};
