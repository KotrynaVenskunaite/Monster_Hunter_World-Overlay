#pragma once
#include<Windows.h>
#include "Monster.h"
#include "Player.h"
#include "Quest.h"
#include "Imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class UIManager
{
	private:
		ImGuiWindowFlags window_flags = { 0 };
		void newFrame();
		
		void DrawMonsterHealthbar(float health, float maxHealth, std::string name);
		void DrawPlayers(int damage, float damageProc, std::string name);
	public:
		UIManager();
		~UIManager();

		void WindowFlags();
		void ToggleWindowFlags();
		void Begin(Monsters(&monsters)[3], Player(&players)[4], int playerCount, Quest& quest);
		void Players(Player(&players)[4], int playerCount, Quest& quest);
		void Render(GLFWwindow* window);
};

