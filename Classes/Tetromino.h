#ifndef BLOCK_TETROMINO_ELEMENT
#define BLOCK_TETROMINO_ELEMENT

#include "cocos2d.h"
#include "GameData.h"
#include "BlockElement.h"

#include "SuperRotationSystem.h"
#include "RandomGenerator.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Tetromino :public Sprite
{
public:

	virtual bool init() override;

	static Tetromino* create(TETROMINO_TYPE);

	Tetromino(TETROMINO_TYPE);

	~Tetromino();

	CC_SYNTHESIZE(TETROMINO_TYPE, myType, Type);

	void setInitStateToTetro();

	void setInitStateToPre();

	void switchState();

	bool isMoveAble();

private:
	friend class SuperRotationSystem;

	std::vector<char16_t>             shapesVector;

	std::vector<std::vector<class BlockElement*>> blocksVector;

	CC_SYNTHESIZE(TETROMINO_STATE, curState, CurState);

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
};



#endif