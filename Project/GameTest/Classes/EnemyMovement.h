#ifndef _ENEMYMOVEMENT_H_
#define _ENEMYMOVEMENT_H_
#include "..\app\app.h"
using namespace std;
using namespace Constants;
class Player;
class Enemy;

class EnemyMovement {
private:
	int backupX;
	int backupY;
	Enemy* enemy;
public:
	EnemyMovement(Enemy* enemy);
	bool updateMovement();
};
#endif
