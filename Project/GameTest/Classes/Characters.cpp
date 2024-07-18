#include "stdafx.h"

Player* Characters::player = nullptr;

Enemy* Characters::enemies[NUMBER_OF_ENEMIES] = {};

Npc* Characters::npc = nullptr;

void Characters::drawObjects() {
	player->draw();
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		enemies[i]->draw();
	}
	npc->draw();
}

void Characters::initializeObjects() {
	player = new Player();
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		enemies[i] = new Enemy(i % 2 == 0); //every second enemy is chasing a random point, others are chasing the player
	}
	npc = new Npc();
}

void Characters::updateObjects() {
	player->updateMovement();
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		if (enemies[i]->updateMovement()) { //if an enemy collides with the player
			General::setNullTime();
		}
	}
}

void Characters::deleteObjects() {
	delete player;
	for (size_t i = 0; i < NUMBER_OF_ENEMIES; i++) delete enemies[i];
	delete npc;
}

void Characters::restartObjects() {
	for (size_t i = 0; i < NUMBER_OF_ENEMIES; i++) enemies[i]->spawnRandom();
	npc->spawnRandom();
	player->restart();
}