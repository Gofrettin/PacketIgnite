// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <AntTweakBar.h>
#include "stdio.h"
#include "detours.h"
#include "HeapMng.h"
#include "ar.h"
#include "Structs.h"
#include "Menu.h"
#include "PktFuncs.h"

#pragma comment (lib, "detours.lib")

extern void* DbNet;
extern void* ClientNet;
extern bool Connected;
extern bool EnableEQ;

void AllocateConsole();
void PlaceHooks();
void InitMenu();
void DoingTheStuff();
DWORD WINAPI SwitchEQ();

// TODO: reference additional headers your program requires here
