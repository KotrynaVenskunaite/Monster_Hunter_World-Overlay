#pragma once
#include <string>
#include<Windows.h>
#include<vector>
#include <array>
#include<algorithm>
#include<map>
#include "Quest.h"

class QuestManager
{
	private:
		Quest quest;

		static constexpr DWORD PLAYER_DATA_ADRESS = { 0x500CDA0 };
		static constexpr DWORD SESSION_QUEST_ADRESS = { 0x500ED30 };
		static constexpr DWORD SELECTED_MONSTER_ADRESS = { 0x051C4368 };
		static constexpr DWORD MONSTER_COUNT_ADRESS = { 0x051F36D0 };
		inline static const std::array<short, 11> hubMaps{ 0, 301, 302, 303, 305, 306, 501, 502, 503, 505, 506 };

		inline static const std::vector<DWORDLONG> QUEST_OFFSETS{ 0x38 };
		inline static const std::vector<DWORDLONG> MAP_OFFSETS{ 0x80, 0xEEC0, 0x118 };
		inline static const std::vector<DWORDLONG> SELECTED_MONSTER_OFFSETS{ 0x70, 0x10, 0xD0, 0xCB0 };
		inline static const std::vector<DWORDLONG> MONSTER_COUNT_OFFSETS{ 0x68, 0x1728 };

		int selectedMonsterValue = { 0 };

		void SetPlayableMap();
		void SetSelectedMonster();

		//variables
		DWORDLONG questAdress = { 0 };
		DWORDLONG mapAdress = { 0 };
		DWORDLONG selectedMonsterAdress = { 0 };
		DWORDLONG monsterCountAdress = { 0 };

	public:
		QuestManager();
		~QuestManager();

		void QuestBaseInformation(HANDLE handle, DWORDLONG gamebaseadress);
		void QuestStatus(HANDLE handle);
		void QuestMap(HANDLE handle);
		void SelectedMonster(HANDLE handle);
		void MonsterCount(HANDLE handle);

		const Quest& GetQuest() const;
};

