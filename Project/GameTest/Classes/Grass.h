#ifndef _GRASS_H_
#define _GRASS_H_
#include "..\app\app.h"
using namespace Constants;
class Field;

class Grass : public Field {
public:
	Grass() : Field(BMP_PATH_GRASS, BMP_COLUMNS_GRASS, BMP_ROWS_GRASS) { SetFrame(BMP_INDEX_GRASS);}
	Grass(Field* field) : Field(field, BMP_PATH_GRASS, BMP_COLUMNS_GRASS, BMP_ROWS_GRASS) { SetFrame(BMP_INDEX_GRASS);}
	int damage() { return 0;}
	bool isPassableGeneral() { return true;}
	bool isPassableForPlayer() { return true;}
};
#endif