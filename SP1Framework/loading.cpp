#include"Loading.h"

void loadfile(string mapname,int *numTele, int *numEnemy, SGameObj *g_sKey, SGameObj g_sDoor[], SGameChar g_sEnemy[], SGameObj g_sTeleporters[])
{
	int row = 1;
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
					break;
				case 'T':
					g_sTeleporters[*numTele].m_cLocation.X = col;
					g_sTeleporters[*numTele].m_cLocation.Y = row;
					g_sTeleporters[*numTele].m_bActive = true;
					map[row][col] = (char)43;
					*numTele = *numTele + 1;
					break;
				case 'P':
					g_sDoor[1].m_cLocation.X = col;
					g_sDoor[1].m_cLocation.Y = row;
					g_sDoor[1].m_bActive = true;
					map[row][col] = (char)205;
					break;
				case 'B':
					g_sEnemy[*numEnemy].m_cLocation.X = col;
					g_sEnemy[*numEnemy].m_cLocation.Y = row;
					g_sEnemy[*numEnemy].m_bActive = true;
					map[row][col] = '.';
					*numEnemy = *numEnemy + 1;
					break;
				case 'X':
					g_sDoor[0].m_cLocation.X = col;
					g_sDoor[0].m_cLocation.Y = row;
					g_sDoor[0].m_bActive = true;
					map[row][col] = (char)186;
					break;
				case 'K':
					(*g_sKey).m_cLocation.X = col;
					(*g_sKey).m_cLocation.Y = row;
					(*g_sKey).m_bActive = true;
					map[row][col] = '.';
					break;
				default:
					map[row][col] = line[col];
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