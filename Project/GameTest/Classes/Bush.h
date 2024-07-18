#ifndef _BUSH_H_
#define _BUSH_H_
#include "..\app\app.h"
using namespace Constants;
class Field;

class Bush : public Field {
public:
	Bush() : Field(BMP_PATH_BUSH, BMP_COLUMNS_BUSH, BMP_ROWS_BUSH) { SetFrame(BMP_INDEX_BUSH);}
	Bush(Field* field) : Field(field, BMP_PATH_BUSH, BMP_COLUMNS_BUSH, BMP_ROWS_BUSH) { SetFrame(BMP_INDEX_BUSH);}
	int damage() { return 5;}
	bool isPassableGeneral() { return false;}
	bool isPassableForPlayer() { return true;}
};
#endif