#include "Overlay.h"
#include "PointerFunctions.h"
#include "DMC5FONT.h"

#include "PlayerManager.h"
#include "MonsterManager.h"
#include "QuestManager.h"
#include "UIManager.h"

#include<iostream>
#include<Windows.h>
#include<chrono>
#include<thread>
#include <atomic>

#include "Imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


Overlay::Overlay()
{
}

Overlay::~Overlay()
{
}

void Overlay::Init()
{
	hwnd = FindWindowA(NULL, "MONSTER HUNTER: WORLD(421810)");
    if (hwnd == NULL) {
        std::cout << "Can't find window." << std::endl;
        Sleep(3000);
        exit(-1);
    }

    //Get Window Size
    int process_width = { 0 };
    int process_height = { 0 };
    int process_x = { 0 };
    int process_y = { 0 };
    if (GetWindowRect(hwnd, &rect))
    {
        process_x = rect.left;
        process_y = rect.top;

        process_width = rect.right - rect.left;
        process_height = rect.bottom - rect.top;

        std::cout << "Window dimensions are: " << process_width << " X " << process_height << std::endl;
        std::cout << "Window position is: x= " << process_x << " y=  " << process_y << std::endl;
    }
    
    GetWindowThreadProcessId(hwnd, &procID);
    handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    if (procID == NULL) {
        std::cout << "Can't obtain process." << std::endl;
        Sleep(3000);
        exit(-1);
    }

    char gamemodule[] = "MonsterHunterWorld.exe";
    gamebaseadress = GetModuleBaseAdress_EMOKNG(procID, gamemodule);

    //GLFW init
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);//Top bar of a window, can delete

    window = glfwCreateWindow(process_width - 16, process_height - 39, "Health overlay", NULL, NULL);//full window or windowed, window sharing (always null)
    glfwSetWindowPos(window, process_x + 8, process_y + 31);

    if (!window) {
        std::cout << "Fail! Window couldn't get created! \n";
        glfwDestroyWindow(0);
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    //Vsync
    glfwSwapInterval(1);

    gladLoadGL();

    glViewport(0, 0, process_width - 16, process_height - 39);

    //INIT ImGUI

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //Load Font
    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF(DMC5Font, DMC5FontSize, 24.0f, &font_cfg);

    //get quest adress
    questManager.QuestBaseInformation(handle, gamebaseadress);
    monsterManager.MonsterBaseInformation(handle, gamebaseadress);
    playerManager.PlayerBaseInformation(handle, gamebaseadress);
    playerManager.PlayerCount(handle);

    UI.WindowFlags();
    
    //questManager.MonsterCount(handle);
    std::cout << "init done" << std::endl;
}

void Overlay::End()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();



    glfwDestroyWindow(window);
    glfwTerminate();
}

void Overlay::Run()
{
    s_threadStatChanges = std::thread(&Overlay::StatChangesThread, this);
    w_threadWindowHotKey = std::thread(&Overlay::HotKeyThread, this);
    UIThread();
    
    
    
    s_threadStatChanges.join();
    End();
    std::cout << "exec ended" << std::endl;
}

void Overlay::SetWindowFlags()
{

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        int currentState = glfwGetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH);

        // Toggle the value
        glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, !currentState);
    }
}


void Overlay::UIThread()
{
    while(!glfwWindowShouldClose(window))
    {
        UI.Begin(monsters, players, playerCount, quest);
        UI.Render(window);

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    
}

void Overlay::StatChangesThread()
{
    while (true)
    {
        
        if (quest.isHubMap == false) {
            questManager.MonsterCount(handle);
            playerCount = playerManager.PlayerCount(handle);

            //QUEST INFO
            //if (oldMapID != quest.map) {
            //    oldMapID = quest.map;
            //    questManager.QuestStatus(handle);//might not be needed aanymore, change with HUB MAP
            //}
            questManager.SelectedMonster(handle);
            //MONSTER INFO
            //if monster count changes, re-read monster info and pdate pointer chains
            if (oldMonsterCount != quest.monsterCount) {
                oldMonsterCount = quest.monsterCount;
                monsterManager.MonsterBaseInformation(handle, gamebaseadress);
                monsterManager.MonsterMaxHealth(handle); //max health never changes, so it needs to be read only once
                monsterManager.MonsterID(handle); //same as max health, never changes
            }
            monsterManager.MonsterCurrentHealth(handle);
            

            //PLAYER INFO
            //if the player count changes, re-read all player data.
            if (oldPlayerCount != playerCount) {
                oldPlayerCount = playerCount;
                playerManager.PlayerNames(handle);
                playerManager.PlayerHRLv(handle);
                playerManager.PlayerMRLv(handle);
            }
            playerManager.PlayerDamage(handle);
            playerManager.PlayerDamageProc(handle);


            //GET ALL VALUES
            
            for (int i = 0; i < quest.monsterCount; i++) {
                monsters[i] = monsterManager.GetMonster(i);

            }
            for (int i = 0; i < playerCount; i++) {
                players[i] = playerManager.GetPlayer(i);
            }
        }
        questManager.QuestMap(handle);
        quest = questManager.GetQuest();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

void Overlay::HotKeyThread()
{
    // hotkey
    RegisterHotKey(NULL, 1, MOD_CONTROL | 0x4000, VK_F1);
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
            if (msg.message == WM_HOTKEY) {
                if (msg.wParam == 1)  // Your hotkey ID
                {
                    //std::cout << "Pressed ctrl + 1" << std::endl;
                    int currentState = glfwGetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH);
                    UI.ToggleWindowFlags();
                    glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, !currentState);
                }
            }
        }
    }
   
}