#include "points.h"

points::points()
{
	pointCount = 0;
}

points::~points()
{

}

int points::getPoints()
{
	return pointCount;
}

void points::increasePoints()
{
	pointCount += 5;
}