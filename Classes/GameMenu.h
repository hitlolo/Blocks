#ifndef BLOCK_MENU_SCENE
#define BLOCK_MENU_SCENE

#include "cocos2d.h"
USING_NS_CC;

class GameMenu :public Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameMenu);

private:
	~GameMenu();

	void addMenu();
};








#endif