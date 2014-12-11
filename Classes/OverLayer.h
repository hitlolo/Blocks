#ifndef BLOCK_GAME_OVER
#define BLOCK_GAME_OVER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "DiscJockey.h"
#include "CommandCenter.h"

USING_NS_CC;

using namespace ui;


class OverLayer :public Layer
{

public:
	CREATE_FUNC(OverLayer);

	virtual bool init() override;

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void onTouchCancelled(Touch* touch, Event* event);

	virtual void onEnter();

	virtual void onExit();



private:
	Point originPoint;

	Size  visibleSize;

	void  restart(Ref* sender);

	void  addLayer();

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);
};

#endif