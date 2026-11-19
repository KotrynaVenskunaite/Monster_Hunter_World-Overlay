//#include "PointerFunctions.h"
//#include "DMC5FONT.h"
//#include "PlayerManager.h"
//#include "MonsterManager.h"
//#include "QuestManager.h"
//#include "UIManager.h"
//
//#include<iostream>
//#include<Windows.h>
//#include<vector>
//#include<map>
//#include<algorithm>
//#include <array>
//#include<chrono>
//#include <thread>
//
//#include "Imgui/imgui.h"
//#include "imgui/imgui_impl_opengl3.h"
//#include "imgui/imgui_impl_glfw.h"
//
//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
//
//using namespace std;
//
//
//struct Monster
//{
//    //Pointer offsets
//    vector<DWORDLONG> healthOffsets;
//    vector<DWORDLONG> maxHealthOffsets;
//    vector<DWORDLONG> idOffsets;
//
//    //Pointer adresses
//    atomic<DWORDLONG> healthAdress = { 0 };
//    atomic<DWORDLONG> idAdress = { 0 };
//    atomic<DWORDLONG> maxhealthAdress = { 0 };
//
//    //Variables
//    float health = { 0.0f };
//    float maxHealth = { 0.0f };
//    int id = { 0 };
//    int isMonsterOnMap = { 0 };
//};
//
////MAKE QUEST A STRUCT
//struct QuestMain
//{
//    //Pointer offsets
//    vector<DWORDLONG> questOffsets{ 0x38 };
//    vector<DWORDLONG> mapOffsets{ 0x80, 0xEEC0, 0x118 };
//    vector<DWORDLONG> selectedMonsterOffsets{ 0x70, 0x10, 0xD0, 0xCB0 };
//
//
//    //Pointer adresses
//    atomic<DWORDLONG> questAdress = { 0 };
//    atomic<DWORDLONG> mapAdress = { 0 };
//    atomic<DWORDLONG> selectedMonsterAdress = { 0 };
//
//    //Variables
//    int questStatus = 0;
//    int selectedMonster = -1;
//    short map = 0;
//};
//
//void SetSelectedMonster(int selectedMonsterID, int& selectedMonster, short map) {
//
//    switch (selectedMonsterID) {
//    case 0:
//        selectedMonster = 1;
//        break;
//    case 4:
//        selectedMonster = 1;
//        break;
//    case 16:
//        selectedMonster = 1;
//        break;
//    case 17:
//        selectedMonster = 2;
//        break;
//    case 18:
//        selectedMonster = 3;
//        break;
//    case 45:
//        selectedMonster = 1;
//        break;
//    case 46:
//        selectedMonster = 2;
//        break;
//    case 47:
//        selectedMonster = 3;
//        break;
//    case 57:
//        selectedMonster = 1;
//        break;
//    case 58:
//        selectedMonster = 2;
//        break;
//    case 59:
//        selectedMonster = 3;
//        break;
//    case 61:
//        selectedMonster = 1;
//        break;
//    case 62:
//        selectedMonster = 2;
//        break;
//    case 63:
//        if (map == 109) {
//            selectedMonster = 1;
//        }
//        else {
//            selectedMonster = 3;
//        }
//        break;
//    case 64:
//        selectedMonster = 2;
//        break;
//    case 65:
//        selectedMonster = 3;
//        break;
//    case 67:
//        selectedMonster = 1;
//        break;
//    case 68:
//        selectedMonster = 2;
//        break;
//    case 69:
//        selectedMonster = 3;
//        break;
//    case 80:
//        selectedMonster = 1;
//        break;
//    case 81:
//        selectedMonster = 2;
//        break;
//    case 82:
//        selectedMonster = 3;
//        break;
//    default:
//        selectedMonster = -1;
//        break;
//    }
//}
//
//void PointerAdressThread(HANDLE handle, DWORDLONG gamebaseadress, Monster(&monsters)[3], QuestMain(&quest))
//{
//    DWORDLONG baseHealthAdress = 0x5013C50;
//    DWORDLONG baseIdAdress = 0x04F9F9E0;
//
//    DWORD playerDataAdress = 0x500CDA0;
//    DWORD sessionQuestAdress = 0x500ED30;
//    DWORD selectedMonsterAdress = 0x051C4368;
//
//
//    //test if they need to be inside of while, to see if they reset on quest
//    quest.questAdress = GetPointerAddress(handle, gamebaseadress, sessionQuestAdress, quest.questOffsets);
//    quest.mapAdress = GetPointerAddress(handle, gamebaseadress, playerDataAdress, quest.mapOffsets);
//    quest.selectedMonsterAdress = GetPointerAddress(handle, gamebaseadress, selectedMonsterAdress, quest.selectedMonsterOffsets);
//
//    while (true) {
//        for (auto& monster : monsters) {
//            //std::cout<< std::hex << monster.healthOffsets[1] << endl;
//            monster.healthAdress = GetPointerAddress(handle, gamebaseadress, baseHealthAdress, monster.healthOffsets);
//            monster.maxhealthAdress = GetPointerAddress(handle, gamebaseadress, baseHealthAdress, monster.maxHealthOffsets);
//            monster.idAdress = GetPointerAddress(handle, gamebaseadress, baseIdAdress, monster.idOffsets);
//        }
//        this_thread::sleep_for(chrono::seconds(10));
//    }
//}
//
//void MonsterReadAdress(HANDLE handle, Monster(&monsters)[3], QuestMain(&quest), PlayerManager(&players_test)) {
//
//    while (true) {
//        DWORDLONG questAdress = quest.questAdress.load();
//        DWORDLONG mapAdress = quest.mapAdress.load();
//        DWORDLONG selectedMonsterAdress = quest.selectedMonsterAdress.load();
//
//        ReadProcessMemory(handle, (PBYTE*)questAdress, &quest.questStatus, sizeof(quest.questStatus), 0);
//        ReadProcessMemory(handle, (PBYTE*)mapAdress, &quest.map, sizeof(quest.map), 0);
//        ReadProcessMemory(handle, (PBYTE*)selectedMonsterAdress, &quest.selectedMonster, sizeof(quest.selectedMonster), 0);
//
//        //players_test.UpdatePlayer(handle);
//        //players_test.PlayerNames(handle);
//        //players.PlayerDamage(handle);
//        //cout << quest.selectedMonster << endl;
//        for (auto& monster : monsters) {
//            DWORDLONG healthAdress = monster.healthAdress.load();
//            DWORDLONG maxHealtAdress = monster.maxhealthAdress.load();
//            DWORDLONG idAdress = monster.idAdress.load();
//
//            if (ReadProcessMemory(handle, (PBYTE*)healthAdress, &monster.health, sizeof(monster.health), 0)) {
//                monster.isMonsterOnMap = true;
//                ReadProcessMemory(handle, (PBYTE*)healthAdress, &monster.health, sizeof(monster.health), 0);
//                ReadProcessMemory(handle, (PBYTE*)maxHealtAdress, &monster.maxHealth, sizeof(monster.maxHealth), 0);
//                ReadProcessMemory(handle, (PBYTE*)idAdress, &monster.id, sizeof(monster.id), 0);
//            }
//            else {
//                monster.isMonsterOnMap = false;
//            }
//        }
//        this_thread::sleep_for(chrono::milliseconds(200));
//    }
//}
//
//
//int main_old() {
//
//    //Process Init
//    HWND hwnd = FindWindowA(NULL, "MONSTER HUNTER: WORLD(421810)");
//    if (hwnd == NULL) {
//        cout << "Can't find window." << endl;
//        Sleep(3000);
//        exit(-1);
//    }
//
//    //Get Window Size
//    RECT rect;
//    int process_width = { 0 };
//    int process_height = { 0 };
//    int process_x = { 0 };
//    int process_y = { 0 };
//    if (GetWindowRect(hwnd, &rect))
//    {
//        process_x = rect.left;
//        process_y = rect.top;
//
//        process_width = rect.right - rect.left;
//        process_height = rect.bottom - rect.top;
//
//        cout << "Window dimensions are: " << process_width << " X " << process_height << endl;
//        cout << "Window position is: x= " << process_x << " y=  " << process_y << endl;
//    }
//    DWORD procID; //DWORDLONG
//    GetWindowThreadProcessId(hwnd, &procID);
//    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
//
//    if (procID == NULL) {
//        cout << "Can't obtain process." << endl;
//        Sleep(3000);
//        exit(-1);
//    }
//
//    //Helper my own
//    char gamemodule[] = "MonsterHunterWorld.exe";
//    DWORDLONG gamebaseadress = GetModuleBaseAdress_EMOKNG(procID, gamemodule);
//
//    QuestMain quest;
//    Monster monsters[3] =
//    {
//        {
//            { 0xE58, 0x7670, 0x64 },
//            { 0xE58, 0x7670, 0x60 },
//            { 0x118, 0x0, 0x68 }
//        },
//
//        {
//            { 0xEA8, 0x7670, 0x64 },
//            { 0xEA8, 0x7670, 0x60 },
//            { 0x118, 0x8, 0x68 }
//        },
//
//        {
//            { 0xEF8, 0x7670, 0x64 },
//            { 0xEF8, 0x7670, 0x60 },
//            { 0x118, 0x10, 0x68 }
//        }
//    };
//    /*DWORDLONG BASE_HEALTH_ADRESS = { 0x5013C50 };
//    float HHH = { 0.0f };
//    vector<DWORDLONG> monsterhealthoffsetstest = { 0xE58, 0x7670, 0x64 };
//    monsterhealthoffsetstest[0] = monsterhealthoffsetstest[0] + (1 * 0x50);
//    DWORDLONG temp_adress = GetPointerAddress(hwnd, gamebaseadress, BASE_HEALTH_ADRESS, monsterhealthoffsetstest);
//    ReadProcessMemory(handle, (PBYTE*)temp_adress, &HHH, sizeof(HHH), 0);
//    std::cout << HHH << endl;*/
//    //VARIABLES
//
//    int questStatus = 0;
//    int selectedMonster = -1;
//
//    short map = 0;
//    bool active = true;
//    string overlay = "";
//
//    //LOCALES
//            //MM            -   0
//            //ASTERA        -  301
//            //ASTERA HUB    -  302
//            //SHIP          -  303
//            //SELIANA       -  305
//            //SELIANA GH    -  306
//            //ROOM          -  501
//            //ROOM          -  502
//            //ROOM          -  503
//            //GH            -  505
//            //ROOM          -  506
//    const array<short, 11> hubMaps{ 0, 301, 302, 303, 305, 306, 501, 502, 503, 505, 506 };
//    float progress = 0.0f;
//    atomic<int> selectedMonsterIndex = -1;
//
//
//    // CLASS TEST INIT
//    PlayerManager players_test;
//    players_test.PlayerBaseInformation(handle, gamebaseadress);
//    players_test.UpdatePlayer(handle);
//
//    MonsterManager monsters_test;
//    monsters_test.MonsterBaseInformation(handle, gamebaseadress);
//    monsters_test.MonsterCurrentHealth(handle);
//    monsters_test.MonsterMaxHealth(handle);
//    monsters_test.MonsterID(handle);
//    Monsters monsterRef[3];
//    monsterRef[0] = monsters_test.GetMonster(0);
//    monsterRef[1] = monsters_test.GetMonster(1);
//    monsterRef[2] = monsters_test.GetMonster(2);
//    /*for (int i = 0; i < 3; i++) {
//        cout << monsterRef[i].name << endl;
//    }*/
//
//    QuestManager quest_test;
//    quest_test.QuestBaseInformation(handle, gamebaseadress);
//    quest_test.QuestMap(handle);
//    quest_test.QuestStatus(handle);
//    quest_test.SelectedMonster(handle);
//    //quest_test.SetSelectedMonster();
//    Quest questRef = quest_test.GetQuest();
//    cout << "Selected Monster from Method is: " << questRef.selectedMonster << endl;
//    // CLASS TEST INIT END
//
//    thread thrAdress(PointerAdressThread, handle, gamebaseadress, ref(monsters), ref(quest));
//    thread thrReadProcess(MonsterReadAdress, handle, ref(monsters), ref(quest), ref(players_test));
//
//
//    std::map<int, string> MonsterID = {
//        {0, "Anjanath"},
//        {1, "Rathalos"},
//        {4, "Zorah Magdaros"},
//        {7, "Great Jagras"},
//        {9, "Rathian"},
//        {10, "Pink Rathian"},
//        {11, "Azure Rathalos"},
//        {12, "Diablos"},
//        {13, "Black Diablos"},
//        {14, "Kirin"},
//        {15, "Behemoth"},
//        {16, "Kushala Daora"},
//        {17, "Lunastra"},
//        {18, "Teostra"},
//        {19, "Lavasioth"},
//        {20, "Deviljho"},
//        {21, "Barroth"},
//        {22, "Uragaan"},
//        {23, "Leshen"},
//        {24, "Pukei-Pukei"},
//        {25, "Nergigante"},
//        {26, "Xeno'jiiva"},
//        {27, "Kulu-Ya-Ku"},
//        {28, "Tzitzi-Ya-Ku"},
//        {29, "Jyuratodus"},
//        {30, "Tobi-Kadachi"},
//        {31, "Paolumu"},
//        {32, "Legiana"},
//        {33, "Great Girros"},
//        {34, "Odogaron"},
//        {35, "Radobaan"},
//        {36, "Vaal Hazak"},
//        {37, "Dodogama"},
//        {38, "Kulve Taroth"},
//        {39, "Bazelgeuse"},
//        {40, "Apceros"},
//        {41, "Kelbi"},
//        {42, "Kelbi"},
//        {51, "Ancient Leshen"},
//        {61, "Tigrex"},
//        {62, "Nargacuga"},
//        {63, "Barioth"},
//        {64, "Savage Deviljho"},
//        {65, "Brachydios"},
//        {66, "Glavenus"},
//        {67, "Acidic Glavenus"},
//        {68, "Fulgur Anjanath"},
//        {69, "Coral Pukei-Pukei"},
//        {70, "Ruiner Nergigante"},
//        {71, "Viper Tobi-Kadachi"},
//        {72, "Nightshade Paolumu"},
//        {73, "Shrieking Legiana"},
//        {74, "Ebony Odogaron"},
//        {75, "Blackveil Vaal Hazak"},
//        {76, "Seething Bazelgeuse"},
//        {77, "Beotodus"},
//        {78, "Banbaro"},
//        {79, "Velkhana"},
//        {80, "Namielle"},
//        {81, "Shara Ishvalda"},
//        {87, "Alatreon"},
//        {88, "Gold Rathian"},
//        {89, "Silver Rathalos"},
//        {90, "Yian Garuga"},
//        {91, "Rajang"},
//        {92, "Furious Rajang"},
//        {93, "Brute Tigrex"},
//        {94, "Zinogre"},
//        {95, "Stygian Zinogre"},
//        {96, "Raging Brachydios"},
//        {97, "Safi'jiiva"},
//        {99, "Scarred Yian Garuga"},
//        {100, "Frostfang Barioth"},
//        {101, "Fatalis"}
//    };
//
//    //GLFW init
//    glfwInit();
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
//
//    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
//
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
//    glfwWindowHint(GLFW_DECORATED, GL_FALSE);//Top bar of a window, can delete
//
//    GLFWwindow* window = glfwCreateWindow(process_width - 16, process_height - 39, "Health overlay", NULL, NULL);//full window or windowed, window sharing (always null)
//    glfwSetWindowPos(window, process_x + 8, process_y + 31);
//
//    if (!window) {
//        cout << "Fail! Window couldn't get created! \n";
//        glfwDestroyWindow(0);
//        return 0;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    //Vsync
//    glfwSwapInterval(1);
//
//    gladLoadGL();
//
//    glViewport(0, 0, process_width - 16, process_height - 39);
//
//    //INIT ImGUI
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 330");
//
//    //Load Font
//    ImFontConfig font_cfg;
//    font_cfg.FontDataOwnedByAtlas = false;
//
//    io.Fonts->AddFontFromMemoryTTF(DMC5Font, DMC5FontSize, 24.0f, &font_cfg);
//
//    /*PlayerManager players(hwnd, gamebaseadress);
//    players.PlayerNames(handle);*/
//    //DWORDLONG partyBaseAddress = { 0x04F9F9E0 };
//    //vector<DWORDLONG> partyOffsets{ 0x118, 0x0 };
//
//    //// This already does ALL the dereferencing
//    //DWORDLONG damageArrayBase = GetPointerAddress(hwnd, gamebaseadress, partyBaseAddress, partyOffsets);
//    //DWORDLONG damageADress2 = { 0 };
//    //// Now add the index offset to get to the specific player
//    //DWORDLONG playerDamageAddress = damageArrayBase + (1 * 0x8);
//
//    //// Read the damage directly (no more dereferencing!)
//    //int damage = 0;
//    //ReadProcessMemory(handle, (PBYTE*)(damageArrayBase), &damageADress2, sizeof(damageADress2), 0);
//    //ReadProcessMemory(handle, (PBYTE*)(damageADress2 + 0x68), &damage, sizeof(damage), 0);
//    //std::cout << "moster ID in MAIN: " << std::dec << damage << std::endl;
//
//
//
//    //players.PlayerNames(handle);
//
//    ImGuiWindowFlags window_flags = 0;
//    window_flags |= ImGuiWindowFlags_NoBackground;
//    window_flags |= ImGuiWindowFlags_NoTitleBar;
//    window_flags |= ImGuiWindowFlags_NoInputs;
//    window_flags |= ImGuiWindowFlags_NoResize;
//
//    UIManager UI;
//
//    while (!glfwWindowShouldClose(window)) {
//
//        //players.UpdatePlayer(handle);
//
//        //glClearColor(0.5f, 0.2f, 0.1f, 1.0f);
//
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //Imgui must be after OpenGL
//        //ImGui_ImplOpenGL3_NewFrame();
//        //ImGui_ImplGlfw_NewFrame();
//        //ImGui::NewFrame();
//        //
//
//        //
//        //ImGui::Begin("Monster Health", 0, window_flags);
//        //if (questRef.isHubMap == false) {
//        //    //selectedMonsterIndex = quest.selectedMonster.load();
//        //    //SetSelectedMonster(quest.selectedMonster, selectedMonster, quest.map);
//        //    for (int i = 0; i < 3; i++)
//        //    {
//        //        //auto& monster = monsters[i];
//        //        //DWORDLONG healthAdress = monster.healthAdress.load();
//        //        if (monsterRef[i].isMonsterOnMap == true && questRef.questStatus != 1) {
//        //            if (i + 1 == questRef.selectedMonster) {
//        //                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(57, 169, 0, 255)); // Green
//        //            }else{
//        //                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(57, 169, 222, 255)); // Green
//        //            }
//        //            
//        //            progress = monsterRef[i].health / monsterRef[i].maxHealth;
//        //            overlay = format("{:.0f} / {:.0f} {:.0f}%", monsterRef[i].health, monsterRef[i].maxHealth, progress * 100);
//        //            ImGui::Text("%s", monsterRef[i].name.c_str());
//        //            ImGui::ProgressBar(progress, ImVec2(200, 20), overlay.c_str());
//        //            ImGui::PopStyleColor();
//        //        }
//        //    }
//        //}
//
//
//        /*ImGui::Checkbox("EZPZ", &active);
//
//        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
//
//        ImVec2 p1 = ImVec2(200, 300);
//        ImVec2 p2 = ImVec2(300, 400);
//        draw_list->AddLine(p1, p2, IM_COL32(255, 0, 0, 255), 10.0f);*/
//
//        /* ImGui::End();
//
//
//         ImGui::Render();
//
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//         glfwSwapBuffers(window);
//
//         glfwPollEvents();*/
//
//         //------------------------------------------------------------------
//         /// NEW TEST CLASS STUFF//
//         //------------------------------------------------------------------
//
//        UI.Begin(monsterRef, questRef);
//        UI.Render(window);
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
//        //OTHER STUFF
//
//    }
//    thrAdress.join();
//    thrReadProcess.join();
//
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}