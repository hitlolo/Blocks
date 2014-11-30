#ifndef BLOCK_LOGO_SCENE
#define BLOCK_LOGO_SCENE

#include "cocos2d.h"
#include "CommandCenter.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameLogo :public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLogo);

private:
	~GameLogo();

	void addLogo();

	void loadRes();

	void loadImageOver(Texture2D* texture);

	void loadMusic();

	void startGame();

	void nextScene();

	virtual void onExit() override;

};





#endif