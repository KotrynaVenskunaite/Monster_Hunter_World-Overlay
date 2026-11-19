#include "MonsterManager.h"
#include "PointerFunctions.h"
#include<iostream>

MonsterManager::MonsterManager()
{
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::MonsterBaseInformation(HANDLE handle, DWORDLONG gamebaseadress) {

	//healthPointer = GetPointerAddress(hwnd, gamebaseadress, BASE_HEALTH_ADRESS, partyOffsets);
	IDAdress = GetPointerAddress(handle, gamebaseadress, BASE_ID_ADRESS, ID_OFFSETS);
	int index = -1;
	for (auto& monster : monsters) {
		localAdressVar = gamebaseadress + 0x5013C50;
		index++;

		ReadProcessMemory(handle, (PBYTE*)localAdressVar, &monster.healthAdress, sizeof(monster.healthAdress), 0);
		localAdressVar = monster.healthAdress + 0xE58 + (index * 0x50);
		ReadProcessMemory(handle, (PBYTE*)localAdressVar, &monster.healthAdress, sizeof(monster.healthAdress), 0);
		localAdressVar = monster.healthAdress + 0x7670;
		ReadProcessMemory(handle, (PBYTE*)localAdressVar, &monster.healthAdress, sizeof(monster.healthAdress), 0);

		//ID adress
		localAdressVar = IDAdress + (index * 0x8);
		ReadProcessMemory(handle, (PBYTE*)localAdressVar, &monster.idAdress, sizeof(monster.idAdress), 0);
	}
}

void MonsterManager::MonsterCurrentHealth(HANDLE handle)
{
	for (auto& monster : monsters) {
		monster.isMonsterOnMap = (ReadProcessMemory(handle, (PBYTE*)(monster.healthAdress + 0x64), &monster.health, sizeof(monster.health), 0) == true) 
			? true 
			: false;
		//std::cout << "current m health: " << monster.health << std::endl;
	}
}

void MonsterManager::MonsterMaxHealth(HANDLE handle)
{
	for (auto& monster : monsters) {
		ReadProcessMemory(handle, (PBYTE*)(monster.healthAdress + 0x60), &monster.maxHealth, sizeof(monster.maxHealth), 0);
	}
}

void MonsterManager::MonsterID(HANDLE handle)
{
	for (auto& monster : monsters) {
		ReadProcessMemory(handle, (PBYTE*)(monster.idAdress + 0x68), &monster.id, sizeof(monster.id), 0);
		monster.name = AssignMonsterName(monster.id);
		//std::cout << "mosnter name: " << monster.name << std::endl;
	}
}

std::string MonsterManager::AssignMonsterName(int id)
{
	return MonsterIDNameMap[id].c_str();
}

const Monsters& MonsterManager::GetMonster(int index) const {
	return monsters[index];
}