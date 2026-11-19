#pragma once
#include <string>
#include<Windows.h>
#include "Monster.h"
#include<vector>
#include<map>

class MonsterManager
{
	private:
		Monsters monsters[3];
		static constexpr DWORDLONG BASE_HEALTH_ADRESS = { 0x5013C50 };
		static constexpr DWORDLONG BASE_ID_ADRESS = { 0x04F9F9E0 };
		//DWORDLONG LEVEL_ONE_HEALT_ADRESS = { 0 };
		// DO LEVEL_ONE_HEALT_ADRESS(gamebaseadress + BASE_HEALTH_ADRESS) when creating the class, not at constructor
		// Also read the first level of memory for this adress
		//inline static std::vector<DWORDLONG> HEALTH_OFFSETS{ 0 }; //last offset 64 - health | 60 - max health 0xE58, 0x7670
		// first offset E58 + (index * 0x50)
		inline static const std::vector<DWORDLONG> ID_OFFSETS{ 0x118, 0x0 }; //] i*8]+68

		DWORDLONG localAdressVar = { 0 };
		DWORDLONG IDAdress = { 0 };
        std::map<int, std::string> MonsterIDNameMap = {
            {0, "Anjanath"},
            {1, "Rathalos"},
            {4, "Zorah Magdaros"},
            {7, "Great Jagras"},
            {9, "Rathian"},
            {10, "Pink Rathian"},
            {11, "Azure Rathalos"},
            {12, "Diablos"},
            {13, "Black Diablos"},
            {14, "Kirin"},
            {15, "Behemoth"},
            {16, "Kushala Daora"},
            {17, "Lunastra"},
            {18, "Teostra"},
            {19, "Lavasioth"},
            {20, "Deviljho"},
            {21, "Barroth"},
            {22, "Uragaan"},
            {23, "Leshen"},
            {24, "Pukei-Pukei"},
            {25, "Nergigante"},
            {26, "Xeno'jiiva"},
            {27, "Kulu-Ya-Ku"},
            {28, "Tzitzi-Ya-Ku"},
            {29, "Jyuratodus"},
            {30, "Tobi-Kadachi"},
            {31, "Paolumu"},
            {32, "Legiana"},
            {33, "Great Girros"},
            {34, "Odogaron"},
            {35, "Radobaan"},
            {36, "Vaal Hazak"},
            {37, "Dodogama"},
            {38, "Kulve Taroth"},
            {39, "Bazelgeuse"},
            {40, "Apceros"},
            {41, "Kelbi"},
            {42, "Kelbi"},
            {51, "Ancient Leshen"},
            {61, "Tigrex"},
            {62, "Nargacuga"},
            {63, "Barioth"},
            {64, "Savage Deviljho"},
            {65, "Brachydios"},
            {66, "Glavenus"},
            {67, "Acidic Glavenus"},
            {68, "Fulgur Anjanath"},
            {69, "Coral Pukei-Pukei"},
            {70, "Ruiner Nergigante"},
            {71, "Viper Tobi-Kadachi"},
            {72, "Nightshade Paolumu"},
            {73, "Shrieking Legiana"},
            {74, "Ebony Odogaron"},
            {75, "Blackveil Vaal Hazak"},
            {76, "Seething Bazelgeuse"},
            {77, "Beotodus"},
            {78, "Banbaro"},
            {79, "Velkhana"},
            {80, "Namielle"},
            {81, "Shara Ishvalda"},
            {87, "Alatreon"},
            {88, "Gold Rathian"},
            {89, "Silver Rathalos"},
            {90, "Yian Garuga"},
            {91, "Rajang"},
            {92, "Furious Rajang"},
            {93, "Brute Tigrex"},
            {94, "Zinogre"},
            {95, "Stygian Zinogre"},
            {96, "Raging Brachydios"},
            {97, "Safi'jiiva"},
            {99, "Scarred Yian Garuga"},
            {100, "Frostfang Barioth"},
            {101, "Fatalis"}
        };
		std::string AssignMonsterName(int id);

	public:
		MonsterManager();
		~MonsterManager();

		void MonsterBaseInformation(HANDLE handle, DWORDLONG gamebaseadress);
		void MonsterCurrentHealth(HANDLE handle);
		void MonsterMaxHealth(HANDLE handle);
		void MonsterID(HANDLE handle);
        const Monsters& GetMonster(int index) const;
};

