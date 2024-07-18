#include "stdafx.h"

RandomGenerator* RandomGenerator::instance = nullptr;

int RandomGenerator::generateInt(int lower, int upper) {
	int randNumber;
	randNumber = lower + rand() % (upper + 1 - lower);
	return randNumber;
}

float RandomGenerator::generateFloat(int lower, int upper) {
	float randNumber;
	randNumber = lower + (float)rand() / (float)(RAND_MAX / (upper - lower));
	return randNumber;
}

RandomGenerator* RandomGenerator::getInstance() {
	if (!instance) instance = new RandomGenerator();
	return instance;
}

