#include "stdafx.h"

#define CHECK_BUTTON(a) (App::GetController().CheckButton(a, false))
#define CHECK_REGULAR_BUTTON(a) (CHECK_BUTTON(a) && (a == General::lastPressedButton || !CHECK_BUTTON(General::lastPressedButton)))

void PlayerMovement::updateMovement(Player* p, Npc* npc, Enemy** enemies) {
	CSimpleSprite* testSprite = p->getSprite();
	if (CHECK_REGULAR_BUTTON(XINPUT_GAMEPAD_DPAD_UP)) {
		float x, y;
		testSprite->GetPosition(x, y);
		y += STEP_SIZE_PLAYER;
		if(p->canStep(x,y)){
			testSprite->SetPosition(x, y);
		}
		General::lastPressedButton = XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (CHECK_REGULAR_BUTTON(XINPUT_GAMEPAD_DPAD_DOWN)) {
		float x, y;
		testSprite->GetPosition(x, y);
		y -= STEP_SIZE_PLAYER;
		if (p->canStep(x, y)) {
			testSprite->SetPosition(x, y);
		}
		General::lastPressedButton = XINPUT_GAMEPAD_DPAD_DOWN;
	}
	else if (CHECK_REGULAR_BUTTON(XINPUT_GAMEPAD_DPAD_LEFT)) {
		float x, y;
		testSprite->GetPosition(x, y);
		x -= STEP_SIZE_PLAYER;
		if (p->canStep(x, y)) {testSprite->SetPosition(x, y);
		}
		General::lastPressedButton = XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (CHECK_REGULAR_BUTTON(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		float x, y;
		testSprite->GetPosition(x, y);
		x += STEP_SIZE_PLAYER;
		if (p->canStep(x, y)) {
			testSprite->SetPosition(x, y);
		}
		General::lastPressedButton = XINPUT_GAMEPAD_DPAD_RIGHT;
	}
	if (App::IsKeyPressed('C')) { //to carry npc
		float x, y;
		testSprite->GetPosition(x, y);
		if (npc->IsOverlayed(x, y, testSprite->GetWidth(), testSprite->GetHeight(), SCALE_PLAYER) && !p->getNpcHeld()) {
			p->setNpcHeld(true);
			npc->getSprite()->SetPosition(x, y);
		} else if (npc->IsOverlayed(x, y, testSprite->GetWidth(), testSprite->GetHeight(), SCALE_PLAYER) && p->getNpcHeld()) {
			p->setNpcHeld(false);
			if (Map::getInstance()->getField(x, y)->damage() == DAMAGE_BATTERY) { //if we reached the battery
				p->addScore();
				General::scoreGainWarning = SCORE_GAIN_COUNTER;
				npc->spawnRandom();
				for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
					enemies[i]->spawnRandom();
				}
			}
		}
	}
	float x, y;
	testSprite->GetPosition(x, y);
	int damage = Map::getInstance()->getField(x, y)->damage();
	if (damage > 0 && getIsOnFieldWithoutDamage()) {
		p->setHealth(max(0, p->getHealth() - damage));
		setIsOnFieldWithoutDamage(false);
		General::damageWarning = DAMAGE_COUNTER;
	} else if (damage <= 0 && !getIsOnFieldWithoutDamage()) {
		setIsOnFieldWithoutDamage(true);
	}
}