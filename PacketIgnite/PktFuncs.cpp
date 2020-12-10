#include "stdafx.h"

Send_t Send;

void SpawnItem(void* ptr, DWORD idplayer, DWORD itemid, DWORD itemnum, long long awake)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0x0000001a;

	ar << idplayer << 0;
	ar << (BYTE)1;

	ar << DWORD(0) << (DWORD)itemid;
	ar << DWORD(0);
	ar.WriteString((""));

	ar << short(itemnum);
	ar << (BYTE)0 << 0;
	ar << 0;
	ar << (BYTE)0;
	ar << 0;
	ar << (DWORD)0;
	ar << (BYTE)0;
	ar << 0;
	ar << 0;

	ar << 0;
	ar << 0;
	ar << 0;

	ar << (BOOL)0;
	ar << awake;
	ar << DWORD(0); //keeptime

	//ar << (BYTE)0x00; //Pet
	ar << (BYTE)0x01; //m_pPet
	ar << (BYTE)6;
	ar << (BYTE)2;
	ar << (DWORD)1;
	ar << (WORD)1;
	ar << (WORD)14;
	ar << (BYTE)1 << (BYTE)3 << (BYTE)5 << (BYTE)7 << (BYTE)9;
	ar.WriteString(LPCTSTR(""));

	ar << (BOOL)0; //m_bTranformVisPet
	ar << (DWORD)0xffffffff;

	ar << 0;
	ar.WriteString((""));
	ar.WriteString((""));

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}

void SendQueryAddCoupleExperience(void* ptr, DWORD idplayer, int exp)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0x8FFFF006;

	ar << idplayer << exp;

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}

void SendDecouple(void* ptr, unsigned long idPlayer)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0x8FFFF003;

	ar << idPlayer;

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}

void SendChangeBankPass(void* ptr, const char* szName, const char *szNewPass, unsigned long uidPlayer)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0xffffff47;

	ar.WriteString(szName);
	ar.WriteString(szNewPass);
	ar << uidPlayer;

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}

void SendQuerySetPlayerName(void* ptr, unsigned long idPlayer, const char* lpszPlayer, DWORD dwData)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0x00000012;

	ar << idPlayer;
	ar.WriteString(lpszPlayer);
	ar << dwData;

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}


void SendTest(void* ptr)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0x00ff0000;

	ar.WriteString("/say Uno ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 4);
}

void SendQueryGetSealCharConm(void* ptr, DWORD idReceiver)
{
	CAr ar;
	int nBufSize;
	ar << 0xFFFFFFFF << 0xFFFFFFFF << 0xf000f812;

	ar << idReceiver << (DWORD)1;

	LPBYTE lpBuf = ar.GetBuffer(&nBufSize);
	Send(ptr, (LPVOID)lpBuf, nBufSize, 1);
}



