#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_
#include "..\app\app.h"
using namespace std;
using namespace Constants;
class Player;
class Enemy;

class Characters {
private:
	static Player* player;
	static Enemy* enemies[NUMBER_OF_ENEMIES];
	static Npc* npc;

public:
	static void initializeObjects();
	static void updateObjects();
	static void drawObjects();
	static void deleteObjects();
	static void restartObjects();

public:
	static Npc* getNpc() { return npc;}
	static Player* getPlayer() { return player;}
	static Enemy** getEnemies() { return enemies;}
};
#endif