#ifndef _GENERAL_H_
#define _GENERAL_H_
#include "..\app\app.h"
using namespace Constants;

class General {
private:
	static int time;
	static int bestScore;
	static bool shouldDecrement;

public:
	static int damageWarning;
	static int scoreGainWarning;
	static int lastPressedButton;
	static void waitForUserInput();
	static bool gameOver();
	static void decrementTime();

public:
	static void setNullTime() { time = 0;}
	static void restartTime() { time = START_TIME;}
	static int getBestScore() { return bestScore;}
	static void setBestScore(int bestScorevar) { bestScore = bestScorevar;}
	static int getTime() { return time / 30;}
	static bool timeEnded() { return time == 0;}
};
#endif