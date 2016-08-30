#ifndef _HUD_H
#define _HUD_H

#include "game.h"

void renderHUD(SGameChar *g_sChar, Console *g_Console);
void SelectedEnemyHP(unsigned int iHP);
void eRenderHP(Console *g_Console);

#endif // !_HUD_H