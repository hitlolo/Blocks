#ifndef BLOCK_TETROMINO_ELEMENT
#define BLOCK_TETROMINO_ELEMENT

#include "cocos2d.h"
#include "GameData.h"
#include "BlockElement.h"
#include "TouchDelegate.h"

USING_NS_CC;

class Tetromino :public Sprite, public TouchDelegate
{
public:

	virtual bool init() override;

	static Tetromino* create(TETROMINO_TYPE);

	Tetromino(TETROMINO_TYPE);

	~Tetromino();

	CC_SYNTHESIZE(TETROMINO_TYPE, myType, Type);

	virtual void onLeft() override;

	virtual void onRight() override;

	virtual void onRotate() override;

	virtual void onDown() override;

	virtual void onHardDrop() override;

	virtual void onHold() override;


private:

	std::vector<char16_t>             shapesVector;

	std::vector<std::vector<class BlockElement*>> blocksVector;

	int     curShape;     //the index of current Shape

	bool    matrix[PIECE_SIZE][PIECE_SIZE]; //mask the ocupied cell

	void initBlocks();

	bool leftAble();

	bool rightAble();


};



#endif