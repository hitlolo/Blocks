#ifndef BLOCK_LOGO_SCENE
#define BLOCK_LOGO_SCENE

#include "cocos2d.h"
#include "CommandCenter.h"
#include "DiscJockey.h"

USING_NS_CC;

class GameLogo :public Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameLogo);

	virtual bool init();

private:

	void addLogo();

	void loadRes();

	void loadImageOver(Texture2D* texture);

	void loadMusic();

	void startGame();

	void nextScene();

	virtual void onExit() override;

};





#endif