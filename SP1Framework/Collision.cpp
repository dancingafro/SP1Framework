#include"Collision.h"

bool collision(int x, int y, MAPDATA(&MapData)[height][width])
{
	switch (MapData[y][x])
	{
	case WALL:
		return false;
		break;
	case DOOR:
		return false;
		break;
	case EXIT:
		return true;
		break;
	default:
		return true;
		break;
	}
}

bool PositionCollision(int x1, int y1, int x2, int y2)		// x1 - x coord of first char, y1 - y coord of first char, x2 - x coord of second char, y2 - y coord of second char
{
	return (x1 == x2 && y1 == y2);
}