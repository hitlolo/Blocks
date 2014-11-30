#include "GameBoard.h"

bool GameBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto tetro = Tetromino::create(TETROMINO_TYPE::J);
	this->addChild(tetro);

	return true;
}

GameBoard::GameBoard()
{
	this->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));

	this->setPosition(504, 288);
}


GameBoard::~GameBoard()
{
	this->removeAllChildrenWithCleanup(true);
}

