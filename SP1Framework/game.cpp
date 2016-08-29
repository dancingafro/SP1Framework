// This is the main file for the game logic and function
//
//
#include "game.h"

points* playerPoints = new points();

double  g_dElapsedTime;
double  g_dDeltaTime;
double  g_dCharNextAttackTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameObj	g_sKey;
SGameObj	g_sDoor[2];
SGameObj	g_sTeleporters[totalTele];
SGameChar   g_sChar;
SGameChar   g_sEnemy[totalEnemy];
EGAMESTATES g_eGameState;
int level = 1;
char map[height][width];
char fog[height][width];
int oldLocationx;
int oldLocationy;
double  g_dBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once
double govertime;
int numTele = 0;
int numEnemy = 0;
int g_menuselect = 0;
int goverselect = 0;
int enemyatttime = 0;
// Console object
Console g_Console(width, height, "Dungeon Explorer");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
	g_eGameState = S_LOADING;

	g_dCharNextAttackTime = 0.0;
	g_sChar.m_cAttackLocation = { 0, 0 };
	g_sChar.m_bAttacking = false;
	g_sChar.m_iHitpoints = 10;
	g_sChar.m_dAttackRate = 0.25;
	g_sChar.m_iKills = 0;

	oldLocationx = 0;
	oldLocationx = 0;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Bitstream Vera Sans");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------

void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------

void getInput( void )
{    
    g_abKeyPressed[K_UP]			= isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]			= isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]			= isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]			= isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]			= isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE]		= isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_BACK]			= isKeyPressed(VK_BACK);
	g_abKeyPressed[K_W]				= isKeyPressed(VK_W);
	g_abKeyPressed[K_A]				= isKeyPressed(VK_A);
	g_abKeyPressed[K_S]				= isKeyPressed(VK_S);
	g_abKeyPressed[K_D]				= isKeyPressed(VK_D);
	g_abKeyPressed[K_ESCAPE]		= isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_RETURN]		= isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_1]				= isKeyPressed(VK_1);
	g_abKeyPressed[K_2]				= isKeyPressed(VK_2); 
	g_abKeyPressed[K_3]             = isKeyPressed(VK_3);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------

