#ifndef BLOCK_GAME_BOARD
#define BLOCK_GAME_BOARD

#include "cocos2d.h"
#include "GameData.h"
#include "Tetromino.h"
#include "RandomGenerator.h"
#include "TouchDelegate.h"
#include "DiscJockey.h"
#include "BoardInterface.h"


USING_NS_CC;
class GameBoard :public Layer, public TouchDelegate, public BoardInterface
{

public:

	virtual bool init();

	CREATE_FUNC(GameBoard);

	GameBoard();

	~GameBoard();

	virtual bool isPointOccupied(Point point) override;

	virtual TETROMINO_TYPE getTetroType() override;

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

	virtual void gameOver() override;

	virtual void checkClear() override;

private:

	int curTop;

	virtual void setCurTop(int) override;

	virtual int  getCurTop() override;

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);

	CC_SYNTHESIZE(class Tetromino*, curTetromino, CurTetromino);

	CC_SYNTHESIZE(class Tetromino*, nextTetromino, NextTetromino);

	CC_SYNTHESIZE(class Tetromino*, ghostTetromino, ghostTetromino);

	CC_SYNTHESIZE(TETROMINO_TYPE, curTetroType, CurTetroType);

	std::vector<int> comboVector;
	
	std::vector<std::vector<class BlockElement*>> playFieldVector;
	
	void initPlayField();

	void gameStart(); 

	void clearLine(std::vector<int>&);

	void fallLine(int);
	
};











#endif