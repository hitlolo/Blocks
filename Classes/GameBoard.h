#ifndef BLOCK_GAME_BOARD
#define BLOCK_GAME_BOARD

#include "cocos2d.h"
#include "GameData.h"
#include "Tetromino.h"

USING_NS_CC;

class GameBoard :public Layer
{

public:

	virtual bool init();

	CREATE_FUNC(GameBoard);

	GameBoard();

	~GameBoard();

private:
	

	
};











#endif