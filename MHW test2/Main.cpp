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

#include "Overlay.h"



int main() {

    Overlay overlay;
    overlay.Init();
    overlay.Run();


    //!glfwWindowShouldClose(window)
   /* while (true){
        overlay.UIThread();
    }
    overlay.End();*/
    return 0;
}