#ifndef BLOCK_MENU_SCENE
#define BLOCK_MENU_SCENE

#include "cocos2d.h"
#include "RandomGenerator.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CommandCenter.h"
#include "OptionLayer.h"
#include "CreditLayer.h"
#include "DiscJockey.h"
USING_NS_CC;

class GameMenu :public Layer
{

public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameMenu);

	virtual bool init();

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);

private:

	Point originPoint;

	Size  visibleSize ;

	void addMenu();

	void startGame(Ref* sender);

	void showOption(Ref* sender);

	void showCreditsView(Ref* sender);

};








#endif