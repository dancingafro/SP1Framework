#include "game.h"

int     directionAIMove = 1;      // 1 = up, 2 = left, 3 = down, 4 =right

void randomMovement(double g_dElapsedTime, SGameChar *g_sEnemy, MAPDATA(&MapData)[height][width])
{
	// Lets the AI only be able to move after at least X second has passed since it's last movement
	if (g_dElapsedTime < g_sEnemy->m_dTimeSinceLastAIMove)
	{
		return;
	}
	directionAIMove = g_sEnemy->m_directionFacing;
	
	if (directionAIMove == 1)
	{
		if (collision(g_sEnemy->m_cLocation.X, g_sEnemy->m_cLocation.Y - 1, MapData))     // Check if above AI got wall
		{
			g_sEnemy->m_cLocation.Y--;
		}
		else       // Above AI got wall
		{
			directionAIMove = (rand() % 4 + 1);
		}

	}
	else if (directionAIMove == 2)
	{
		if (collision(g_sEnemy->m_cLocation.X - 1, g_sEnemy->m_cLocation.Y, MapData))     // Check if above AI got wall
		{
			g_sEnemy->m_cLocation.X--;
		}
		else       // Above AI got wall
		{
			directionAIMove = (rand() % 4 + 1);
		}

	}
	else if (directionAIMove == 3)
	{
		if (collision(g_sEnemy->m_cLocation.X, g_sEnemy->m_cLocation.Y + 1, MapData))     // Check if above AI got wall
		{
			g_sEnemy->m_cLocation.Y++;
		}
		else       // Above AI got wall
		{
			directionAIMove = (rand() % 4 + 1);
		}

	}
	else if (directionAIMove == 4)
	{
		if (collision(g_sEnemy->m_cLocation.X + 1, g_sEnemy->m_cLocation.Y, MapData))     // Check if above AI got wall
		{
			g_sEnemy->m_cLocation.X++;
		}
		else       // Above AI got wall
		{
			directionAIMove = (rand() % 4 + 1);
		}
	}
	g_sEnemy->m_dTimeSinceLastAIMove = g_dElapsedTime + 1;
}

