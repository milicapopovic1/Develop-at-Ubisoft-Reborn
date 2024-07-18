#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "..\app\app.h"
using namespace Constants;
class PlayerMovement;
class Npc;
class Enemy;

class Player {
private:
	int health;
	int score = 0;
	PlayerMovement* movement;
	CSimpleSprite* sprite;
	bool npcHeld = false;

public:
	Player();
	~Player();
	void updateMovement();
	void draw();
	bool canStep(float x, float y);
	void addScore();
	void restart();

public:
	int getHealth() { return health;}
	CSimpleSprite* getSprite() { return sprite;}
	bool getNpcHeld() { return npcHeld;}
	int getScore() { return score;}
	void resetScore() { score = 0;};
	void setNpcHeld(bool heldvar) { npcHeld = heldvar;}
	void setHealth(int healthvar) { health = healthvar;}
};
#endif
