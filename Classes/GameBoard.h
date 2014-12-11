#ifndef BLOCK_GAME_BOARD
#define BLOCK_GAME_BOARD

#include "cocos2d.h"
#include "GameData.h"
#include "Tetromino.h"
#include "RandomGenerator.h"
#include "TouchDelegate.h"
#include "DiscJockey.h"
#include "BoardInterface.h"
#include "HUDDelegate.h"


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

	void switchShowingForCell(Point);

	void switchCurAndNextTetromino();

	void switchCurAndHoldTetromino();

	virtual void onLeft() override;

	virtual void onRight() override;

	virtual void onRotate() override;

	virtual void onDown() override;

	virtual void onHardDrop() override;

	virtual void onHold() override;

	virtual void onPause() override;

	virtual void onSoftDropStart() override;

	virtual void onSoftDropStop() override;

	virtual void gameOver() override;

	virtual void checkClear() override;

	virtual void setCurTop(int) override;

	virtual int  getCurTop() override;

private:

	int curTop;

	CC_SYNTHESIZE(DiscJockeyDelegate*, djDelegator, DJ);

	CC_SYNTHESIZE(HUDDelegate*, HUDDelegator, HUD);

	CC_SYNTHESIZE(class Tetromino*, curTetromino, CurTetromino);

	CC_SYNTHESIZE(class Tetromino*, nextTetromino, NextTetromino);

	CC_SYNTHESIZE(class Tetromino*, ghostTetromino, GhostTetromino);

	CC_SYNTHESIZE(class Tetromino*, holdTetromino, HoldTetromino);

	CC_SYNTHESIZE(TETROMINO_TYPE, curTetroType, CurTetroType);

	CC_SYNTHESIZE(bool, isPaused, IsPaused);

	std::vector<int> comboVector;
	
	std::vector<std::vector<class BlockElement*>> playFieldVector;
	
	void initPlayField();

	void gameStart(); 

	void createCurTetro();

	void createNextTetro();

	void createGhostPiece();

	void createHoldPiece();

	void clearLine(std::vector<int>&);

	void fallLine(int);
	
};











#endif