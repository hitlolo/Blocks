#ifndef BLOCK_GAME_SCENE
#define BLOCK_GAME_SCENE

#include "cocos2d.h"
#include "GameBoard.h"
#include "SimpleAudioEngine.h"
#include "TouchLayer.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

private:
	~GameScene();

	Point originPoint;

	Size  visibleSize;

	void  addLayers();

	std::vector<Node*> starVector;

	void startShining(float time);
};




#endif