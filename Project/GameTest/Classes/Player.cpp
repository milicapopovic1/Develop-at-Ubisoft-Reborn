#include "stdafx.h"

Player::Player() {
	sprite = App::CreateSprite(BMP_PATH_PLAYER, BMP_COLUMNS_PLAYER, BMP_ROWS_PLAYER);
	health = PLAYER_START_HEALTH;
	movement = new PlayerMovement();
	sprite->SetPosition(PLAYER_START_X, PLAYER_START_Y);
	sprite->SetScale(SCALE_PLAYER);
}

Player::~Player() {
	delete sprite;
	delete movement;
}

void Player::updateMovement() {
	movement->updateMovement(this, Characters::getNpc(), Characters::getEnemies());
}

void Player::draw() {
	sprite->Draw();
}
void Player::restart() {
	health = PLAYER_START_HEALTH;
	sprite->SetPosition(PLAYER_START_X, PLAYER_START_Y);
	if (score > General::getBestScore()) General::setBestScore(score);
	resetScore();
	npcHeld = false;
}

bool Player::canStep(float x,float y) {
	Map* map = Map::getInstance();
	bool canStepUp = map->getField(x, y + sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	bool canStepDown = map->getField(x, y - sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	bool canStepRight = map->getField(x + sprite->GetWidth() * SCALE_PLAYER / 2, y )->isPassableForPlayer();
	bool canStepLeft = map->getField(x - sprite->GetWidth() * SCALE_PLAYER / 2, y )->isPassableForPlayer();
	bool canStepRightUp = map->getField(x + sprite->GetWidth() * SCALE_PLAYER / 2, y + sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	bool canStepLeftDown = map->getField(x - sprite->GetWidth() * SCALE_PLAYER / 2, y - sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	bool canStepRightDown = map->getField(x + sprite->GetWidth() * SCALE_PLAYER / 2, y - sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	bool canStepLeftUp = map->getField(x - sprite->GetWidth() * SCALE_PLAYER / 2, y + sprite->GetHeight() * SCALE_PLAYER / 2)->isPassableForPlayer();
	return canStepUp && canStepDown && canStepRight && canStepLeft && canStepRightUp && canStepLeftDown && canStepRightDown && canStepLeftUp;
}

void Player::addScore() {
	score += 1;
}
