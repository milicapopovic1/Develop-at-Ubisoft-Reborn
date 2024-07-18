#ifndef _RANDOMGENERATOR_H_
#define _RANDOMGENERATOR_H_
#include "..\app\app.h"
#include <time.h>

#define RANDOMINT(a, b) (RandomGenerator::getInstance()->generateInt(a, b))
#define RANDOMFLOAT(a, b) (RandomGenerator::getInstance()->generateFloat(a, b))
#define RANDOMBOOL() (RANDOMINT(0, 1) == 0)

class RandomGenerator {
private:
	static RandomGenerator* instance;
	RandomGenerator() { srand(time(NULL));}

public:
	static RandomGenerator* getInstance();
	int generateInt(int lower, int upper);
	float generateFloat(int lower, int upper);
};
#endif
