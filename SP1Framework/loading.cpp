#include"Loading.h"

void loadfile(string mapname, int *numTele, int *numEnemy, MAPDATA(&MapData)[height][width], SGameObj *g_sKey, SGameObj g_sDoor[], SGameChar g_sEnemy[], SGameObj g_sTeleporters[], char(&map)[height][width], char(&fog)[height][width])
{
	unsigned int row = 1;
	string line = " ";
	ifstream file(mapname);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			for (unsigned int col = 0; col < line.size(); col++)
			{
				switch (line[col])
				{
				case 'W':
					map[row][col] = (char)219;
					MapData[row][col] = WALL;
					break;
				case 'w':
					map[row][col] = 'W';
					break;
				case 'b':
					map[row][col] = 'B';
					break;
				case 'T':
					initializeTeleporters(&g_sTeleporters[*numTele], row, col);
					map[row][col] = (char)43;
					MapData[row][col] = TELE;
					*numTele = *numTele + 1;
					break;
				case 'P':
					g_sDoor[1].m_cLocation.X = col;
					g_sDoor[1].m_cLocation.Y = row;
					g_sDoor[1].m_bActive = true;
					map[row][col] = (char)205;
					MapData[row][col] = DOOR;
					break;
				case 'B':
					initializeEnemy(&g_sEnemy[*numEnemy], row, col);
					map[row][col] = '.';
					MapData[row][col] = NOTHING;
					*numEnemy = *numEnemy + 1;
					break;
				case 'X':
					g_sDoor[0].m_cLocation.X = col;
					g_sDoor[0].m_cLocation.Y = row;
					g_sDoor[0].m_bActive = true;
					map[row][col] = (char)186;
					MapData[row][col] = DOOR;
					break;
				case 'K':
					(*g_sKey).m_cLocation.X = col;
					(*g_sKey).m_cLocation.Y = row;
					(*g_sKey).m_bActive = true;
					map[row][col] = '.';
					MapData[row][col] = NOTHING;
					break;
				default:
					map[row][col] = line[col];
					MapData[row][col] = NOTHING;
					break;
				}
			}
			row++;
		}
		file.close();
	}
	row = 1;
	ifstream afile("fog.txt");
	if (afile.is_open())
	{
		while (getline(afile, line))
		{
			for (unsigned int col = 0; col < line.size(); col++)
			{
				if (line[col] == '.')
				{
					fog[row][col] = ' ';
				}
				else if (line[col] == 'N')
				{
					fog[row][col] = (char)178;
				}
				else
				{
					fog[row][col] = line[col];
				}
			}
			row++;
		}
	}
}

void initializeEnemy(SGameChar *g_sEnemy, unsigned int row, unsigned int col)
{
	g_sEnemy->m_cLocation.X = col;
	g_sEnemy->m_cLocation.Y = row;
	g_sEnemy->m_bActive = true;
	g_sEnemy->m_iHitpoints = 3;
	g_sEnemy->m_dExplosionTime = 0.0;
	g_sEnemy->m_dNextAttackTime = 0.0;
	g_sEnemy->m_iDamage = 1;
	g_sEnemy->m_dAttackRate = 2.0;
	g_sEnemy->m_bCanAttack = false;
	g_sEnemy->m_cAttackLocation = { 0,0 };
}

void initializeTeleporters(SGameObj *g_sTeleporters, unsigned int row, unsigned int col)
{
	g_sTeleporters->m_cLocation.X = col;
	g_sTeleporters->m_cLocation.Y = row;
	g_sTeleporters->m_bActive = true;
}