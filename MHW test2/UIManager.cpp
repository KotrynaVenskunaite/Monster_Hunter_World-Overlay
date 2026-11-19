#include "UIManager.h"
#include<iostream>
#include<string>


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::newFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Imgui must be after OpenGL
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIManager::WindowFlags()
{
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoInputs;
    window_flags |= ImGuiWindowFlags_NoResize;
}

void UIManager::ToggleWindowFlags()
{
    window_flags ^= ImGuiWindowFlags_NoBackground;
    window_flags ^= ImGuiWindowFlags_NoTitleBar;
    window_flags ^= ImGuiWindowFlags_NoInputs;
    window_flags ^= ImGuiWindowFlags_NoResize;
}

void UIManager::Render(GLFWwindow* window)
{
    

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    glfwPollEvents();

    //std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

void UIManager::DrawMonsterHealthbar(float health, float maxHealth, std::string name)
{
    float progress = health / maxHealth;
    std::string overlay = std::format("{:.0f} / {:.0f} {:.0f}%", health, maxHealth, progress * 100);
    ImGui::Text("%s", name.c_str());
    ImGui::ProgressBar(progress, ImVec2(200, 20), overlay.c_str());
    ImGui::PopStyleColor();
}

void UIManager::DrawPlayers(int damage, float damageProc, std::string name)
{
    //std::string overlay = std::format("{:.0f} {:.0f}%", players[0].damage, players[0].damageProc);
    
    if ( isnan(damageProc) == true) {
        damageProc = 0;
    }
    //std::cout << damageProc << std::endl;
    std::string PlayerOverlay = std::format("{} ({:.0f}%)", damage, damageProc * 100);
    //std::cout << "player name " << name << std::endl;
    ImGui::Text("%s", name.c_str());
    ImGui::ProgressBar(damageProc, ImVec2(200, 20), PlayerOverlay.c_str());
    //ImGui::PopStyleColor();
}

void UIManager::Begin(Monsters(&monsters)[3], Player(&players)[4], int playerCount, Quest& quest)
{

    //WindowFlags(); //remove, this only needs to execute once
    newFrame();
    ImGui::SetWindowSize(ImVec2(230, 210), 0);
    ImGui::Begin("Monster Health", 0, window_flags);

    //maby add quest.isHubMap == false check
    for (int i = 0; i < quest.monsterCount; i++) {
        if (quest.selectedMonster == i+1) {
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(57, 169, 0, 255)); // Green
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(57, 169, 222, 255)); // BLue
        }
        //ImGui::SetCursorPos(ImVec2(400, 100));
        DrawMonsterHealthbar(monsters[i].health, monsters[i].maxHealth, monsters[i].name);
    }

    //std::cout << "window size X: " << ImGui::GetWindowSize().x << " window size Y: " << ImGui::GetWindowSize().y << std::endl;
   
    ImGui::End();
    //std::cout << "player Count: " << playerCount << std::endl;
    ImGui::Begin("Player Info", 0, window_flags);
    for (int i = 0; i < playerCount; i++)
    {
        DrawPlayers(players[i].damage, players[i].damageProc, players[i].name);
    }
    ImGui::End();
}

void UIManager::Players(Player(&players)[4], int playerCount, Quest& quest)
{
    WindowFlags(); //remove, this only needs to execute once
    newFrame();
    //std::cout << "player Count: " << playerCount << std::endl;
    ImGui::Begin("Player Info", 0, window_flags);
    for (int i = 0; i < playerCount; i++)
    {
        DrawPlayers(players[i].damage, players[i].damageProc, players[i].name);
    }
}