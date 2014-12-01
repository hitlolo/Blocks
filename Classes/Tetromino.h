#ifndef BLOCK_TETROMINO_ELEMENT
#define BLOCK_TETROMINO_ELEMENT

#include "cocos2d.h"
#include "GameData.h"
#include "BlockElement.h"

USING_NS_CC;

class Tetromino :public Sprite
{
public:

	virtual bool init() override;

	static Tetromino* create(TETROMINO_TYPE);

	Tetromino(TETROMINO_TYPE);

	~Tetromino();

	CC_SYNTHESIZE(TETROMINO_TYPE, myType, Type);

private:

	std::vector<char16_t> shapesVector;

	int     curShape;     //the index of current Shape

	bool    matrix[PIECE_WIDTH][PIECE_HEIGHT]; //mask the ocupied cell



};



#endif