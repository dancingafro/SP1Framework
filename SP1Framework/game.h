#ifndef _GAME_H
#define _GAME_H

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33

#include "Framework\timer.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "points.h"
#include <queue>
#include <cmath>

using namespace std;

const int width = 80;
const int height = 35;
const int totalEnemy = 22;
const int totalTele = 80;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_BACK,
	K_W,
	K_A,
	K_S,
	K_D,
	K_RETURN,
	K_1,
	K_2,
	K_3,
	K_COUNT // MUST BE LAST IN ENUM!!!
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_LOADING,
	S_INSTRUCTION,
	S_INSTRUCTLOAD,
	S_SPLASHSCREEN,
	S_GAMELOAD,
	S_GAME,
	S_GAMEOVER,
	S_OVERLOAD,
    S_COUNT
};
enum MAPDATA
{
	WALL,
	ROAD,
	EXIT,
	DOOR,
	TELE,
	NOTHING
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
	COORD m_cLastSeenLocation;
	COORD m_cAttackLocation;
	COORD m_cAttackRenderLocation;
	bool  m_bActive;
	bool  m_haveKey;
    bool  m_bAttacking;
	bool  m_seePlayer;
	bool  m_bCanAttack;
	bool  m_bCanExplode;
	int   m_directionFacing = 1;
	int   m_idirectionAIMove;
	bool  m_bRecentlyAttacked;
	unsigned int m_iHitpoints;
	unsigned int m_iDamage;
	unsigned int m_iKills;
	double m_dAttackRate;
	double m_dExplosionTime;
	double m_dTimeSinceLastAIMove = 0;
	double m_dAttackRenderTime;
	double m_dNextAttackTime;
};

struct SGameObj
{
	COORD m_cLocation;
	bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory
void Splashscreenloading();
void splashScreenWait();    // waits for time to pass in splash screen
void instructscreen();
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderloadinginstruct();
void renderGameover();
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void loadfile(string mapname, int *numTele, int *numEnemy, MAPDATA(&MapData)[height][width], SGameObj *g_sKey, SGameObj g_sDoor[], SGameChar g_sEnemy[], SGameObj g_sTeleporters[], char(&map)[height][width], char(&fog)[height][width]);
void gameLoad(int level);
void renderEnemy();
void enemyBehaviour(SGameChar *g_sEnemy);
void randomMovement(double g_dElapsedTime, SGameChar *g_sEnemy, MAPDATA(&MapData)[height][width]);
void renderObject();
void checkCharacterAttack();
void renderCharacterAttack();
bool collision(int x, int y, MAPDATA(&MapData)[height][width]);
void breadthFirstSearch(double g_dElapsedTime, SGameChar *g_sEnemy, SGameChar *g_sChar, MAPDATA(&MapData)[height][width]);
bool lineOfSight(SGameChar *g_sEnemy, SGameChar *g_sChar, MAPDATA(&MapData)[height][width]);
int  playerToEnemyDistance(int a, SGameChar g_sEnemy[], SGameChar *g_sChar);
void FOW(int x, int y, char(&map)[height][width], char(&fog)[height][width]);
void ResetAllData(int *numTele, int *numEnemy, SGameObj *g_sKey, SGameChar g_sEnemy[], SGameObj g_sDoor[], SGameObj g_sTeleporters[],  MAPDATA (&MapData)[height][width], char(&map)[height][width], char(&fog)[height][width]);
void instructionloading();
bool PositionCollision(int x1, int y1, int x2, int y2);
void menu(COORD c);
void overloading();
void overscreen();
void govermenu(COORD c);

#endif