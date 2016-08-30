#include "game.h"
#include "CheckAttack.h"

unsigned int iEnemyHP;

void renderHUD(SGameChar *g_sChar, Console *g_Console)
{
	WORD HPColor = 0x0A;
	char cKillCountOnes = '0';
	char cKillCountTens = '0';
	COORD c;
	c.Y = 28;
	unsigned int iHP = g_sChar->m_iHitpoints;

	for (unsigned int i = 0; i < iHP; i++)
	{
		c.X = 6 + i;
		if (g_sChar->m_iHitpoints <= 7 && g_sChar->m_iHitpoints > 3)
		{
			HPColor = 0x0E;
		}
		else if (g_sChar->m_iHitpoints <= 3)
		{
			HPColor = 0x0C;
		}
		g_Console->writeToBuffer(c, (char)219, HPColor);
	}
	c.Y = 29;
	c.X = 8;
	if (g_sChar->m_iKills <= 9)
	{
		cKillCountOnes += g_sChar->m_iKills;
		g_Console->writeToBuffer(c, '0', 0x0F);
		c.X = 9;
		g_Console->writeToBuffer(c, cKillCountOnes, 0x0F);
	}
	else if (g_sChar->m_iKills > 9)
	{
		int r = g_sChar->m_iKills - 10;
		cKillCountOnes += r;
		cKillCountTens = '1';
		g_Console->writeToBuffer(c, cKillCountTens, 0x0F);
		c.X = 9;
		g_Console->writeToBuffer(c, cKillCountOnes, 0x0F);
	}
}
void SelectedEnemyHP(unsigned int iHP)
{
	iEnemyHP = iHP;
}
void eRenderHP(Console *g_Console)
{
	COORD c = { 0,28 };
	string sHPString = "Enemy H/P:";
	for (unsigned int i = 0; i < iEnemyHP; i++)
	{
		c.X = 23;
		g_Console->writeToBuffer(c, sHPString, 0x0F);
		c.X = 33 + i;
		g_Console->writeToBuffer(c, (char)219, 0x0C);
	}
}