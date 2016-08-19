#include"Loading.h"

void loadfile(string mapname)
{
	int row = 0;
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
					map[row][col] = (char)43;
					break;
				case 'P':
					g_sDoor[1].m_cLocation.X = col;
					g_sDoor[1].m_cLocation.Y = row;
					map[row][col] = (char)205;
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