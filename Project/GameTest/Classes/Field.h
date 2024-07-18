#ifndef _FIELD_H_
#define _FIELD_H_
#include "..\app\app.h"
using namespace Constants;

class CSimpleSprite;

class Field : public CSimpleSprite
{
protected:
	Field(const char* fileName, unsigned int nColumns, unsigned int nRows);
	Field(Field* field, const char* fileName, unsigned int nColumns, unsigned int nRows);

public:
	void Draw();

public:
	virtual int damage() = 0;
	virtual bool isPassableGeneral() = 0;
	virtual bool isPassableForPlayer() = 0;
};
#endif