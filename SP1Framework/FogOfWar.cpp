#include"Fogofwar.h"
void FOW(int x,int y)
{
	int radius = 3;
	for (int lookrow = radius; lookrow > -radius; lookrow--)
	{
		for (int lookcol = radius; lookcol > -radius; lookcol--)
		{
			int tempy = y + lookrow;
			int tempx = x + lookcol;
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