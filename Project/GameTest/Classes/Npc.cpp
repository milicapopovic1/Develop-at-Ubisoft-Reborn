#include "stdafx.h"

Npc::Npc() {
	sprite = App::CreateSprite(BMP_PATH_NPC, BMP_COLUMNS_NPC, BMP_COLUMNS_NPC);
	spawnRandom();
	sprite->SetScale(SCALE_NPC);
}

Npc::~Npc() {
	delete sprite;
}

void Npc::draw() {
	sprite->Draw();
}

bool Npc::IsOverlayed(float x, float y, float width, float height, float scale) {
	float xs, ys;
	sprite->GetPosition(xs, ys);
	float xDiff = x > xs ? x - xs : xs - x;
	float yDiff = y > ys ? y - ys : ys - y;
	float maxDistance = sprite->GetHeight() / 2 * sprite->GetScale() + height / 2 * scale;
	if (xDiff < maxDistance && yDiff < maxDistance) return true;
	return false;
}

void Npc::spawnRandom() {
	bool found = false;
	while(true){
		int x = MAP_X_OFFSET + (BMP_WIDTH_FIELD * SCALE_FIELD) / 2 + RANDOMINT(0, COLUMN_NUMBER - 2) * BMP_WIDTH_FIELD * SCALE_FIELD;
		int y = MAP_Y_OFFSET + (BMP_HEIGHT_FIELD * SCALE_FIELD) / 2 + RANDOMINT(0, ROW_NUMBER - 2) * BMP_HEIGHT_FIELD * SCALE_FIELD;
		if (Map::getInstance()->getField(x, y)->isPassableGeneral()) {
			sprite->SetPosition(x, y);
			return;
		}
	}
}