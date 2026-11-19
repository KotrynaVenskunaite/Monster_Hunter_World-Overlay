#pragma once
#include <string>

struct Player
{
	DWORDLONG playerInformationAdress = { 0 };
	DWORDLONG playerDamageAdress = { 0 };
	std::string name = { 0 };
	int damage = { 0 };
	int HR = { 0 };
	int MR = { 0 };
	float damageProc = { 0 };
	//int weapon
	//int slot;
};