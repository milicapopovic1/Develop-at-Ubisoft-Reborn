#ifndef _WOOD_H_
#define _WOOD_H_
#include "..\app\app.h"
using namespace Constants;
class Field;

class Wood : public Field {
public:
	Wood() : Field(BMP_PATH_WOOD, BMP_COLUMNS_WOOD, BMP_ROWS_WOOD) { SetFrame(BMP_INDEX_WOOD);}
	Wood(Field* field) : Field(field, BMP_PATH_WOOD, BMP_COLUMNS_WOOD, BMP_ROWS_WOOD) { SetFrame(BMP_INDEX_WOOD);}
	int damage() { return 0;}
	bool isPassableGeneral() { return false;}
	bool isPassableForPlayer() { return false;}
};
#endif