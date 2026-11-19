#pragma once
#include <string>
#include<Windows.h>
#include "Player.h"
#include<vector>

class PlayerManager
{
	private:
		Player players[4];
		static constexpr DWORDLONG partyBaseAdress = { 0x05013530 }; //Player base information
		static constexpr DWORDLONG partyDamageAdress = { 0x051C46B8 };
		//DWORDLONG partyDamageAdress = { 0x05013950 };
		inline static const std::vector<DWORDLONG> partyOffsets{ 0x1AB0 };
		//Name offsets = 1AB0+(i*58)]+49    i = player positions    (length 32)
		///Name offsets 49
		//HR offsets 70
		//MR offset 72
		inline static const std::vector<DWORDLONG> partyDamageOffsets{ 0x258,0x38,0x450,0x8,0x48 };
		inline static const std::vector<DWORDLONG> partyCountOffsets{ 0x258,0x108, 0x86AC };
		//Damage offset = ADRESS + (i*2A0)
		//slot = index
		//atomic<DWORDLONG>
		DWORDLONG partyPointer = { 0 };
		DWORDLONG partyDamagePointer= { 0 };
		DWORDLONG partyCountPointer = { 0 };
		int currentQuestPlayerCount = { 0 };
		float totalDamage = { 0.0f };

		
	public:
		PlayerManager();
		~PlayerManager();

		int PlayerCount(HANDLE handle);
		void PlayerHRLv(HANDLE handle);
		void PlayerMRLv(HANDLE handle);
		void PlayerDamage(HANDLE handle);
		void PlayerDamageProc(HANDLE handle);
		void ResetPlayers();
		void PlayerBaseInformation(HANDLE handle, DWORDLONG gamebaseadress);
		void PlayerNames(HANDLE handle);

		void UpdatePlayer(HANDLE handle);

		
		const Player& GetPlayer(int index) const;
};

