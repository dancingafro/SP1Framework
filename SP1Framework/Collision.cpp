#include"Collision.h"

bool collision(int x,int y)
{
	switch (map[y][x])
	{
	case (char)219:
		return false;
		break;
	case (char)186:
		return false;
		break;
	case (char)205:
		return false;
		break;
	case 'E':
		return true;
		break;
	default:
		return true;
		break;
	}
}

bool EnemyIsAttacked(int x1, int x2,int y1, int y2)
{
	if (x1 == x2 && y1 == y2)
	{
		return true;
	}
	return false;
}