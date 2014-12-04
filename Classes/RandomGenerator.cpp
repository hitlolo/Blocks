#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::_randomGenerator = nullptr;


RandomGenerator::RandomGenerator()
{
	itemIndex = 0;
	mt = new std::mt19937(randomDevice());
	this->bag.resize(7);
	for (int i = 0; i < 7; i++)
	{
		bag[i] = i;
	}
		
	
}

RandomGenerator::~RandomGenerator()
{
	CC_SAFE_DELETE(mt);
	CC_SAFE_DELETE(_randomGenerator);
}

RandomGenerator* RandomGenerator::getInstance()
{
	if (_randomGenerator == nullptr)
	{
		_randomGenerator = new RandomGenerator();
		return _randomGenerator;
	}
	else
		return _randomGenerator;
}

void RandomGenerator::fillBag()
{
	for (int i = 0; i < 7; i++)
		CCLOG("%d,bag%d__before", bag[i], i);
	random_shuffle(bag.begin(), bag.end(), CC_CALLBACK_1(RandomGenerator::myRand,this));
	for (int i = 0; i < 7; i++)
		CCLOG("%d,bag%d__after", bag[i], i);
}

int RandomGenerator::myRand(int index)
{
	std::uniform_int_distribution<int> dist(1, 7);
	return dist(*mt) % index;
}

int RandomGenerator::getItemfromBag()
{
	if (itemIndex == 0)
	{
		this->fillBag();
		
	}
	int type = bag[itemIndex];
	itemIndex++;
	if (itemIndex == 7)
	{
		itemIndex = 0;
	}
	return type;
}