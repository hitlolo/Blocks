
#ifndef BLOCK_SCORE_LAYER
#define BLOCK_SCORE_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "HUDDelegate.h"
#include "GameData.h"
#include "DiscJockey.h"

USING_NS_CC;
using namespace ui;

extern int speedLevel;
class ScoreLayer :public Layer, public HUDDelegate
{

public:
	CREATE_FUNC(ScoreLayer);

	virtual bool init() override;

	void addLayer();

	virtual void addLine(int) override;

	ScoreLayer();

	~ScoreLayer();

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