#ifndef _LOADING_H
#define _LOADING_H

#include"game.h"

extern char map[height][width];
extern char fog[height][width];
extern int numTele;
extern SGameObj g_sKey;
extern SGameObj g_sDoor[2];
extern SGameObj g_sTeleporters[totalTele];
extern SGameChar g_sEnemy[numEnemy];

#endif