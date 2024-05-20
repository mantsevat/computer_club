#include <vector>
#include <fstream>
#include "../events/in_events.h"
#include "club_settings.h"

class EventReader
{
public:
    std::vector<InEvent *> readEvents(std::ifstream &open_file);
    ClubSettings readSettings(std::ifstream &open_file);
};
