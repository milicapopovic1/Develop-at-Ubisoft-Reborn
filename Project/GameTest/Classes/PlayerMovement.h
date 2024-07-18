#ifndef _PLAYERMOVEMENT_H_
#define _PLAYERMOVEMENT_H_
#include "..\app\app.h"
class Player;
class Npc;
class Enemy;

class PlayerMovement {
private:
	bool isOnFieldWithoutDamage;

public:
	PlayerMovement() { isOnFieldWithoutDamage = true;}
	void updateMovement(Player* p, Npc* npc, Enemy** enemies);

public:
	bool getIsOnFieldWithoutDamage() { return isOnFieldWithoutDamage;}
	void setIsOnFieldWithoutDamage(bool isOnFieldWithoutDamagevar) { isOnFieldWithoutDamage = isOnFieldWithoutDamagevar;}
};
#endif
