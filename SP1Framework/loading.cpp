#include"Loading.h"

void loadfile(string mapname)
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
					g_sTeleporters[numTele].m_cLocation.X = col;
					g_sTeleporters[numTele].m_cLocation.Y = row;
					map[row][col] = (char)43;
					numTele++;
					break;
				case 'P':
					g_sDoor[1].m_cLocation.X = col;
					g_sDoor[1].m_cLocation.Y = row;
					map[row][col] = (char)205;
					break;
				case 'B':
					g_sEnemy[0].m_cLocation.X = col;
					g_sEnemy[0].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '1':
					g_sEnemy[1].m_cLocation.X = col;
					g_sEnemy[1].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '2':
					g_sEnemy[2].m_cLocation.X = col;
					g_sEnemy[2].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '3':
					g_sEnemy[3].m_cLocation.X = col;
					g_sEnemy[3].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '4':
					g_sEnemy[4].m_cLocation.X = col;
					g_sEnemy[4].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '5':
					g_sEnemy[5].m_cLocation.X = col;
					g_sEnemy[5].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '6':
					g_sEnemy[6].m_cLocation.X = col;
					g_sEnemy[6].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '7':
					g_sEnemy[7].m_cLocation.X = col;
					g_sEnemy[7].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '8':
					g_sEnemy[8].m_cLocation.X = col;
					g_sEnemy[8].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case '9':
					g_sEnemy[9].m_cLocation.X = col;
					g_sEnemy[9].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case 'A':
					g_sEnemy[10].m_cLocation.X = col;
					g_sEnemy[10].m_cLocation.Y = row;
					map[row][col] = ' ';
					break;
				case 'X':
					g_sDoor[0].m_cLocation.X = col;
					g_sDoor[0].m_cLocation.Y = row;
					map[row][col] = (char)186;
					break;
				case 'K':
					g_sKey.m_cLocation.X = col;
					g_sKey.m_cLocation.Y = row;
					map[row][col] = ' ';
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
}