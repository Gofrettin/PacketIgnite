#include "stdafx.h"

int ItemId;
int ItemNum;
int PlayerId;
int PlayerIdCouple;
int ExpAmount;
int DST1, Value1;
int DST2, Value2;
int DST3, Value3;

void TW_CALL GetMenuTargetId(void *value, void *clientData)
{
	g_pPlayer = *(pPlayer**)((reinterpret_cast<DWORD>(GetModuleHandle(nullptr)) + 0x95EA04));
	*(int*)value = g_pPlayer->GetTargetId();
}

void TW_CALL GetMenuTargetHP(void *value, void *clientData)
{
	g_pPlayer = *(pPlayer**)((reinterpret_cast<DWORD>(GetModuleHandle(nullptr)) + 0x95EA04));
	*(int*)value = g_pPlayer->GetTargetHP();
}

void TW_CALL GetMenuId(void *value, void *clientData)
{
	g_pPlayer = *(pPlayer**)((reinterpret_cast<DWORD>(GetModuleHandle(nullptr)) + 0x95EA04));
	*(int*)value = g_pPlayer->GetId();
}

void TW_CALL SetMaxDCT(void *clientData)
{
	g_pPlayer = *(pPlayer**)((reinterpret_cast<DWORD>(GetModuleHandle(nullptr)) + 0x95EA04));
	*(float*)(g_pPlayer + 0x1158) = 1000000.0f;
}

void InitMenu()
{
	RECT m_rectNeuz;

	TwInit(TW_DIRECT3D9, g_pD3DApplication->GetD3DDevice());

	GetClientRect(FindWindowA(nullptr, "Fly For Fun (Classic)"), &m_rectNeuz);
	TwWindowSize(m_rectNeuz.right, m_rectNeuz.bottom);

	TwBar *myBar;
	myBar = TwNewBar("qHook");

	TwAddVarRW(myBar, "ItemId", TW_TYPE_INT32, &ItemId, "group='Item Creation' label='ID' ");
	TwAddVarRW(myBar, "ItemNum", TW_TYPE_INT32, &ItemNum, "group='Item Creation' label='Num' ");

	/*TwAddSeparator(myBar, NULL, "group='Item Creation' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &DST1, "group='Item Creation' label='DST' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &Value1, "group='Item Creation' label='Value' ");

	TwAddSeparator(myBar, NULL, "group='Item Creation' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &DST2, "group='Item Creation' label='DST' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &Value2, "group='Item Creation' label='Value' ");

	TwAddSeparator(myBar, NULL, "group='Item Creation' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &DST3, "group='Item Creation' label='DST' ");
	TwAddVarRW(myBar, NULL, TW_TYPE_INT32, &Value3, "group='Item Creation' label='Value' ");

	TwAddSeparator(myBar, NULL, "group='Item Creation' ");*/

	TwAddVarRW(myBar, "PlayerId", TW_TYPE_INT32, &PlayerId, "group='Item Creation' label='Player Id' ");
	TwAddButton(myBar, "SpawnItem", RunCB, NULL, "group='Item Creation' label='Spawn' ");
	TwAddVarCB(myBar, "MyId", TW_TYPE_UINT32, 0, GetMenuId, 0, "group='Item Creation' label='My ID' ");

	TwAddVarCB(myBar, "TargetId", TW_TYPE_UINT32, 0, GetMenuTargetId, 0, "group='Target Info' label='ID' ");
	TwAddVarCB(myBar, "TargetHP", TW_TYPE_UINT32, 0, GetMenuTargetHP, 0, "group='Target Info' label='HP' ");

	TwAddVarRW(myBar, "PlayerIdCouple", TW_TYPE_INT32, &PlayerIdCouple, "group='Couple' label='Player Id' ");
	TwAddVarRW(myBar, "ExpAmount", TW_TYPE_INT32, &ExpAmount, "group='Couple' label='XP Amount' ");
	TwAddButton(myBar, "AddEXP", RunCB2, NULL, "group='Couple' label='Add XP' ");

	TwAddButton(myBar, "DCT", SetMaxDCT, NULL, "group='Misc' label='DCT Hack' ");
	TwAddVarRW(myBar, "SwitchEQ", TW_TYPE_BOOLCPP, &EnableEQ, "group='Misc' label='Enable Switch' ");
}

void CraftAwake(__int64* pnRandomOptItemId, int nDst, int nAdj, int slot)
{
	__int64 nRandomOptionItemId = nDst;
	nRandomOptionItemId = nRandomOptionItemId << 10;

	if (nAdj < 0)
	{
		nRandomOptionItemId |= 0x0200;
		nRandomOptionItemId = nRandomOptionItemId | (-nAdj);
	}
	else
		nRandomOptionItemId = nRandomOptionItemId | nAdj;

	nRandomOptionItemId = nRandomOptionItemId << (8 + 18 * slot);
	*pnRandomOptItemId |= nRandomOptionItemId;
}

void TW_CALL RunCB(void * /*clientData*/)
{
	if (!Connected)
	{
		printf("Not Connected !\n");
	}

	if (ItemNum > 0 && ItemId > 0)
	{
		/*__int64		m_iRandomOptItemId;

		CraftAwake(&m_iRandomOptItemId, DST1, Value1, 0);
		CraftAwake(&m_iRandomOptItemId, DST2, Value2, 1);
		CraftAwake(&m_iRandomOptItemId, DST3, Value3, 2);*/

		g_pPlayer = *(pPlayer**)((reinterpret_cast<DWORD>(GetModuleHandle(nullptr)) + 0x95EA04));

		if(!PlayerId)
			PlayerId = g_pPlayer->GetId();

		if (PlayerId)
			SpawnItem(DbNet, PlayerId, ItemId, ItemNum, 0);
	}
		
}

void TW_CALL RunCB2(void * /*clientData*/)
{
	if (!Connected)
	{
		printf("Not Connected !\n");
	}

	if (ExpAmount > 0 && PlayerIdCouple > 0)
		SendQueryAddCoupleExperience(DbNet, PlayerIdCouple, ExpAmount);
}