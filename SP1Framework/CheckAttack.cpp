#include "game.h"

double ntt = 0.0;

void checkUp( SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened)
{
	g_sChar -> m_cAttackLocation = { g_sChar -> m_cLocation.X, g_sChar -> m_cLocation.Y - 1 };
	ntt = *g_dElapsedTime + g_sChar->m_dAttackRate;
	*g_dCharNextAttackTime = ntt;
	g_sChar -> m_bCanAttack = false;
	g_sChar -> m_bAttacking = true;
	*bSomethingHappened = true;
	PlaySound(TEXT("SwordAttack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void checkLeft(SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened)
{
	g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X - 1, g_sChar->m_cLocation.Y };
	ntt = *g_dElapsedTime + g_sChar->m_dAttackRate;
	*g_dCharNextAttackTime = ntt;
	g_sChar->m_bCanAttack = false;
	g_sChar->m_bAttacking = true;
	*bSomethingHappened = true;
	PlaySound(TEXT("SwordAttack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void checkDown(SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened)
{
	g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X, g_sChar->m_cLocation.Y + 1 };
	ntt = *g_dElapsedTime + g_sChar->m_dAttackRate;
	*g_dCharNextAttackTime = ntt;
	g_sChar->m_bCanAttack = false;
	g_sChar->m_bAttacking = true;
	*bSomethingHappened = true;
	PlaySound(TEXT("SwordAttack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void checkRight(SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened)
{
	g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X + 1, g_sChar->m_cLocation.Y };
	ntt = *g_dElapsedTime + g_sChar->m_dAttackRate;
	*g_dCharNextAttackTime = ntt;
	g_sChar->m_bCanAttack = false;
	g_sChar->m_bAttacking = true;
	*bSomethingHappened = true;
	PlaySound(TEXT("SwordAttack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}