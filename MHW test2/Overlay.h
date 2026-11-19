#pragma once
#include <thread>

#include "PlayerManager.h"
#include "MonsterManager.h"
#include "QuestManager.h"
#include "UIManager.h"

class Overlay
{
	private:
	

		//classes
		//PlayerManager playerManager;
		QuestManager questManager;
		MonsterManager monsterManager;
		PlayerManager playerManager;
		UIManager UI;


		//structs
		Monsters monsters[3];
		Quest quest;
		Player players[4];

		//variables
		HWND hwnd;
		RECT rect;
		DWORD procID;
		HANDLE handle;
		DWORDLONG gamebaseadress;
		GLFWwindow* window;
		//bool allPlayersPresent = { false };
		int playerCount = { 0 };
		int oldPlayerCount = { 0 };
		int oldMonsterCount = { 0 };
		short oldMapID = { 0 };


		//methods
		void StatChangesThread();
		void SetWindowFlags();
		void HotKeyThread();

		//threads
		std::thread s_threadStatChanges;
		std::thread w_threadWindowHotKey;
		

	public:
		Overlay();
		~Overlay();

		void Init();
		void End();
		void Run();
		void UIThread();
};

