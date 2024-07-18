#ifndef _BATTERY_H_
#define _BATTERY_H_
#include "..\app\app.h"
using namespace Constants;
class Field;

class Battery : public Field {
public:
	Battery() : Field(BMP_PATH_BATTERY, BMP_COLUMNS_BATTERY, BMP_ROWS_BATTERY) { SetFrame(BMP_INDEX_BATTERY);}
	Battery(Field* field) : Field(field, BMP_PATH_BATTERY, BMP_COLUMNS_BATTERY, BMP_ROWS_BATTERY) { SetFrame(BMP_INDEX_BATTERY);}
	int damage() { return -1;}
	bool isPassableGeneral() { return true;}
	bool isPassableForPlayer() { return true;}
};
#endif
