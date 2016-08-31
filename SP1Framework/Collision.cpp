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

bool PositionCollision(int x1, int y1, int x2, int y2)		// x1 - x coord of first char, y1 - y coord of first char, x2 - x coord of second char, y2 - y coord of second char
{
	return (x1 == x2 && y1 == y2);
}

bool CheckAroundSelf(COORD cTarget, COORD cSelf)
{
	COORD cSelfUp = { cSelf.X,cSelf.Y - 1 };
	COORD cSelfDown = { cSelf.X,cSelf.Y + 1 };
	COORD cSelfRight = { cSelf.X + 1,cSelf.Y };
	COORD cSelfLeft = { cSelf.X - 1,cSelf.Y };

	if (PositionCollision(cTarget.X, cTarget.Y, cSelfUp.X, cSelfUp.Y) || PositionCollision(cTarget.X, cTarget.Y, cSelfLeft.X, cSelfLeft.Y) || PositionCollision(cTarget.X, cTarget.Y, cSelfRight.X, cSelfRight.Y) || PositionCollision(cTarget.X, cTarget.Y, cSelfDown.X, cSelfDown.Y))
	{
		return true;
	}
	else
	{
		return false;
	}
}