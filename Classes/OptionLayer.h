#ifndef BLOCK_OPTIONS
#define BLOCK_OPTIONS

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "DiscJockey.h"
#include "CommandCenter.h"

USING_NS_CC;

using namespace ui;


class OptionLayer :public Layer
{

public:
	CREATE_FUNC(OptionLayer);

	virtual bool init() override;

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void onTouchCancelled(Touch* touch, Event* event);

	virtual void onEnter();

private:
	Point originPoint;

	Size  visibleSize;

	void addOption();

	void cancel(Ref* sender);

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);

	void musicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	void effectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	void speedSliderCallback(Ref*pSender, ui::SliderEventType event_type);
};

#endif