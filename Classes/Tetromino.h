#ifndef BLOCK_TETROMINO_ELEMENT
#define BLOCK_TETROMINO_ELEMENT

#include "cocos2d.h"
#include "GameData.h"
#include "BlockElement.h"
#include "BlockGhost.h"
#include "GameBoard.h"
#include "SuperRotationSystem.h"
#include "RandomGenerator.h"

USING_NS_CC;

class Tetromino :public Sprite
{
public:

	virtual bool init() override;

	static Tetromino* create(TETROMINO_TYPE,bool);

	Tetromino(TETROMINO_TYPE,bool);

	~Tetromino();

	CC_SYNTHESIZE(TETROMINO_TYPE, myType, Type);

	void setInitStateToTetro();

	void setInitStateToPre();

	void setInitStateToGhost();

	void switchState();

	bool isMoveAble();

private:
	friend class SuperRotationSystem;

	std::vector<char16_t>             shapesVector;

	std::vector<std::vector<class Block*>> blocksVector;

	CC_SYNTHESIZE(TETROMINO_STATE, curState, CurState);

	CC_SYNTHESIZE(bool, isGhost, IsGhost);

	CC_SYNTHESIZE(bool, mobility, CurMobility);

	CC_SYNTHESIZE(int, curShape, CurShape);//the index of current Shape
     
	bool shapeMatrix[PIECE_SIZE][PIECE_SIZE]; //mask the ocupied cell

	void initBlocks();

	void doCleanBeforeReset();

	void setShapesByType(TETROMINO_TYPE);

	void reShowing();

	void onLeft();

	void onRight();

	void onRotate();

	void onDown();

	void onHardDrop();

	void onHold();


	bool leftAble();

	bool rightAble();

	bool downAble();

	bool rotateAble();

	void doRotation();
	
	void fallingDown(float time);

	void lockOn();

	void startFalling();

	void stopFalling();

	bool isFalling();

	void runLockDelay();

	void getHaunted();

	void ghostRefreshType(TETROMINO_TYPE type);

	void ghostRefreshShape(int shape);
};



#endif