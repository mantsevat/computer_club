#include <iostream>
#include "computer_manager.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "No filename was given!\n";
        return 0;
    }

    if (argc > 2)
    {
        std::cout << "Warning! Multiple names were given, the first one will be used as a filename\n";
    }

    ComputerManager cm;
    cm.createStartCClub(argv[1]);

    return 0;
}