void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
    switch (g_eGameState)
	{
		case S_LOADING: 
			Splashscreenloading();
			break;
        case S_SPLASHSCREEN : 
			splashScreenWait(); // game logic for the splash screen
			break;
		case S_INSTRUCTLOAD:
			instructionloading();
			break;
		case S_INSTRUCTION:
			instructscreen();
			break;
		case S_GAMELOAD:
			ResetAllData(&numTele, &numEnemy, &g_sKey, g_sEnemy, g_sDoor, g_sTeleporters, map, fog);
			gameLoad(level);
			break;
        case S_GAME: 
			gameplay(); // gameplay logic when we are in the game
            break;
		case S_GAMEOVER:
			overscreen();
			break;
		case S_OVERLOAD:
			overloading();
			break;
    }
	//PlaySound(NULL, 0, 0);
	
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
	{
        case S_SPLASHSCREEN: 
			renderSplashScreen();
            break;
		case S_INSTRUCTION:
			renderloadinginstruct();
			break;
        case S_GAME: 
			renderGame();
            break;
		case S_GAMEOVER:
			renderGameover();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void Splashscreenloading()
{
	loadfile("Splashscreen.txt", &numTele, &numEnemy, &g_sKey, g_sDoor, g_sEnemy, g_sTeleporters,map,fog);
	g_eGameState = S_SPLASHSCREEN;
}

void instructionloading()
{
	loadfile("instructions.txt", &numTele, &numEnemy, &g_sKey, g_sDoor, g_sEnemy, g_sTeleporters, map, fog);
	g_eGameState = S_INSTRUCTION;
}

void overloading()
{
	loadfile("gameover.txt", &numTele, &numEnemy, &g_sKey, g_sDoor, g_sEnemy, g_sTeleporters, map, fog);
	g_eGameState = S_GAMEOVER;
}

void gameLoad(int level)
{
	switch (level)
	{
	case 1:
		loadfile("maze2.txt", &numTele, &numEnemy, &g_sKey, g_sDoor, g_sEnemy, g_sTeleporters, map, fog);
		g_sChar.m_cLocation.X = 2;
		g_sChar.m_cLocation.Y = 2;
		break;
	case 2:
		loadfile("maze3.txt", &numTele, &numEnemy, &g_sKey, g_sDoor, g_sEnemy, g_sTeleporters, map, fog);
		g_sChar.m_cLocation.X = 2;
		g_sChar.m_cLocation.Y = 2;
		break;
	default:
		break;
	}
	g_eGameState = S_GAME;
}

void gameplay()			// gameplay logic
{
                        // sound can be played here too.
	processUserInput();// checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	// sound can be played here too.
	if (oldLocationx != g_sChar.m_cLocation.X || oldLocationy != g_sChar.m_cLocation.Y)
	{
		oldLocationx = g_sChar.m_cLocation.X;
		oldLocationy = g_sChar.m_cLocation.Y;
		FOW(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y, map, fog);
	}

	for (int i = 0; i < numEnemy; i++)
	{
		if (g_sEnemy[i].m_bActive)
		{
			enemyBehaviour();
		}
	}
}

void moveCharacter()
{
    bool bSomethingHappened = false;
	bool noEnemyNearby = true;
	
    if (g_dBounceTime > g_dElapsedTime)
        return;

	if (g_abKeyPressed[K_2])
	{
		g_sChar.m_iHitpoints--;
		bSomethingHappened = true;
	}
	if (!g_sChar.m_bAttacking)
	{
		if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
		{
			if (collision(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y - 1))
			{
				for (int a = 0; a < numEnemy; a++)
				{
					if (gotPlayerCollision(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y - 1, g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y) && g_sEnemy[a].m_bActive)
					{
						noEnemyNearby = false;
						break;
					}
				}
				if (noEnemyNearby)
				{
					g_sChar.m_cLocation.Y--;
				}
				noEnemyNearby = true;
				
				if (g_sChar.m_cLocation.Y == g_sDoor[1].m_cLocation.Y && g_sChar.m_cLocation.X == g_sDoor[1].m_cLocation.X)
				{
					level++;
					g_eGameState = S_GAMELOAD;
				}
				if (g_sChar.m_cLocation.Y == g_sKey.m_cLocation.Y && g_sChar.m_cLocation.X == g_sKey.m_cLocation.X && g_sKey.m_bActive)
				{
					map[g_sDoor[0].m_cLocation.Y][g_sDoor[0].m_cLocation.X] = '.';
					g_sKey.m_bActive = false;
					playerPoints->increasePoints();
				}
			}
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
		{
			if (collision(g_sChar.m_cLocation.X-1, g_sChar.m_cLocation.Y))
			{
				
				for (int a = 0; a < numEnemy; a++)
				{
					if (gotPlayerCollision(g_sChar.m_cLocation.X - 1, g_sChar.m_cLocation.Y, g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y) && g_sEnemy[a].m_bActive)
					{
						noEnemyNearby = false;
						break;
					}
				}
				if (noEnemyNearby)
				{
					g_sChar.m_cLocation.X--;
				}
				noEnemyNearby = true;
				
				if (g_sChar.m_cLocation.Y == g_sDoor[1].m_cLocation.Y && g_sChar.m_cLocation.X == g_sDoor[1].m_cLocation.X)
				{
					level++;
					g_eGameState = S_GAMELOAD;
				}
				if (g_sChar.m_cLocation.Y == g_sKey.m_cLocation.Y && g_sChar.m_cLocation.X == g_sKey.m_cLocation.X && g_sKey.m_bActive)
				{
					map[g_sDoor[0].m_cLocation.Y][g_sDoor[0].m_cLocation.X] = '.';
					g_sKey.m_bActive = false;
					playerPoints->increasePoints();
				}
			}
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
		{
			if (collision(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y+1))
			{
				
				for (int a = 0; a < numEnemy; a++)
				{
					if (gotPlayerCollision(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y + 1, g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y) && g_sEnemy[a].m_bActive)
					{
						noEnemyNearby = false;
						break;
					}
				}
				if (noEnemyNearby)
				{
					g_sChar.m_cLocation.Y++;
				}
				noEnemyNearby = true;
				
				if (g_sChar.m_cLocation.Y == g_sDoor[1].m_cLocation.Y && g_sChar.m_cLocation.X == g_sDoor[1].m_cLocation.X)
				{
					level++;
					g_eGameState = S_GAMELOAD;
				}
				if (g_sChar.m_cLocation.Y == g_sKey.m_cLocation.Y && g_sChar.m_cLocation.X == g_sKey.m_cLocation.X && g_sKey.m_bActive)
				{
					map[g_sDoor[0].m_cLocation.Y][g_sDoor[0].m_cLocation.X] = '.';
					g_sKey.m_bActive = false;
					playerPoints->increasePoints();
				}
			}
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
		{
			if (collision(g_sChar.m_cLocation.X + 1, g_sChar.m_cLocation.Y))
			{
				for (int a = 0; a < numEnemy; a++)
				{
					if (gotPlayerCollision(g_sChar.m_cLocation.X + 1, g_sChar.m_cLocation.Y, g_sEnemy[a].m_cLocation.X, g_sEnemy[a].m_cLocation.Y) && g_sEnemy[a].m_bActive)
					{
						noEnemyNearby = false;
						break;
					}
				}
				if (noEnemyNearby)
				{
					g_sChar.m_cLocation.X++;
				}
				noEnemyNearby = true;
				
				if (g_sChar.m_cLocation.Y == g_sDoor[1].m_cLocation.Y && g_sChar.m_cLocation.X == g_sDoor[1].m_cLocation.X)
				{
					level++;
					g_eGameState = S_GAMELOAD;
				}
				if (g_sChar.m_cLocation.Y == g_sKey.m_cLocation.Y && g_sChar.m_cLocation.X == g_sKey.m_cLocation.X && g_sKey.m_bActive)
				{
					map[g_sDoor[0].m_cLocation.Y][g_sDoor[0].m_cLocation.X] = '.';
					g_sKey.m_bActive = false;
					playerPoints->increasePoints();
				}
			}
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			for (int i = 0; i<numTele; i++)
			{
				if (g_sChar.m_cLocation.Y == g_sTeleporters[i].m_cLocation.Y && g_sChar.m_cLocation.X == g_sTeleporters[i].m_cLocation.X)
				{
					int randNum = 0;
					while (true)
					{
						float frandNum = (rand() % numTele);
						if (frandNum == i)
						{
							continue;
						}
						
						randNum = frandNum;
						break;
					}
					g_sChar.m_cLocation.Y = g_sTeleporters[randNum].m_cLocation.Y;
					g_sChar.m_cLocation.X = g_sTeleporters[randNum].m_cLocation.X;
					break;
				}
			}
			bSomethingHappened = true;
		}
	}
    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.15; // 125ms should be enough
    }
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;
	if (g_abKeyPressed[K_1])
	{
		map[g_sDoor[1].m_cLocation.Y][g_sDoor[1].m_cLocation.X] = 'E';
		for (int i = 0; i < numEnemy; i++)
		{
			g_sEnemy[i].m_bActive = false;
		}
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer();
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();

	c.X = 20;
	c.Y = 1;
	string line;
	for (int y = 0; y < height; y++)
	{
		line = map[y];
		g_Console.writeToBuffer(c,line );
		c.Y++;
	}
	
	menu(c);
}

void renderGameover()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 12;
	c.Y = 5;
	ifstream file;
	string line;
	file.open("gameover.txt");

	while (!file.eof())
	{
		getline(file, line);
		g_Console.writeToBuffer(c, line);
		c.Y++;	
	}
	file.close();
	govermenu(c);
}

void menu(COORD c)
{
	c.X = 27;
	c.Y = 15;
	g_Console.writeToBuffer(c, "Press <Enter> to select.", 0x0B);
	c.X = 34;
	c.Y = 17;
	g_Console.writeToBuffer(c, "Start Game");
	c.X = 33;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Instructions");
	if (g_abKeyPressed[K_DOWN])
		g_menuselect = 1;
	if (g_menuselect == 1 && g_abKeyPressed[K_UP])
		g_menuselect = 0;
	if (g_menuselect == 0)
	{
		c.X = 34;
		c.Y = 17;
		g_Console.writeToBuffer(c, "Start Game", 0xF0);
	}
	if (g_menuselect == 1)
	{
		c.X = 33;
		c.Y = 18;
		g_Console.writeToBuffer(c, "Instructions", 0xF0);
	}
}

void govermenu(COORD c)
{
	c.X = 27;
	c.Y = 15;
	g_Console.writeToBuffer(c, "Press <Enter> to select.", 0x0B);
	c.X = 34;
	c.Y = 17;
	g_Console.writeToBuffer(c, "Main Menu");
	c.X = 34;
	c.Y = 18;
	g_Console.writeToBuffer(c, "Quit Game");
	if (g_abKeyPressed[K_DOWN])
		goverselect = 1;
	if (goverselect == 1 && g_abKeyPressed[K_UP])
		goverselect = 0;
	if (goverselect == 0)
	{
		c.X = 34;
		c.Y = 17;
		g_Console.writeToBuffer(c, "Main Menu", 0xF0);

	}
	if (goverselect == 1)
	{
		c.X = 34;
		c.Y = 18;
		g_Console.writeToBuffer(c, "Quit Game", 0xF0);
	}
	if (goverselect == 0)
	{
		g_eGameState = S_LOADING;

		g_dCharNextAttackTime = 0.0;
		g_sChar.m_cAttackLocation = { 0, 0 };
		g_sChar.m_bAttacking = false;
		g_sChar.m_iHitpoints = 10;
		g_sChar.m_dAttackRate = 0.25;
		g_sChar.m_iKills = 0;
	}
	else if (goverselect == 1)
		g_bQuitGame = true;
}

void renderloadinginstruct()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();

	c.X = 20;
	c.Y = 1;
	string line;
	for (int y = 0; y < height; y++)
	{
		line = map[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}

void splashScreenWait()
{
	renderSplashScreen();
	if (g_dElapsedTime < govertime)
		return;
	if (g_abKeyPressed[K_RETURN])
	{
		if(g_menuselect == 0)
		g_eGameState = S_GAMELOAD;
		else if (g_menuselect == 1)
		g_eGameState = S_INSTRUCTLOAD;
	}
}

//void overscreen()
//{
//	if (g_abKeyPressed[K_RETURN])
//	{
//		govertime = g_dElapsedTime + 0.5;
//		if (goverselect == 0) 
//		{
//			g_eGameState = S_LOADING;
//
//			g_dCharNextAttackTime = 0.0;
//			g_sChar.m_cAttackLocation = { 0, 0 };
//			g_sChar.m_bAttacking = false;
//			g_sChar.m_iHitpoints = 10;
//			g_sChar.m_dAttackRate = 0.25;
//			g_sChar.m_iKills = 0;
//		}
//		else if (goverselect == 1)
//			g_bQuitGame = true;
//	}
//}

void instructscreen()
{
	if (g_abKeyPressed[K_BACK])
	{
		g_eGameState = S_GAMELOAD;
	}
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderObject();
	renderCharacter();  // renders the character into the buffer
	renderEnemy();		// renders an enemy into the buffer
	checkCharacterAttack();
	renderCharacterAttack();
	renderHUD(&g_sChar, &g_Console);
}

void renderMap()
{
	COORD c = g_Console.getConsoleSize();

	c.X = 0;
	c.Y = 0;
	string line;
	for (int y = 0; y < height; y++)
	{
		line = fog[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;			
	}
}
	
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0A;
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)48, charColor);
}

void renderEnemy()
{	
	for (int i = 0; i < numEnemy; i++)
	{
		if (fog[g_sEnemy[i].m_cLocation.Y][g_sEnemy[i].m_cLocation.X]!=' ')
		{
			if (g_sEnemy[i].m_bActive)
			{
				g_Console.writeToBuffer(g_sEnemy[i].m_cLocation, "C", 0x07);
			}
		}
		eCheckForDamage( &g_Console, &g_sEnemy[i], &g_sChar, &g_dElapsedTime);
	}
}

void enemyatt(COORD a, COORD b)
{
	if (((a.X == b.X + 1) && (a.Y == b.Y)) || ((a.X == b.X - 1) && (a.Y == b.Y)) || ((a.Y == b.Y + 1) && (a.X == b.X)) || ((a.Y == b.Y - 1) && (a.X == b.X)))
	{
		while (g_dElapsedTime > enemyatttime + 1)
		{
			g_sChar.m_iHitpoints--;
			enemyatttime = (int)g_dElapsedTime;
		}
	}
}

void renderObject()
{
	if (fog[g_sKey.m_cLocation.Y][g_sKey.m_cLocation.X] != ' ')
	{
		if (g_sKey.m_bActive)
		{
			g_Console.writeToBuffer(g_sKey.m_cLocation, (char)254);
		}
	}
}

void enemyBehaviour()
{
	for (int i = 0; i < numEnemy; i++)
	{
		enemyatt(g_sChar.m_cLocation, g_sEnemy[i].m_cLocation);
	}

	randomMovement(&numEnemy,&g_dElapsedTime, g_sEnemy);
	breadthFirstSearch(&g_dElapsedTime, &numEnemy, g_sEnemy, &g_sChar);
	for (int a = 0; a < numEnemy; a++)
	{
		if (lineOfSight(a, g_sEnemy, &g_sChar, map))
			breadthFirstSearch(&g_dElapsedTime, &numEnemy, g_sEnemy, &g_sChar);
	}
}

void checkCharacterAttack()
{
	bool bSomethingHappened = false;
	if (g_sChar.m_bAttacking || g_dCharNextAttackTime > g_dElapsedTime) // (N) If player is launching or next attack time has not come
	{
		g_sChar.m_cAttackLocation = { 0,0 };
		g_sChar.m_bCanAttack = false;
	}
	// (N) If player is not holding down attack keys + attack has already launched + next attack time has passed
	else if (!g_sChar.m_bAttacking && g_dCharNextAttackTime <= g_dElapsedTime && (g_abKeyPressed[K_UP] + g_abKeyPressed[K_LEFT] + g_abKeyPressed[K_DOWN] + g_abKeyPressed[K_RIGHT]) == false)
	{
		g_sChar.m_bCanAttack = true;
	}
	if (g_sChar.m_bCanAttack)
	{
		if (g_abKeyPressed[K_UP])
		{
			setAttackUp( &g_sChar );
			launchPlayerAttack(&g_Console, &g_sChar, &g_sEnemy[totalEnemy], &g_dCharNextAttackTime, &g_dElapsedTime, &numEnemy, &bSomethingHappened);
		}
		if (g_abKeyPressed[K_LEFT])
		{
			setAttackLeft( &g_sChar );
			launchPlayerAttack(&g_Console, &g_sChar, &g_sEnemy[totalEnemy], &g_dCharNextAttackTime, &g_dElapsedTime, &numEnemy, &bSomethingHappened);
		}
		if (g_abKeyPressed[K_DOWN])
		{
			setAttackDown( &g_sChar );
			launchPlayerAttack(&g_Console, &g_sChar, &g_sEnemy[totalEnemy], &g_dCharNextAttackTime, &g_dElapsedTime, &numEnemy, &bSomethingHappened);
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			setAttackRight( &g_sChar );
			launchPlayerAttack(&g_Console, &g_sChar, &g_sEnemy[totalEnemy], &g_dCharNextAttackTime, &g_dElapsedTime, &numEnemy, &bSomethingHappened);
		}
	}
}

void renderCharacterAttack()
{
	if (g_sChar.m_bAttacking)
	{
		g_Console.writeToBuffer(g_sChar.m_cAttackLocation, (char)42, 0x0A);
		g_sChar.m_bAttacking = false;
	}
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    ostringstream ss;
    ss << fixed << setprecision(3);

    // displays the elapsed time
    ss.str("");
	ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

	ss.str("");
	ss << "Points: "<<playerPoints->getPoints();
	c.X = 36;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}