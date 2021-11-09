#pragma once
#include "stdafx.h"

struct Config {
    int   key1;
    int   recoilStrength1;
    int   recoilDelay1;
    int   recoilStrength2;
    int   recoilDelay2;
    int   recoilStrength3;
    int   recoilDelay3;
    int   rapidFireDelay;
};

void _loadConfig(Config& config, int& keyAssign);
void _userMENU(int& keyAssign, string& HACK1, string& HACK2, string& HACK3, string& HACK4, string& FLAG);