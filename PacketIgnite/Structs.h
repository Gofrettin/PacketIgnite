#pragma once

class CD3DApplication
{
public:
	LPDIRECT3DDEVICE9 * GetD3DDevice()
	{
		return *(LPDIRECT3DDEVICE9**)(this + 0x1D8);
	}
};
extern CD3DApplication * g_pD3DApplication;

class pPlayer
{
public:
	int GetTargetId()
	{
		if (this == nullptr)
			return 0;

		auto pWorld = *(DWORD*)(this + 0x16C);
		if (!pWorld)
			return 0;

		auto pFocusObj = *(DWORD*)(pWorld + 0x20);
		if (!pFocusObj)
			return 0;

		return *(DWORD*)(pFocusObj + 0x33C);
	}

	int GetTargetHP()
	{
		if (this == nullptr)
			return 0;

		auto pWorld = *(DWORD*)(this + 0x16C);
		if (!pWorld)
			return 0;

		auto pFocusObj = *(DWORD*)(pWorld + 0x20);
		if (!pFocusObj)
			return 0;

		return *(DWORD*)(pFocusObj + 0x6B8);
	}

	int GetId()
	{
		if (this == nullptr)
			return 0;

		return *(DWORD*)(this + 0x33C);
	}
};
extern pPlayer* g_pPlayer;

typedef BOOL(__thiscall * ConnectToServer_t)(void* This, LPCSTR lpConnection, unsigned short uPort, BOOL bSingleThreaded, DWORD dwcrc, unsigned long uWaitingTime);
extern ConnectToServer_t ConnectToServer;

typedef BOOL(__thiscall * Send_t)(void* This, LPVOID lpData, DWORD dwDataSize, DWORD dpidTo);
extern Send_t Send;