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

bool gotPlayerCollision(int x1, int y1, int x2, int y2)		// x1 - x coord of first char, y1 - y coord of first char, x2 - x coord of second char, y2 - y coord of second char
{
	return (x1 == x2 && y1 == y2);
}

bool EnemyIsAttacked(int x1, int x2,int y1, int y2)
{
	if (x1 == x2 && y1 == y2)
	{
		return true;
	}
	return false;
}