#ifndef _CHECK_ATTACK_H
#define _CHECK_ATTACK_H

#include "game.h"

void setAttack(int directions, SGameChar *g_sChar);
void launchEnemyAttack(SGameChar *g_sChar, SGameChar *sEnemy, double *g_dElapsedTime);
void eCheckForDamage(Console *g_Console, SGameChar *g_sEnemy, SGameChar *g_sChar, double *g_dElapsedTime);
void cCheckForDamage(SGameChar *g_sChar, SGameChar g_sEnemy);
unsigned int checkAtkType(COORD cAtkLctn);
void launchPlayerAttack(Console *g_Console, SGameChar *g_sChar, double *g_dElapsedTime, bool *bSomethingHappened, MAPDATA(&MapData)[height][width]);
void eCheckForDamage(Console *g_Console, SGameChar *g_sEnemy, SGameChar *g_sChar, double *g_dElapsedTime);
unsigned int checkAtkType(COORD cAtkLctn, MAPDATA(&MapData)[height][width]);
void playAttackSound(unsigned int iAtkType);
void renderExplosion(Console *g_Console, short cX, short cY);
bool CheckAroundSelf(COORD cTarget, COORD cSelf);

#endif // !_CHECK_ATTACK_H
