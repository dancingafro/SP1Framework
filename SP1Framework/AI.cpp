#include "game.h"

int     directionAIMove = 1;      // 1 = up, 2 = left, 3 = down, 4 =right
double  timeSinceLastAIMove;

void randomMovement(int *numEnemy, double *g_dElapsedTime, SGameChar g_sEnemy[])
{
	// Lets the AI only be able to move after at least 1 second has passed since it's last movement
	if (timeSinceLastAIMove == 0)
	{
		timeSinceLastAIMove = *g_dElapsedTime;
	}
	else
	{
		if (*g_dElapsedTime - timeSinceLastAIMove > 0.5)
		{
			timeSinceLastAIMove = 0;
		}
		return;
	}
	for (int a = 0; a < *numEnemy; a++)
	{
		

		if (directionAIMove == 1)
		{
			if (collision(g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y - 1))     // Check if above AI got wall
			{
				g_sEnemy[a].m_cLocation.Y--;
			}
			else       // Above AI got wall
			{
				directionAIMove = (rand() % 4 + 1);
			}

		}
		if (directionAIMove == 2)
		{
			if (collision(g_sEnemy[a].m_cLocation.X - 1, g_sEnemy[a].m_cLocation.Y))     // Check if above AI got wall
			{
				g_sEnemy[a].m_cLocation.X--;
			}
			else       // Above AI got wall
			{
				directionAIMove = (rand() % 4 + 1);
			}

		}
		if (directionAIMove == 3)
		{
			if (collision(g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y + 1))     // Check if above AI got wall
			{
				g_sEnemy[a].m_cLocation.Y++;
			}
			else       // Above AI got wall
			{
				directionAIMove = (rand() % 4 + 1);
			}

		}
		if (directionAIMove == 4)
		{
			if (collision(g_sEnemy[a].m_cLocation.X + 1, g_sEnemy[a].m_cLocation.Y))     // Check if above AI got wall
			{
				g_sEnemy[a].m_cLocation.X++;
			}
			else       // Above AI got wall
			{
				directionAIMove = (rand() % 4 + 1);
			}
		}
		/*
		int randomNumber = (rand() % 4 + 1);

		if (randomNumber == 1)
		{
		if (map[g_sEnemy.m_cLocation.Y - 1][g_sEnemy.m_cLocation.X] != (char)219)
		g_sEnemy.m_cLocation.Y--;
		}
		else if (randomNumber == 2)
		{
		if (map[g_sEnemy.m_cLocation.Y][g_sEnemy.m_cLocation.X - 1] != (char)219)
		g_sEnemy.m_cLocation.X--;
		}
		else if (randomNumber == 3)
		{
		if (map[g_sEnemy.m_cLocation.Y + 1][g_sEnemy.m_cLocation.X] != (char)219)
		g_sEnemy.m_cLocation.Y++;
		}
		else if (randomNumber == 4)
		{
		if (map[g_sEnemy.m_cLocation.Y][g_sEnemy.m_cLocation.X + 1] != (char)219)
		g_sEnemy.m_cLocation.X++;
		}
		*/
	}
}

