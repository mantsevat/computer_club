#include "computer_manager.h"
#include "computer_club.h"
#include "event_reader.h"
#include <iostream>
#include <fstream>

void ComputerManager::createStartCClub(char *filename)
{

    std::ifstream settingsfile;
    settingsfile.open(filename);
    if (!settingsfile)
    {
        std::cout << "File was not found!\n";
        return;
    }

    ComputerClub cc;
    EventReader ev;

    try
    {
        cc.setSettings(ev.readSettings(settingsfile));
        cc.processEvents(ev.readEvents(settingsfile));
        cc.printReport();
    }
    catch (std::exception e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return;
}