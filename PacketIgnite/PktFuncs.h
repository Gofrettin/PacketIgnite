#pragma once

void SpawnItem(void* ptr, DWORD idplayer, DWORD itemid, DWORD itemnum, long long awake = 0);
void SendQueryAddCoupleExperience(void* ptr, DWORD idplayer, int exp);
void SendChangeBankPass(void* ptr, const char* szName, const char *szNewPass, unsigned long uidPlayer);
void SendDecouple(void* ptr, unsigned long idPlayer);
void SendQuerySetPlayerName(void* ptr, unsigned long idPlayer, const char* lpszPlayer, DWORD dwData);
void SendTest(void* ptr);
void SendQueryGetSealCharConm(void* ptr, DWORD idReceiver);