#include <regex>
#include <string>
#include <iostream>
#include <stdexcept>
#include <any>
#include "event_reader.h"

ClubSettings EventReader::readSettings(std::ifstream &open_file)
{
    std::string setlines[3];
    ClubSettings settings;

    std::regex uintrgx("^[1-9][0-9]*$");
    std::regex timergx("^([0-1][0-9]|2[0-3]):([0-5][0-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])$");
    std::smatch m;

    if (!(std::getline(open_file, setlines[0]) && std::getline(open_file, setlines[1]) && std::getline(open_file, setlines[2])))
    {
        throw std::runtime_error("Error while reading settings strings");
    }

    if (std::regex_search(setlines[0], m, uintrgx))
    {
        settings.tblc = std::stoul(m[0]);
    }
    else
    {
        throw std::runtime_error("Error at string :" + setlines[0]);
    }

    if (std::regex_search(setlines[1], m, timergx))
    {
        settings.open = std::stoul(m[1]) * 60 + std::stoul(m[2]);
        settings.close = std::stoul(m[3]) * 60 + std::stoul(m[4]);
    }
    else
    {
        throw std::runtime_error("Error at string :" + setlines[1]);
    }

    if (std::regex_search(setlines[2], m, uintrgx))
    {
        settings.costph = std::stoul(m[0]);
    }
    else
    {
        throw std::runtime_error("Error at string :" + setlines[2]);
    }
    return settings;
}

std::vector<InEvent *> EventReader::readEvents(std::ifstream &open_file)
{
    std::map<unsigned int, std::function<InEvent *(unsigned int, unsigned int, std::string)>> ma = {
        {1, [](unsigned int tm, unsigned int ty, std::string c)
         { return new InCame(tm, ty, c); }},
        {3, [](unsigned int tm, unsigned int ty, std::string c)
         { return new InWaiting(tm, ty, c); }},
        {4, [](unsigned int tm, unsigned int ty, std::string c)
         { return new InLeft(tm, ty, c); }}};
         
    std::vector<InEvent *> inevents;

    std::regex eventrgx("^(([0-1][0-9]|2[0-3]):([0-5][0-9])) ([1-4]) ([a-zA-Z0-9]+) ?([1-9][0-9]*)?$");
    std::smatch m;

    std::string currentline;
    while (std::getline(open_file, currentline))
    {
        if (std::regex_search(currentline, m, eventrgx))
        {
            unsigned event_type = std::stoul(m[4]);
            
            if (event_type == 2)
            {
                inevents.push_back(new InSat(std::stoul(m[2]) * 60 + std::stoul(m[3]), event_type, m[5], std::stoul(m[6])));
            }
            else
            {   
                InEvent* ne =  ma.at(event_type)(std::stoul(m[2]) * 60 + std::stoul(m[3]), event_type, m[5]);
                inevents.push_back(ne);
            }
        }
        else
        {
            throw std::runtime_error("Error at string: " + currentline);
        }
    }

    return inevents;
}