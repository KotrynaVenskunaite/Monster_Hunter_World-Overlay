#include "PointerFunctions.h"

#include<iostream>
#include<Windows.h>
#include<TlHelp32.h>
#include<tchar.h>
#include<vector>
#include<stdlib.h>

using namespace std;

DWORDLONG GetPointerAddress(HANDLE handle, DWORDLONG gameBaseAddr, DWORDLONG address, vector<DWORDLONG> offsets)
{
    //DWORD pID = NULL; // Game process ID
    //GetWindowThreadProcessId(hwnd, &pID);
    //HANDLE phandle = NULL;
    //phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    //if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    DWORDLONG offset_null = NULL;
    ReadProcessMemory(handle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORDLONG pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(handle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}

DWORDLONG GetModuleBaseAdress_EMOKNG(DWORD pID, char* moduleName) {
    HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
    DWORDLONG ModuleBaseAdress = 0;

    if (Snapshot != INVALID_HANDLE_VALUE) {
        if (Module32First(Snapshot, &ModuleEntry32)) {
            do {
                if (_tcscmp(ModuleEntry32.szModule, moduleName) == 0) {
                    ModuleBaseAdress = (DWORDLONG)ModuleEntry32.modBaseAddr;
                    cout << "have adress" << endl;
                    break;
                }
            } while (Module32Next(Snapshot, &ModuleEntry32));
        }

    }
    else {
        cout << "invalid handle value" << endl;
    }
    CloseHandle(Snapshot);
    return ModuleBaseAdress;
}