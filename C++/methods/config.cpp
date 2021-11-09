#include "stdafx.h"

void _loadConfig(Config& config, int& keyAssign)
{
    ifstream fin("config.txt");
    string line;
    while (getline(fin, line))
    {
        istringstream sin(line.substr(line.find("=") + 1));

        //Keybind Selection
        if (line.find("keys") != -1)
            sin >> config.key1;

        //User Defined Recoil Params
        if (line.find("recoilStrength1") != -1)
            sin >> config.recoilStrength1;
        if (line.find("recoilDelay1") != -1)
            sin >> config.recoilDelay1;
        if (line.find("recoilStrength2") != -1)
            sin >> config.recoilStrength2;
        if (line.find("recoilDelay2") != -1)
            sin >> config.recoilDelay2;
        if (line.find("recoilStrength3") != -1)
            sin >> config.recoilStrength3;
        if (line.find("recoilDelay3") != -1)
            sin >> config.recoilDelay3;
        if (line.find("rapidFireDelay") != -1)
            sin >> config.rapidFireDelay;
    }

    //Key Assignment
    if (config.key1 == 1)
    {
        keyAssign = 1;
    }
    else if (config.key1 = 2)
    {
        keyAssign = 2;
    }
}

void _userMENU(int& keyAssign, string& HACK1, string& HACK2, string& HACK3, string& HACK4, string& FLAG)
{
    if (keyAssign == 1)
    {
        recoilSELECTION(HACK1, HACK2, HACK3, HACK4, FLAG);
    }
    else if (keyAssign == 2)
    {
        recoilSELECTION2(HACK1, HACK2, HACK3, HACK4, FLAG);
    }
}