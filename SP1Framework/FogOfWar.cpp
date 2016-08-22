#include"Fogofwar.h"
void FOW(int x,int y)
{
	int radius = 2;
	for (int lookrow = (radius * 2); lookrow > -(radius * 2); lookrow--)
	{
		for (int lookcol = (radius * 2); lookcol > -(radius * 2); lookcol--)
		{
			int tempy = y - lookrow;
			int tempx = x - lookcol;
			if (tempy < 0)
			{
				tempy = 0;
			}
			if (tempx < 0)
			{
				tempx = 0;
			}
			fog[tempy][tempx] = map[tempy][tempx];
		}
	}
}