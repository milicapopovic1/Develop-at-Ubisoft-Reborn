#include "stdafx.h"

Enemy::Enemy(bool isRandomTypeSet) {
	isRandomType = isRandomTypeSet;
	sprite = App::CreateSprite(isRandomTypeSet ? BMP_PATH_ENEMY_RANDOM: BMP_PATH_ENEMY, BMP_COLUMNS_ENEMY, BMP_ROWS_ENEMY);
	movement = new EnemyMovement(this);
	sprite->SetScale(SCALE_ENEMY);
	spawnRandom();
}

Enemy::~Enemy() {
	delete movement;
	delete sprite;
}

bool Enemy::updateMovement() {
	return movement->updateMovement();
}

void Enemy::draw() {
	sprite->Draw();
}

void Enemy::spawnRandom() {
	bool found = false;
	while (true) {
		int x = MAP_X_OFFSET + (BMP_WIDTH_FIELD * SCALE_FIELD) / 2 + RANDOMINT(0, (COLUMN_NUMBER - 1) / 2) * BMP_WIDTH_FIELD * SCALE_FIELD;
		int y = MAP_Y_OFFSET + (BMP_HEIGHT_FIELD * SCALE_FIELD) / 2 + RANDOMINT(0, ROW_NUMBER - 1) * BMP_HEIGHT_FIELD * SCALE_FIELD;
		if (Map::getInstance()->getField(x, y)->isPassableGeneral()) {
			sprite->SetPosition(x, y);
			return;
		}
	}
}

bool Enemy::isOverlayed(float x, float y, float width, float height, float scale) {
	float xs, ys;
	sprite->GetPosition(xs, ys);
	float xDiff = x > xs ? x - xs : xs - x;
	float yDiff = y > ys ? y - ys : ys - y;
	float maxDistance = sprite->GetHeight() / 2 * sprite->GetScale() + height / 2 * scale;
	if (xDiff < maxDistance && yDiff < maxDistance) return true;
	return false;
}