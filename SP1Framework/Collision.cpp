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
	default:
		return true;
		break;
	}
}