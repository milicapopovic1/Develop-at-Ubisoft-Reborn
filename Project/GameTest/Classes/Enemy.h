#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "..\app\app.h"
using namespace Constants;
class EnemyMovement;
class Characters;

class Enemy {
private:
	EnemyMovement* movement;
	CSimpleSprite* sprite;
	bool isRandomType;

public:
	Enemy(bool isRandomTypeSet);
	~Enemy();
	bool updateMovement();
	void draw();
	void spawnRandom();
	bool isOverlayed(float x, float y, float width, float height, float scale);

public:
	CSimpleSprite* getSprite() { return sprite;}
	bool getIsRandomType() { return isRandomType;}
};
#endif
