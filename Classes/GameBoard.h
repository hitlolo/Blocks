#ifndef BLOCK_GAME_BOARD
#define BLOCK_GAME_BOARD

#include "cocos2d.h"
#include "GameData.h"
#include "Tetromino.h"
#include "RandomGenerator.h"
#include "TouchDelegate.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameBoard :public Layer,public TouchDelegate
{

public:

	virtual bool init();

	CREATE_FUNC(GameBoard);

	GameBoard();

	~GameBoard();

	CC_SYNTHESIZE(int, curTop, CurTop);

	CC_SYNTHESIZE(class Tetromino*, curTetromino, CurTetromino);

	CC_SYNTHESIZE(class Tetromino*, nextTetromino, NextTetromino);

	CC_SYNTHESIZE(class Tetromino*, ghostTetromino, ghostTetromino);

	bool isPointOccupied(Point);

	void switchShowing(Point);

	void switchTetromino();

	virtual void onLeft() override;

	virtual void onRight() override;

	virtual void onRotate() override;

	virtual void onDown() override;

	virtual void onHardDrop() override;

	virtual void onHold() override;

	virtual void onSoftDropStart() override;

	virtual void onSoftDropStop() override;

	void gameOver();

	void checkClear();

private:
	
	std::vector<std::vector<class BlockElement*>> playFieldVector;
	
	void initPlayField();

	void gameStart(); 

	void clearLine(int);

	void fallLine(int);
	
};











#endif