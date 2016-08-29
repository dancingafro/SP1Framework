#ifndef _CHECK_ATTACK_H
#define _CHECK_ATTACK_H

#include "game.h"

void setAttackUp(SGameChar *g_sChar);
void setAttackLeft(SGameChar *g_sChar);
void setAttackDown(SGameChar *g_sChar);
void setAttackRight(SGameChar *g_sChar);
void launchPlayerAttack(Console *g_Console, SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened);
void eCheckForDamage(Console *g_Console, SGameChar *g_sEnemy, SGameChar *g_sChar, double *g_dElapsedTime);
unsigned int checkAtkType(COORD cAtkLctn);
void playAttackSound(unsigned int iAtkType);
void renderExplosion(Console *g_Console, short cX, short cY);

#endif // !_CHECK_ATTACK_H
