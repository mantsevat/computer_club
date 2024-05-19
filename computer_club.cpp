#include "computer_club.h"
ComputerClub::ComputerClub()
{
}
void ComputerClub::setSettings(ClubSettings sets)
{
    settings = sets;
}

void ComputerClub::processEvents(std::vector<Event *>)
{
}
void ComputerClub::process(InCame *event)
{
}

void ComputerClub::process(InSat *event)
{
}
void ComputerClub::process(InWaiting *event)
{
}
void ComputerClub::process(InLeft *event)
{
}

void ComputerClub::printReport()
{
}