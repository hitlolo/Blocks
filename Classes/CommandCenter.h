#ifndef BLOCK_COMMAND_CENTER
#define BLOCK_COMMAND_CENTER

#include "cocos2d.h"
#include "GameData.h"
#include "GameLogo.h"
#include "GameMenu.h"
#include "GameScene.h"
#include "OverLayer.h"

class CommandCenter
{

public:
	CommandCenter();

	~CommandCenter();

	static CommandCenter* getInstance();

	CC_SYNTHESIZE(Scene*, curScene, CurScene);

	CC_SYNTHESIZE(GAME_STATE, curState, CurState);

	CC_SYNTHESIZE(int, curSpeed, SpeedLevel);

	void goState(GAME_STATE = GAME_STATE::LOGO);


private:

	static CommandCenter* _commandCenter;

	void   toNextScene(Scene*);

	void   toLogo();

	void   toMenu();

	void   toGame();

	void   toOver();
};





#endif