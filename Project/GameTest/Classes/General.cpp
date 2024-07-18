#include "stdafx.h"

int General::time = START_TIME;

int General::bestScore = 0;

int General::damageWarning = 0;

int General::scoreGainWarning = 0;

int General::lastPressedButton = XINPUT_GAMEPAD_DPAD_UP;

bool General::shouldDecrement = false;

void General::waitForUserInput() {
	if (App::IsKeyPressed('R') && gameOver()) {
		restartTime();
		Map::getInstance()->restart();
		Characters::restartObjects();
		damageWarning = 0;
		scoreGainWarning = 0;
	}
}

void General::decrementTime() {
	if (shouldDecrement) {
		time--;
		if (time < 0) time = 0;
	}
	shouldDecrement = !shouldDecrement; //to calculate the real seconds, we decrease time every other time 
}

bool General::gameOver() {
	return timeEnded() || Characters::getPlayer()->getHealth() <= 0;
}

