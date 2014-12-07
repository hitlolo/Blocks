#ifndef BLOCK_OPTIONS
#define BLOCK_OPTIONS

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;


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


};

#endif