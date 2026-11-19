#pragma once
#include <string>

struct Monsters
{
	DWORDLONG healthAdress = { 0 };
	DWORDLONG idAdress = { 0 };
	DWORDLONG maxHealthAdress = { 0 };

	float health = { 0.0f };
	float maxHealth = { 0.0f };
	int id = { 0 };
	bool isMonsterOnMap = { 0 };
	std::string name = { 0 };
};