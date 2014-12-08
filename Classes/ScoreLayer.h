
#ifndef BLOCK_SCORE_LAYER
#define BLOCK_SCORE_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;


class ScoreLayer :public Layer
{

public:
	CREATE_FUNC(ScoreLayer);

	virtual bool init() override;

	void addLayer();
};









#endif