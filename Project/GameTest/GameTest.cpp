#include "stdafx.h"
#include <windows.h> 
#include <math.h>
#include <string>
#include "app\app.h"

CSimpleSprite* keyboardSprite;
CSimpleSprite* letterCSprite;

void Init() {
	Characters::initializeObjects();
	keyboardSprite = App::CreateSprite(BMP_PATH_KEYBOARD, 1, 1);
	keyboardSprite->SetPosition(70, 200);
	keyboardSprite->SetScale(0.06f);
	letterCSprite = App::CreateSprite(BMP_PATH_C, 1, 1);
	letterCSprite->SetPosition(50, 130);
	letterCSprite->SetScale(0.06f);
}

void Update(float deltaTime) {
	if (!General::gameOver()) {
		Characters::updateObjects();
		General::decrementTime();
	}
	else General::waitForUserInput();
}

void Render() {	
	int score = Characters::getPlayer()->getScore();
	if (!General::gameOver()) {
		Map::getInstance()->Draw();
		Characters::drawObjects();

		std::string timeString = "Time: " + std::to_string(General::getTime());
		App::Print(30, 625, timeString.c_str());

		std::string playerHealthString = "Player health: " + std::to_string(Characters::getPlayer()->getHealth());
		if (General::damageWarning > 0) { 
			General::damageWarning--; 
			App::Print(30, 600, playerHealthString.c_str(), 1.0f, 0.0f, 0.0f);
		} else App::Print(30, 600, playerHealthString.c_str());

		std::string scoreString = "Player score: " + std::to_string(score);
		if (General::scoreGainWarning > 0) {
			General::scoreGainWarning--;
			App::Print(30, 575, scoreString.c_str(), 0.0f, 1.0f, 0.0f);
		}
		else App::Print(30, 575, scoreString.c_str());

		std::string bestScoreString = "Best score: " + std::to_string(General::getBestScore());
		App::Print(30, 700, bestScoreString.c_str());

		keyboardSprite->Draw();
		std::string instruction = "to move";
		App::Print(130, 180, instruction.c_str());
		letterCSprite->Draw();
		instruction = "to carry chicken";
		App::Print(80, 120, instruction.c_str());
	} else {
		std::string gameScoreString = "GAME SCORE " + std::to_string(score);
		App::Print(400, 400, gameScoreString.c_str());

		std::string restartText = "PRESS R TO RESTART";
		App::Print(360, 200, restartText.c_str());
	}
}

void Shutdown() {
	Map::deleteMap();
	Characters::deleteObjects();
}
