#include"Fogofwar.h"
void FOW(int x,int y)
{
	int radius = 2;
	for (int lookrow = radius; lookrow >= -radius; lookrow--)
	{
		for (int lookcol = radius; lookcol >= -radius; lookcol--)
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
			if (tempY >= height-10)
			{
				tempY = height - 10;
			}
			if (tempX >= width)
			{
				tempX = width - 1;
			}
			/*if (tempY < y)
			{
				if (tempY+1 < y)
				{
					if (map[tempY+2][tempX] == (char)219)
					{
						continue;
					}
				}
				else if (map[tempY + 1][tempX] == (char)219)
				{
					continue;
				}
			}
			else if (tempY > y)
			{
				if (tempY - 1 > y)
				{
					if (map[tempY - 2][tempX] == (char)219)
					{
						continue;
					}
				}
				else if (map[tempY - 1][tempX] == (char)219)
				{
					continue;
				}
			}
			if (tempX < x)
			{
				if (tempX + 1 < x)
				{
					if (map[tempY][tempX+2] == (char)219)
					{
						continue;
					}
				}
				else if (map[tempY][tempX+1] == (char)219)
				{
					continue;
				}
			}
			else if (tempX > x)
			{
				if (tempX - 1 > x)
				{
					if (map[tempY][tempX - 2] == (char)219)
					{
						continue;
					}
				}
				else if (map[tempY][tempX - 1] == (char)219)
				{
					continue;
				}
			}*/
			fog[tempY][tempX] = map[tempY][tempX];
		}
	}
}