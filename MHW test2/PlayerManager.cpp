#include "PlayerManager.h"
#include "PointerFunctions.h"
#include<iostream>

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::ResetPlayers() {
	for (auto& player : players) {
		player = Player();
	}
}

void PlayerManager::PlayerBaseInformation(HANDLE handle, DWORDLONG gamebaseadress ) {

	DWORDLONG playerStructureAdress = { 0 };
	DWORDLONG playerDamageAdress = { 0 };

	partyPointer = GetPointerAddress(handle, gamebaseadress, partyBaseAdress, partyOffsets);
	partyDamagePointer = GetPointerAddress(handle, gamebaseadress, partyDamageAdress, partyDamageOffsets);
	partyCountPointer = GetPointerAddress(handle, gamebaseadress, partyDamageAdress, partyCountOffsets);
	int index = -1;
	for (auto& player : players) {
		index++;
		playerStructureAdress = partyPointer + (index * 0x58);
		ReadProcessMemory(handle, (PBYTE*)playerStructureAdress, &player.playerInformationAdress, sizeof(player.playerInformationAdress), 0);

		player.playerDamageAdress = partyDamagePointer + (index * 0x2A0);
	}
}

const Player& PlayerManager::GetPlayer(int index) const {
	return players[index];
}

void PlayerManager::UpdatePlayer(HANDLE handle) {
	PlayerNames(handle);
	PlayerDamage(handle);

	for (int i = 0; i < currentQuestPlayerCount; i++) {
		std::cout << players[i].name << " Did "<< std::dec << players[i].damage << " damage" << std::endl;

	}
}

void PlayerManager::PlayerNames(HANDLE handle) {
	for (auto& player : players) {
		char nameBuf[33] = { 0 };
		ReadProcessMemory(handle, (PBYTE*)(player.playerInformationAdress + 0x49), &nameBuf, sizeof(nameBuf), 0);
		player.name = nameBuf;
		//std::cout << "player name: " << player.name << std::endl;
	}
}

void PlayerManager::PlayerHRLv(HANDLE handle) {

	for (int i = 0; i < currentQuestPlayerCount; i++) {
		ReadProcessMemory(handle, (PBYTE*)(players[i].playerInformationAdress + 0x70), &players[i].HR, sizeof(players[i].HR), 0);
	}
}

void PlayerManager::PlayerMRLv(HANDLE handle) {

	for (int i = 0; i < currentQuestPlayerCount; i++) {
		ReadProcessMemory(handle, (PBYTE*)(players[i].playerInformationAdress + 0x72), &players[i].MR, sizeof(players[i].MR), 0);
	}
}

void PlayerManager::PlayerDamage(HANDLE handle) {
	totalDamage = 0;
	for (int i = 0; i < currentQuestPlayerCount; i++) {
		ReadProcessMemory(handle, (PBYTE*)players[i].playerDamageAdress , &players[i].damage, sizeof(players[i].damage), 0);
		totalDamage += players[i].damage;
	}
}

void PlayerManager::PlayerDamageProc(HANDLE handle) {
	for (auto& player : players) {
		player.damageProc = player.damage / totalDamage;
	}
}

int PlayerManager::PlayerCount(HANDLE handle) {
	ReadProcessMemory(handle, (PBYTE*)partyCountPointer, &currentQuestPlayerCount, sizeof(currentQuestPlayerCount), 0);
	//std::cout << "player Count: " << currentQuestPlayerCount << std::endl;
	return currentQuestPlayerCount;
}