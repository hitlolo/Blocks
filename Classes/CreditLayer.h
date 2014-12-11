#ifndef BLOCK_CREDIT
#define BLOCK_CREDIT

#include "cocos2d.h"
#include "DiscJockey.h"
USING_NS_CC;


class CreditLayer :public Layer
{

public:
	CREATE_FUNC(CreditLayer);

	virtual bool init() override;

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void onTouchCancelled(Touch* touch, Event* event);

	virtual void onEnter();

private:
	Point originPoint;

	Size  visibleSize;

	void setCreditString();

	void setEventListener();

	void cancel();

	void show();

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);


};

#endif