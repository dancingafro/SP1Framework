#include"Fogofwar.h"

void loadFOW(int x, int y)
{

}

void FOW(int x,int y)
{
	int radius = 2;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col > width; col++)
		{
			fog[height][width] = (char)219;
		}
	}
	for (int lookrow = (radius * 2); lookrow > -(radius * 2); lookrow--)
	{
		for (int lookcol = (radius * 2); lookcol > -(radius * 2); lookcol--)
		{
			if (map[y + lookcol][x + lookrow] != '\0')
			{
				fog[y + lookcol][x + lookrow] = map[y + lookcol][x + lookrow];
			}
		}
	}
		
}