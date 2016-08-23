#include"ResetData.h"

void ResetAllData(int *numTele, int *numEnemy, SGameObj * g_sKey, SGameChar g_sEnemy[], SGameObj g_sDoor[], SGameObj g_sTeleporters[])
{
	for (unsigned int row = 0; row < height; row++)
	{
		for (unsigned int col = 0; col < width; col++)
		{
			map[row][col] = ' ';
			fog[row][col] = ' ';
		}
	}
	for (unsigned int i = 0; i < totalTele; i++)
	{
		g_sTeleporters[i].m_cLocation.X = 0;
		g_sTeleporters[i].m_cLocation.Y = 0;
		g_sTeleporters[i].m_bActive = false;
	}
	for (unsigned int i = 0; i < totalEnemy; i++)
	{
		g_sEnemy[i].m_cLocation.X = 0;
		g_sEnemy[i].m_cLocation.Y = 0;
		g_sEnemy[i].m_bActive = false;
	}
	for (unsigned int i = 0; i < 2; i++)
	{
		g_sDoor[i].m_cLocation.X = 0;
		g_sDoor[i].m_cLocation.Y = 0;
		g_sDoor[i].m_bActive = false;
	}
	(*g_sKey).m_cLocation.X = 0;
	(*g_sKey).m_cLocation.Y = 0;
	(*g_sKey).m_bActive = false;
	(*numTele) = 0;
	(*numEnemy) = 0;
}