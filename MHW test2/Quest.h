#pragma once
#include <string>

struct Quest
{
   

    //Variables
    int questStatus = 0;
    int selectedMonster = -1;
    short map = 0;
    bool isHubMap = { 0 };
    int monsterCount = { 0 };
};