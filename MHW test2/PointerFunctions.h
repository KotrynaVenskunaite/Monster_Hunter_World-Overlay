#pragma once

#include<Windows.h>
#include<vector>

DWORDLONG GetPointerAddress(HANDLE handle, DWORDLONG gameBaseAddr, DWORDLONG address, std::vector<DWORDLONG> offsets);
DWORDLONG GetModuleBaseAdress_EMOKNG(DWORD pID, char* moduleName);