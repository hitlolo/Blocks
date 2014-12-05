#ifndef BLOCK_TOUCH_LAYER
#define BLOCK_TOUCH_LAYER

#include "cocos2d.h"
#include "TouchDelegate.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


class TouchLayer :public Layer
{

public:

	virtual bool init();

	CREATE_FUNC(TouchLayer);

	CC_SYNTHESIZE(TouchDelegate*, myDelegate, MyTouchDelegate);

	void getAndSetButtons();

private:

	void onLongLeft(float time);

	void onLongRight(float time);

	void onLongDown(float time);

	void onLongRotate(float time);

	void onLeft(Ref* sender);

	void onRight(Ref* sender);

	void onRotation(Ref* sender);

	void onDown(Ref* sender);

	void onHold(Ref* sender);

	void onHardDrop(Ref* sender);

	void onLongLeftClick(Ref *pSender, ui::Widget::TouchEventType type);

	void onLongRightClick(Ref *pSender, ui::Widget::TouchEventType type);

	void onLongDownClick(Ref *pSender, ui::Widget::TouchEventType type);

	void onLongRotateClick(Ref *pSender, ui::Widget::TouchEventType type);

};



#endif