void breadthFirstSearch(double *g_dElapsedTime,int *numEnemy, SGameChar g_sEnemy[], SGameChar *g_sChar)
{
	// Lets the AI only be able to move after at least 1 second has passed since it's last movement
	if (timeSinceLastAIMove == 0)
	{
		timeSinceLastAIMove = *g_dElapsedTime;
	}
	else
	{
		if (*g_dElapsedTime - timeSinceLastAIMove > 1)
		{
			timeSinceLastAIMove = 0;
		}
		return;
	}
	for (int a = 0; a < *numEnemy; a++)
	{
		if ((g_sEnemy[a].m_cLocation.X != (*g_sChar).m_cLocation.X || g_sEnemy[a].m_cLocation.Y != (*g_sChar).m_cLocation.Y) && g_sEnemy[a].m_bActive)
		{
			bool gotAINearby = false;
			vector<int> AICannotMove1;
			vector<int> AICannotMove2;
			int pathFindAI[25][80][3] = { 0, };
			int enemyX = g_sEnemy[a].m_cLocation.X;
			int enemyY = g_sEnemy[a].m_cLocation.Y;
			pathFindAI[enemyY][enemyX][0] = 'c';	 // 0 - open list, c - closed list
			pathFindAI[enemyY][enemyX][1] = enemyY;  // 1 - Y-coords parent
			pathFindAI[enemyY][enemyX][2] = enemyX;  // 2 - X-coords parent
			pair<int, int> coords;
			pair<int, int> current;
			pair<int, int> playerLocation;
			pair<int, int> enemyLocation;
			queue<pair<int, int>> listOfNodes;   // to store the neighbouring nodes that are in the open list

			enemyLocation = make_pair(g_sEnemy[a].m_cLocation.Y, g_sEnemy[a].m_cLocation.X);   // coords of enemy
			playerLocation = make_pair((*g_sChar).m_cLocation.Y, (*g_sChar).m_cLocation.X);    // coords of player


			//-------------------------PREVENT PATHFINDING IF PLAYER NEXT TO AI----------------------------------------------------------------------
			/*
			if ((playerLocation.first + 1, playerLocation.second) == (enemyLocation.first, enemyLocation.second) ||
				(playerLocation.first - 1, playerLocation.second) == (enemyLocation.first, enemyLocation.second) ||
				(playerLocation.first, playerLocation.second + 1) == (enemyLocation.first, enemyLocation.second) ||
				(playerLocation.first, playerLocation.second - 1) == (enemyLocation.first, enemyLocation.second))
			{
				return;
			}
			*/
			//-------------------------PREVENT PATHFINDING IF PLAYER NEXT TO AI----------------------------------------------------------------------

			//-------------------------QUEUE NEIGHBOURING--------------------------------------------------------------------------------------------
			if (collision(enemyX, enemyY - 1))				// if above current node no wall
			{
				coords = make_pair(enemyY - 1, enemyX);		// add above node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY - 1][enemyX][0] = 'c';	// add node to closed list
				pathFindAI[enemyY - 1][enemyX][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY - 1][enemyX][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX, enemyY + 1))				// if below current node no wall
			{
				coords = make_pair(enemyY + 1, enemyX);		// add below node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY + 1][enemyX][0] = 'c';	// add node to closed list
				pathFindAI[enemyY + 1][enemyX][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY + 1][enemyX][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX - 1, enemyY))				// if to the left of current node no wall
			{
				coords = make_pair(enemyY, enemyX - 1);		// add left node to queue
				listOfNodes.push(coords);
				pathFindAI[enemyY][enemyX - 1][0] = 'c';	// add node to closed list
				pathFindAI[enemyY][enemyX - 1][1] = enemyY; // add Y-coords of parent node (the node where the neighbouring node came from)
				pathFindAI[enemyY][enemyX - 1][2] = enemyX; // add X-coords of parent node (the node where the neighbouring node came from)
			}
			if (collision(enemyX + 1, enemyY))				// if to the right of current node no wall
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
				if (collision(current.second, current.first - 1))				// if above current node no wall
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
				if (collision(current.second, current.first + 1))				// if below current node no wall
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
				if (collision(current.second - 1, current.first))				// if to the left of current node no wall
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
				if (collision(current.second + 1, current.first))				// if to the right of current node no wall
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
			}

			//-----------------ADD CURRENT ITEMS IN QUEUE TO CLOSED LIST AFTER ADDING NEIGHBOURING NODES--------------------------------

			//-----------------TRACING THE PATH BACK VIA PARENT-------------------------------------------------------------------------

			int tempX = current.second;
			int tempY = current.first;

			enemyX = tempX;
			enemyY = tempY;

			while (true)
			{
				if (pathFindAI[enemyY][enemyX][1] == g_sEnemy[a].m_cLocation.Y && pathFindAI[enemyY][enemyX][2] == g_sEnemy[a].m_cLocation.X)
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
			
			if (a != (*numEnemy - 1))
			{
				for (int i = a + 1; i < *numEnemy; i++)
				{
					if (enemyX == g_sEnemy[i].m_cLocation.X && enemyY == g_sEnemy[i].m_cLocation.Y)
					{
						gotAINearby = true;
						//AICannotMove1.push_back(i);
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
						//AICannotMove2.push_back(y);
					}
				}
			}
			/*
			if (find(AICannotMove1.begin(), AICannotMove1.end(), a) != AICannotMove1.end())
			{
				gotAINearby = true;
			}
			if (find(AICannotMove2.begin(), AICannotMove2.end(), a) != AICannotMove2.end())
			{
				gotAINearby = true;
			}
			*/
			if (gotAINearby)
			{
				continue;
			}
			//-----------------AI TO AI COLLISION---------------------------------------------------------------------------------------


			//-----------------CALCULATE THE NEXT SINGLE MOVEMENT-----------------------------------------------------------------------

			if ((enemyX != (*g_sChar).m_cLocation.X || enemyY != (*g_sChar).m_cLocation.Y))
			{
				g_sEnemy[a].m_cLocation.X = enemyX;
				g_sEnemy[a].m_cLocation.Y = enemyY;
			}

			//-----------------CALCULATE THE NEXT SINGLE MOVEMENT-----------------------------------------------------------------------

		}
	}
}


