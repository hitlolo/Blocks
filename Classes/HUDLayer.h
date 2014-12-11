
#ifndef BLOCK_SCORE_LAYER
#define BLOCK_SCORE_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "HUDDelegate.h"
#include "GameData.h"
#include "DiscJockey.h"
#include "CommandCenter.h"

USING_NS_CC;
using namespace ui;


class HUDLayer :public Layer, public HUDDelegate
{

public:
	CREATE_FUNC(HUDLayer);

	virtual bool init() override;

	void addLayer();

	virtual void addLine(int) override;

	HUDLayer();

	~HUDLayer();

private:

	int lineNum;

	int scoreNum;

	int comboNum;

	CC_SYNTHESIZE(Text*,curLine,CurLine);

	CC_SYNTHESIZE(Text*, curScore, CurScore);

	CC_SYNTHESIZE(Text*, curCombo, CurCombo);

	CC_SYNTHESIZE(Text*, curSpeed, CurSpeed);

	virtual void addCombo() override;

	virtual void addScore() override;

	virtual void addSpeed() override;
};









#endif