void breadthFirstSearch(double g_dElapsedTime, SGameChar *g_sEnemy, SGameChar *g_sChar, MAPDATA(&MapData)[height][width])
{
	// Lets the AI only be able to move after at least X second has passed since it's last movement
	if (g_dElapsedTime < g_sEnemy->m_dTimeSinceLastAIMove)
	{
		return;
	}
	if (g_sEnemy->m_seePlayer)
	{
		if ((g_sEnemy->m_cLocation.X != g_sChar->m_cLocation.X || g_sEnemy->m_cLocation.Y != g_sChar->m_cLocation.Y) && g_sEnemy->m_bActive)
		{
			bool gotAINearby = false;
			vector<int> AICannotMove1;
			vector<int> AICannotMove2;
			int pathFindAI[25][80][3] = { 0, };
			//int enemyX = g_sChar->m_cLocation.X;
			//int enemyY = g_sChar->m_cLocation.Y;
			int enemyX = g_sEnemy->m_cLocation.X;
			int enemyY = g_sEnemy->m_cLocation.Y;
			pathFindAI[enemyY][enemyX][0] = 'c';	 // 0 - open list, c - closed list
			pathFindAI[enemyY][enemyX][1] = enemyY;  // 1 - Y-coords parent
			pathFindAI[enemyY][enemyX][2] = enemyX;  // 2 - X-coords parent
			pair<int, int> coords;
			pair<int, int> current;
			pair<int, int> playerLocation;
			pair<int, int> enemyLocation;
			queue<pair<int, int>> listOfNodes;   // to store the neighbouring nodes that are in the open list

			playerLocation = make_pair(g_sEnemy->m_cLastSeenLocation.Y, g_sEnemy->m_cLastSeenLocation.X);    // coords of player last seen location

			//-------------------------QUEUE NEIGHBOURING--------------------------------------------------------------------------------------------
			if (collision(enemyX, enemyY - 1, MapData))				// if above current node no wall
			{
				coords = make_pair(enemyY - 1, enemyX);		// add above node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY - 1][enemyX][0] = 'c';	// add node to closed list
				pathFindAI[enemyY - 1][enemyX][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY - 1][enemyX][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX, enemyY + 1, MapData))				// if below current node no wall
			{
				coords = make_pair(enemyY + 1, enemyX);		// add below node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY + 1][enemyX][0] = 'c';	// add node to closed list
				pathFindAI[enemyY + 1][enemyX][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY + 1][enemyX][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX - 1, enemyY, MapData))				// if to the left of current node no wall
			{
				coords = make_pair(enemyY, enemyX - 1);		// add left node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY][enemyX - 1][0] = 'c';	// add node to closed list
				pathFindAI[enemyY][enemyX - 1][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY][enemyX - 1][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX + 1, enemyY, MapData))				// if to the right of current node no wall
			{
				coords = make_pair(enemyY, enemyX + 1);		// add right node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY][enemyX + 1][0] = 'c';	// add node to closed list
				pathFindAI[enemyY][enemyX + 1][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY][enemyX + 1][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			//-------------------------QUEUE NEIGHBOURING--------------------------------------------------------------------------------------------

			//-----------------ADD CURRENT ITEMS IN QUEUE TO CLOSED LIST AFTER ADDING NEIGHBOURING NODES--------------------------------


			while (current != playerLocation)
			{
				current = listOfNodes.front();			 // current.first = y-coords, current.second = x-coords
				listOfNodes.pop();
				if (collision(current.second, current.first - 1, MapData))				// if above current node no wall
				{
					if (pathFindAI[current.first - 1][current.second][0] == 0)
					{
						coords = make_pair(current.first - 1, current.second);		// add above node to queue
						listOfNodes.push(coords);
						pathFindAI[current.first - 1][current.second][0] = 'c';		// add node to closed list
						pathFindAI[current.first - 1][current.second][1] = current.first; // add Y-coords of parent node (the node where the neighbouring node came from)
						pathFindAI[current.first - 1][current.second][2] = current.second; // add X-coords of parent node (the node where the neighbouring node came from)
					}
				}
				if (collision(current.second, current.first + 1, MapData))				// if below current node no wall
				{
					if (pathFindAI[current.first + 1][current.second][0] == 0)
					{
						coords = make_pair(current.first + 1, current.second);		// add below node to queue
						listOfNodes.push(coords);
						pathFindAI[current.first + 1][current.second][0] = 'c';		// add node to closed list
						pathFindAI[current.first + 1][current.second][1] = current.first; // add Y-coords of parent node (the node where the neighbouring node came from)
						pathFindAI[current.first + 1][current.second][2] = current.second; // add X-coords of parent node (the node where the neighbouring node came from)
					}
				}
				if (collision(current.second - 1, current.first, MapData))				// if to the left of current node no wall
				{
					if (pathFindAI[current.first][current.second - 1][0] == 0)
					{
						coords = make_pair(current.first, current.second - 1);		// add left node to queue
						listOfNodes.push(coords);
						pathFindAI[current.first][current.second - 1][0] = 'c';		// add node to closed list
						pathFindAI[current.first][current.second - 1][1] = current.first; // add Y-coords of parent node (the node where the neighbouring node came from)
						pathFindAI[current.first][current.second - 1][2] = current.second; // add X-coords of parent node (the node where the neighbouring node came from)
					}
				}
				if (collision(current.second + 1, current.first, MapData))				// if to the right of current node no wall
				{
					if (pathFindAI[current.first][current.second + 1][0] == 0)
					{
						coords = make_pair(current.first, current.second + 1);		// add right node to queue
						listOfNodes.push(coords);
						pathFindAI[current.first][current.second + 1][0] = 'c';		// add node to closed list
						pathFindAI[current.first][current.second + 1][1] = current.first; // add Y-coords of parent node (the node where the neighbouring node came from)
						pathFindAI[current.first][current.second + 1][2] = current.second; // add X-coords of parent node (the node where the neighbouring node came from)
					}
				}
				if (listOfNodes.empty())
				{
					g_sEnemy->m_seePlayer = false;
					break;
				}
			}
			//-----------------ADD CURRENT ITEMS IN QUEUE TO CLOSED LIST AFTER ADDING NEIGHBOURING NODES--------------------------------

			//-----------------TRACING THE PATH BACK VIA PARENT-------------------------------------------------------------------------

			int tempX = current.second;
			int tempY = current.first;

			enemyX = tempX;
			enemyY = tempY;

			while (true)
			{
				if (pathFindAI[enemyY][enemyX][1] == g_sEnemy->m_cLocation.Y && pathFindAI[enemyY][enemyX][2] == g_sEnemy->m_cLocation.X)
				{
					break;
				}
				tempY = pathFindAI[enemyY][enemyX][1];
				tempX = pathFindAI[enemyY][enemyX][2];

				enemyX = tempX;
				enemyY = tempY;
			}
			//-----------------TRACING THE PATH BACK VIA PARENT-------------------------------------------------------------------------

			//-----------------AI TO AI COLLISION---------------------------------------------------------------------------------------

			/*if (a != (*numEnemy - 1))
			{
				for (int i = a + 1; i < *numEnemy; i++)
				{
					if (enemyX == g_sEnemy[i].m_cLocation.X && enemyY == g_sEnemy[i].m_cLocation.Y)
					{
						gotAINearby = true;
					}
				}
			}
			if (a != 0)
			{
				for (int y = a - 1; y >= 0; y--)
				{

					if (enemyX == g_sEnemy[y].m_cLocation.X && enemyY == g_sEnemy[y].m_cLocation.Y)
					{
						gotAINearby = true;
					}
				}
			}
			if (gotAINearby)
			{
				return;
			}*/
			//-----------------AI TO AI COLLISION---------------------------------------------------------------------------------------


			//-----------------CALCULATE THE NEXT SINGLE MOVEMENT-----------------------------------------------------------------------

			//if ((enemyX != g_sEnemy->m_cLastSeenLocation.X || enemyY != g_sEnemy->m_cLastSeenLocation.Y))
			if ((enemyX != g_sChar->m_cLocation.X || enemyY != g_sChar->m_cLocation.Y))
			{
				g_sEnemy->m_cLocation.X = enemyX;
				g_sEnemy->m_cLocation.Y = enemyY;
			}
			//-----------------CALCULATE THE NEXT SINGLE MOVEMENT-----------------------------------------------------------------------


		}
		g_sEnemy->m_dTimeSinceLastAIMove = g_dElapsedTime + 0.4;
	}
}


bool lineOfSight( SGameChar *g_sEnemy, SGameChar *g_sChar, MAPDATA(&MapData)[height][width])
{
	int x = g_sEnemy->m_cLocation.X;
	int y = g_sEnemy->m_cLocation.Y;
	float walls = 0.0f;
	bool hitWall = false;
	int radius = 3;
	int playerY = g_sChar->m_cLocation.Y;
	int playerX = g_sChar->m_cLocation.X;

	for (int lookrow = y; lookrow >= y - radius; lookrow--)
	{
		for (int lookcol = x - ceil(walls / 2.0f); lookcol <= x + ceil(walls / 2.0f); lookcol++)
		{	
			if (MapData[lookrow][x] == NOTHING)
			{
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			else
			{
				if (MapData[lookrow + 1][lookcol + 1] == WALL && lookcol == x - ceil(walls / 2.0f))
				{
					continue;
				}
				if (MapData[lookrow + 1][lookcol - 1] == WALL && lookcol == x + ceil(walls / 2.0f))
				{
					continue;
				}
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			if (MapData[lookrow][x] == WALL || MapData[lookrow][x] == DOOR)
			{
				hitWall = true;
			}
			
		}
		walls++;
		if (hitWall)
		{
			g_sEnemy->m_seePlayer = false;
			break;
		}
	}
	walls = 0.0f;
	hitWall = false;


	for (int lookrow = y; lookrow <= y + radius; lookrow++)
	{
		for (int lookcol = x - ceil(walls / 2.0f); lookcol <= x + ceil(walls / 2.0f); lookcol++)
		{
			if (MapData[lookrow][x] == NOTHING)
			{
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			else
			{
				if (MapData[lookrow - 1][lookcol + 1] == WALL && lookcol == x - ceil(walls / 2.0f))
				{
					continue;
				}
				if (MapData[lookrow - 1][lookcol - 1] == WALL && lookcol == x + ceil(walls / 2.0f))
				{
					continue;
				}
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			if (MapData[lookrow][x] == WALL || MapData[lookrow][x] == DOOR)
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


	for (int lookcol = x; lookcol >= x - radius; lookcol--)
	{
		for (int lookrow = y - ceil(walls / 2.0f); lookrow <= y + ceil(walls / 2.0f); lookrow++)
		{
			if (MapData[y][lookcol] == NOTHING)
			{
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			else
			{
				if (MapData[lookrow + 1][lookcol + 1] == WALL && lookrow == y - ceil(walls / 2.0f))
				{
					continue;
				}
				if (MapData[lookrow - 1][lookcol + 1] == WALL && lookrow == y + ceil(walls / 2.0f))
				{
					continue;
				}
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			if (MapData[y][lookcol] == WALL || MapData[y][lookcol] == DOOR)
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


	for (int lookcol = x; lookcol <= x + radius; lookcol++)
	{
		for (int lookrow = y - ceil(walls / 2.0f); lookrow <= y + ceil(walls / 2.0f); lookrow++)
		{
			if (MapData[y][lookcol] == NOTHING)
			{
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			else
			{
				if (MapData[lookrow + 1][lookcol - 1] == WALL && lookrow == y - ceil(walls / 2.0f))
				{
					continue;
				}
				if (MapData[lookrow - 1][lookcol - 1] == WALL && lookrow == y + ceil(walls / 2.0f))
				{
					continue;
				}
				if (lookcol == playerX && lookrow == playerY)
				{
					g_sEnemy->m_seePlayer = true;
					g_sEnemy->m_cLastSeenLocation.X = playerX;
					g_sEnemy->m_cLastSeenLocation.Y = playerY;
					return true;
				}
			}
			if (MapData[y][lookcol] == WALL || MapData[y][lookcol] == DOOR)
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
	g_sEnemy->m_seePlayer = false;
	return false;
	/*
	int enemyX = g_sEnemy->m_cLocation.X;
	int enemyY = g_sEnemy->m_cLocation.Y;

	int distanceFromPlayerToEnemyX = g_sChar->m_cLocation.X - enemyX;
	int distanceFromPlayerToEnemyY = g_sChar->m_cLocation.Y - enemyY;

	int distanceX = abs(distanceFromPlayerToEnemyX);
	int distanceY = abs(distanceFromPlayerToEnemyY);

	int signX;
	int signY;

	if (distanceX > 0)
	{
		signX = 1;
	}
	else
	{
		signX = -1;
	}

	if (distanceY > 0)
	{
		signY = 1;
	}
	else
	{
		signY = -1;
	}

	int x = g_sEnemy->m_cLocation.X;
	int y = g_sEnemy->m_cLocation.Y;

	double increaseNonDominant;

	if (distanceX > distanceY)
	{
		increaseNonDominant = (distanceY * 2) - distanceX;
		do
		{
			if (increaseNonDominant >= 0)
			{
				y += signY;
				increaseNonDominant -= (distanceX * 2);
			}
			x += signX;
			increaseNonDominant += (distanceY * 2);

			if (x == g_sChar->m_cLocation.X && y == g_sChar->m_cLocation.Y)
			{
				g_sChar->m_cLastSeenLocation.X = x;
				g_sChar->m_cLastSeenLocation.Y = y;
				g_sEnemy->m_seePlayer = true;
				return true;
			}
		} while (collision(x, y));
		return false;
	}
	else
	{
		increaseNonDominant = (distanceY * 2) - distanceX;
		do
		{
			if (increaseNonDominant >= 0)
			{
				x += signX;
				increaseNonDominant -= (distanceY * 2);
			}
			y += signY;
			increaseNonDominant += (distanceX * 2);

			if (x == g_sChar->m_cLocation.X && y == g_sChar->m_cLocation.Y)
			{
				g_sChar->m_cLastSeenLocation.X = x;
				g_sChar->m_cLastSeenLocation.Y = y;
				g_sEnemy->m_seePlayer = true;
				return true;
			}
		} while (collision(x, y));
		return false;
	}
	*/
}

int playerToEnemyDistance(int a, SGameChar g_sEnemy[], SGameChar *g_sChar)
{
	int x1 = g_sEnemy->m_cLocation.X;
	int y1 = g_sEnemy->m_cLocation.Y;
	int x2 = g_sChar->m_cLocation.X;
	int y2 = g_sChar->m_cLocation.Y;
	int distance = sqrt(pow(x1 - x2, 2) - pow(y1 - y2, 2));
	return distance;
}

