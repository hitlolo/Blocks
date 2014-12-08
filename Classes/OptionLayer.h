#ifndef BLOCK_OPTIONS
#define BLOCK_OPTIONS

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "DiscJockey.h"
#include "GameData.h"
USING_NS_CC;

using namespace ui;

extern int speedLevel;
class OptionLayer :public Layer
{

public:
	CREATE_FUNC(OptionLayer);

	virtual bool init() override;

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void onTouchCancelled(Touch* touch, Event* event);

	virtual void onEnter();

	virtual void onExit();

	
	
private:
	Point originPoint;

	Size  visibleSize;

	void cancel(Ref* sender);

	void addOption();

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);

	void musicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	void effectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	void speedSliderCallback(Ref*pSender, ui::SliderEventType event_type);
};

#endif