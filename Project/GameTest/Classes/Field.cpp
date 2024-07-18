#include "stdafx.h"

Field::Field(const char* fileName, unsigned int nColumns, unsigned int nRows) : CSimpleSprite(fileName, nColumns, nRows) {
	SetScale(SCALE_FIELD);
}

Field::Field(Field* field,const char* fileName, unsigned int nColumns, unsigned int nRows) : Field(fileName, nColumns, nRows) {
	float x, y;
	field->GetPosition(x, y);
	SetPosition(x, y);
}

void Field::Draw() {
	CSimpleSprite::Draw();
}

