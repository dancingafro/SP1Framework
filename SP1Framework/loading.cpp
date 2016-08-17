#include"Loading.h"

void loadmaps(string mapname)
{
	int row = 0;
	string line = " ";
	ifstream file(mapname);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i]=='W')
				{
					map[row][i] = (char)219;
				}
				else
				{
					map[row][i] = line[i];
				}
			}
			row++;
		}
		file.close();
	}
}