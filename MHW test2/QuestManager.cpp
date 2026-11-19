#include "QuestManager.h"
#include "PointerFunctions.h"
#include<iostream>

QuestManager::QuestManager()
{
}

QuestManager::~QuestManager()
{
}

void QuestManager::QuestBaseInformation(HANDLE handle, DWORDLONG gamebaseadress)
{
	questAdress = GetPointerAddress(handle, gamebaseadress, SESSION_QUEST_ADRESS, QUEST_OFFSETS);
	mapAdress = GetPointerAddress(handle, gamebaseadress, PLAYER_DATA_ADRESS, MAP_OFFSETS);
	selectedMonsterAdress = GetPointerAddress(handle, gamebaseadress, SELECTED_MONSTER_ADRESS, SELECTED_MONSTER_OFFSETS);
    monsterCountAdress = GetPointerAddress(handle, gamebaseadress, MONSTER_COUNT_ADRESS, MONSTER_COUNT_OFFSETS);
}

void QuestManager::QuestStatus(HANDLE handle)
{
	ReadProcessMemory(handle, (PBYTE*)questAdress, &quest.questStatus, sizeof(quest.questStatus), 0);
}

void QuestManager::QuestMap(HANDLE handle)
{
	ReadProcessMemory(handle, (PBYTE*)mapAdress, &quest.map, sizeof(quest.map), 0);
    SetPlayableMap();
}

void QuestManager::SetPlayableMap()
{
    quest.isHubMap = std::find(hubMaps.begin(), hubMaps.end(), quest.map) != hubMaps.end();
    //std::cout << "is hub map?: " << quest.isHubMap << std::endl;
}

void QuestManager::SelectedMonster(HANDLE handle)
{
	ReadProcessMemory(handle, (PBYTE*)selectedMonsterAdress, &selectedMonsterValue, sizeof(selectedMonsterValue), 0);
    SetSelectedMonster();
}

void QuestManager::MonsterCount(HANDLE handle)
{
    ReadProcessMemory(handle, (PBYTE*)monsterCountAdress, &quest.monsterCount, sizeof(quest.monsterCount), 0);
}

const Quest& QuestManager::GetQuest() const {
    return quest;
}

void QuestManager::SetSelectedMonster()
{
    switch (selectedMonsterValue) {
    case 0:
        quest.selectedMonster = 1;
        break;
    case 4:
        quest.selectedMonster = 1;
        break;
    case 16:
        quest.selectedMonster = 1;
        break;
    case 17:
        quest.selectedMonster = 2;
        break;
    case 18:
        quest.selectedMonster = 3;
        break;
    case 45:
        quest.selectedMonster = 1;
        break;
    case 46:
        quest.selectedMonster = 2;
        break;
    case 47:
        quest.selectedMonster = 3;
        break;
    case 57:
        quest.selectedMonster = 1;
        break;
    case 58:
        quest.selectedMonster = 2;
        break;
    case 59:
        quest.selectedMonster = 3;
        break;
    case 61:
        quest.selectedMonster = 1;
        break;
    case 62:
        quest.selectedMonster = 2;
        break;
    case 63:
        if (quest.map == 109) {
            quest.selectedMonster = 1;
        }
        else {
            quest.selectedMonster = 3;
        }
        break;
    case 64:
        quest.selectedMonster = 2;
        break;
    case 65:
        quest.selectedMonster = 3;
        break;
    case 67:
        quest.selectedMonster = 1;
        break;
    case 68:
        quest.selectedMonster = 2;
        break;
    case 69:
        quest.selectedMonster = 3;
        break;
    case 80:
        quest.selectedMonster = 1;
        break;
    case 81:
        quest.selectedMonster = 2;
        break;
    case 82:
        quest.selectedMonster = 3;
        break;
    default:
        quest.selectedMonster = -1;
        break;
    }
}