#include"Fogofwar.h"
void FOW(int x,int y)
{
	int radius = 3;
	for (int lookrow = radius; lookrow > -radius; lookrow--)
	{
		for (int lookcol = radius; lookcol > -radius; lookcol--)
		{
			int tempY = y + lookrow;
			int tempX = x + lookcol;
			if (tempY < 0)
			{
				tempY = 0;
			}
			if (tempX < 0)
			{
				tempX = 0;
			}
			if (tempY > height-10)
			{
				tempY = height - 10;
			}
			if (tempX > width)
			{
				tempX = 80;
			}
			fog[tempY][tempX] = map[tempY][tempX];
		}
	}
}