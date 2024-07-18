#ifndef _NPC_H_
#define _NPC_H_
#include "..\app\app.h"
using namespace Constants;
class CSimpleSprite;

class Npc {
private:
	CSimpleSprite* sprite;

public:
	Npc();
	~Npc();
	void draw();
	bool IsOverlayed(float x,float y,float width, float height, float scale);
	void spawnRandom();

public:
	CSimpleSprite* getSprite() { return sprite;}
};
#endif
