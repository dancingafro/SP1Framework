#include "game.h"
#include "CheckAttack.h"
#include "HUD.h"

double ntt = 0.0;
bool bEnemyIsHit;
unsigned int iAtkType;

void setAttack(int directions, SGameChar *g_sChar )
{
	switch (directions)
	{
	case 1:
		g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X, g_sChar->m_cLocation.Y - 1 };
		break;
	case 2:
		g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X, g_sChar->m_cLocation.Y + 1 };
		break;
	case 3:
		g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X - 1, g_sChar->m_cLocation.Y };
		break;
	case 4:
		g_sChar->m_cAttackLocation = { g_sChar->m_cLocation.X + 1, g_sChar->m_cLocation.Y };
		break;
	default:
		break;
	}
}


void launchPlayerAttack(Console *g_Console, SGameChar *g_sChar, double *g_dElapsedTime, bool *bSomethingHappened )
{
	COORD cAtkLctn = g_sChar->m_cAttackLocation;
	ntt = *g_dElapsedTime + g_sChar->m_dAttackRate;
	g_sChar->m_dNextAttackTime = ntt;
	g_sChar->m_bCanAttack = false;
	g_sChar->m_bAttacking = true;
	g_sChar->m_cAttackRenderLocation = g_sChar->m_cAttackLocation;
	g_sChar->m_dAttackRenderTime = *g_dElapsedTime + 0.5;
	*bSomethingHappened = true;
	iAtkType = checkAtkType( cAtkLctn);
	playAttackSound(iAtkType);
}

void launchEnemyAttack(SGameChar *g_sChar, SGameChar *g_sEnemy, double *g_dElapsedTime)
{
	g_sEnemy->m_cAttackLocation = g_sChar->m_cLocation;
	g_sEnemy->m_dNextAttackTime = *g_dElapsedTime + g_sEnemy->m_dAttackRate;
	cCheckForDamage(g_sChar, *g_sEnemy);
}

void eCheckForDamage( Console *g_Console, SGameChar *g_sEnemy, SGameChar *g_sChar, double *g_dElapsedTime )
{
	if (g_sEnemy->m_bActive && PositionCollision(g_sEnemy->m_cLocation.X, g_sEnemy->m_cLocation.Y, g_sChar->m_cAttackLocation.X, g_sChar->m_cAttackLocation.Y))
	{
		g_sEnemy->m_iHitpoints--;
		SelectedEnemyHP(g_sEnemy->m_iHitpoints);
		PlaySound(TEXT("snd_PlayerHitEnemy.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (g_sEnemy->m_iHitpoints == 0)
		{
			g_sChar->m_iKills++;
			if (g_sChar->m_iHitpoints < 9)
			{
				g_sChar->m_iHitpoints += 2;
			}
			else
			{
				g_sChar->m_iHitpoints = 10;
			}
			g_sEnemy->m_bActive = false;
			//playerPoints->increasePoints();
			PlaySound(TEXT("snd_EnemyDie.wav"), NULL, SND_FILENAME | SND_ASYNC);
			g_sEnemy->m_dExplosionTime = *g_dElapsedTime + 0.25;

		}
	}
	if (g_sEnemy->m_dExplosionTime > *g_dElapsedTime)
	{
		renderExplosion(g_Console, g_sEnemy->m_cLocation.X - 1, g_sEnemy->m_cLocation.Y - 1);
	}
	else if (*g_dElapsedTime > g_sEnemy->m_dExplosionTime && !g_sEnemy->m_bActive)
	{
		g_sEnemy->m_cLocation.X = 0;
		g_sEnemy->m_cLocation.Y = 0;
	}
}

void cCheckForDamage(SGameChar *g_sChar, SGameChar g_sEnemy)
{
	if (g_sChar->m_cLocation.X == g_sEnemy.m_cAttackLocation.X && g_sChar->m_cLocation.Y == g_sEnemy.m_cAttackLocation.Y)
	{
		PlaySound(TEXT("snd_EnemyHitPlayer.wav"), NULL, SND_FILENAME | SND_ASYNC);
		g_sChar->m_iHitpoints -= g_sEnemy.m_iDamage;
	}
}

unsigned int checkAtkType( COORD cAtkLctn )
{
	if (!collision(cAtkLctn.X, cAtkLctn.Y))
	{
		iAtkType = 1;
	}
	else
	{
		iAtkType = 0;
	}
	return iAtkType;
}

void playAttackSound(unsigned int iAtkType)
{
	switch (iAtkType)
	{
	case 0:
		PlaySound(TEXT("snd_PlayerAttackMiss.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 1:
		PlaySound(TEXT("snd_PlayerHitWall.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
}

void renderExplosion(Console *g_Console, short cX, short cY)
{
	WORD co = 0x0E;
	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{
			g_Console->writeToBuffer({ cX + i, cY + j }, (char)42, co);
		}
	}
}