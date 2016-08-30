#include"Fogofwar.h"

void FOW(int x,int y, char(&map)[height][width], char(&fog)[height][width])
{
	float walls = 0.0f;
	bool hitWall = false;
	int radius = 2;
	/*for (int lookrow = radius; lookrow >= -radius; lookrow--)
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
			fog[tempY][tempX] = map[tempY][tempX];
		}
	}*/
	//--------------------------------------------------------------
	// reveal up/north side of the player
	//--------------------------------------------------------------

	for (int lookrow = y; lookrow >= y - radius; lookrow--)
	{
		for (int lookcol = x - ceil(walls / 2.0f); lookcol <= x + ceil(walls / 2.0f); lookcol++)
		{
			if (map[lookrow][x] == '.')
			{
				fog[lookrow][lookcol] = map[lookrow][lookcol];
			}
			else
			{
				if (map[lookrow + 1][lookcol + 1] == (char)219 && lookcol == x - ceil(walls / 2.0f))
				{
					continue;
				}
				if (map[lookrow + 1][lookcol - 1] == (char)219 && lookcol == x + ceil(walls / 2.0f))
				{
					continue;
				}
				else
				{
					fog[lookrow][lookcol] = map[lookrow][lookcol];
				}

			}
			if (map[lookrow][x] == (char)219 || map[lookrow][x] == (char)186 || map[lookrow][x] == (char)205)
			{
				hitWall = true;
			}
		}
		walls++;
		if (hitWall)
		{
			break;
		}
	}
	walls = 0.0f;
	hitWall = false;
	//--------------------------------------------------------------
	// reveal down/south side of the player
	//--------------------------------------------------------------
	for (int lookrow = y; lookrow <= y + radius; lookrow++)
	{
		for (int lookcol = x - ceil(walls / 2.0f); lookcol <= x + ceil(walls / 2.0f); lookcol++)
		{
			if (map[lookrow][x] == '.')
			{
				fog[lookrow][lookcol] = map[lookrow][lookcol];
			}
			else
			{
				if (map[lookrow - 1][lookcol + 1] == (char)219 && lookcol == x - ceil(walls / 2.0f))
				{
					continue;
				}
				if (map[lookrow - 1][lookcol - 1] == (char)219 && lookcol == x + ceil(walls / 2.0f))
				{
					continue;
				}
				else
				{
					fog[lookrow][lookcol] = map[lookrow][lookcol];
				}

			}
			if (map[lookrow][x] == (char)219|| map[lookrow][x] == (char)186|| map[lookrow][x] == (char)205)
			{
				hitWall = true;
			}
		}
		walls++;
		if (hitWall)
		{
			break;
		}
	}
	walls = 0.0f;
	hitWall = false;
	//--------------------------------------------------------------
	// reveal left/west side of the player
	//--------------------------------------------------------------
	for (int lookcol = x; lookcol >= x - radius; lookcol--)
	{
		for (int lookrow = y - ceil(walls / 2.0f); lookrow <= y + ceil(walls / 2.0f); lookrow++)
		{
			if (map[y][lookcol] == '.')
			{
				fog[lookrow][lookcol] = map[lookrow][lookcol];
			}
			else
			{
				if (map[lookrow + 1][lookcol + 1] == (char)219 && lookrow == y - ceil(walls / 2.0f))
				{
					continue;
				}
				if (map[lookrow - 1][lookcol + 1] == (char)219 && lookrow == y + ceil(walls / 2.0f))
				{
					continue;
				}
				else
				{
					fog[lookrow][lookcol] = map[lookrow][lookcol];
				}

			}
			if (map[y][lookcol] == (char)219 || map[y][lookcol] == (char)186 || map[y][lookcol] == (char)205)
			{
				hitWall = true;
			}
		}
		walls++;
		if (hitWall)
		{
			break;
		}
	}
	walls = 0.0f;
	hitWall = false;
	//--------------------------------------------------------------
	// reveal rigt/east side of the player
	//--------------------------------------------------------------

	for (int lookcol = x; lookcol <= x + radius; lookcol++)
	{
		for (int lookrow = y - ceil(walls / 2.0f); lookrow <= y + ceil(walls / 2.0f); lookrow++)
		{
			if (map[y][lookcol] == '.')
			{
				fog[lookrow][lookcol] = map[lookrow][lookcol];
			}
			else
			{
				if (map[lookrow + 1][lookcol - 1] == (char)219 && lookrow == y - ceil(walls / 2.0f))
				{
					continue;
				}
				if (map[lookrow - 1][lookcol - 1] == (char)219 && lookrow == y + ceil(walls / 2.0f))
				{
					continue;
				}
				else
				{
					fog[lookrow][lookcol] = map[lookrow][lookcol];
				}

			}
			if (map[y][lookcol] == (char)219 || map[y][lookcol] == (char)186 || map[y][lookcol] == (char)205)
			{
				hitWall = true;
			}
		}
		walls++;
		if (hitWall)
		{
			break;
		}
	}
}