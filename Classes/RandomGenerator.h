#ifndef BLOCK_RANDOM
#define BLOCK_RANDOM

#include "cocos2d.h"

USING_NS_CC;

class RandomGenerator
{
public:
	
	RandomGenerator();

	~RandomGenerator();

	static RandomGenerator* getInstance();

	int getItemfromBag();

	Point getRandomPosition();

	int getRandomFromRange(int, int);

	float getRandomFromRange(float, float);

private:
	static RandomGenerator* _randomGenerator;

	int  itemIndex;

	std::vector<int> bag;

	void fillBag();

	std::random_device randomDevice;

	std::mt19937*      mt;

	int myRand(int index);

};


#endif