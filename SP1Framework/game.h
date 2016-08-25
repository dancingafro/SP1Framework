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
#include "points.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <queue>
#include <string>

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
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
	COORD m_cAttackLocation;
	bool  m_bActive;
	bool  m_haveKey;
    bool  m_bAttacking;
	bool  m_seePlayer;
	bool  m_bCanAttack;
	bool  m_bCanExplode;
	unsigned int m_iHitpoints;
	unsigned int m_iDamage;
	unsigned int m_iKills = 0;
	double m_dAttackRate;
	double m_dExplosionTime;
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
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void loadfile(string mapname, int *numTele, int *numEnemy, SGameObj *g_sKey, SGameObj g_sDoor[], SGameChar g_sEnemy[], SGameObj g_sTeleporters[]);
void gameLoad(int level);
void renderEnemy();
void enemyBehaviour();
void randomMovement(int *numEnemy, double *g_dElapsedTime, SGameChar g_sEnemy[]);
void renderObject();
void checkCharacterAttack();
void renderCharacterAttack();
bool collision(int x, int y);
void breadthFirstSearch(double *g_dElapsedTime, int *numEnemy, SGameChar g_sEnemy[], SGameChar *g_sChar);
bool EnemyIsAttacked(int x1, int x2, int y1, int y2);
//bool lineOfSight();
void FOW(int x, int y);
void checkUp( SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened );
void checkLeft( SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened );
void checkDown( SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened );
void checkRight( SGameChar *g_sChar, double *g_dCharNextAttackTime, double *g_dElapsedTime, bool *bSomethingHappened );
void ResetAllData(int *numTele, int *numEnemy, SGameObj *g_sKey, SGameChar g_sEnemy[], SGameObj g_sDoor[], SGameObj g_sTeleporters[]);
void instructionloading();
void renderHUD();
void menu(COORD c);
void initializeEnemy(SGameChar *g_sEnemy, unsigned int row, unsigned int col);
void renderExplosion(Console *g_Console, short cX, short cY);


#endif