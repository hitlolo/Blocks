#include "GameBoard.h"

bool GameBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//this->ignoreAnchorPointForPosition(true);	
	this->setAnchorPoint(Point(0, 0));
	//this->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	//this->setPosition(504, 288);
	this->setPosition(384, 48);
	auto tetro = Tetromino::create(TETROMINO_TYPE::O);
	tetro->setPosition(SPAWN_POINT);
	this->addChild(tetro);
	CCLOG("%f,%f tetro", tetro->getPosition().x, tetro->getPosition().y);
	auto grid = Sprite::create("grid.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setOpacity(100);
	return true;
}

GameBoard::GameBoard()
{
	this->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));
	//this->setPosition(504, 288);
	//this->setPosition(0, 0);
}


GameBoard::~GameBoard()
{
	this->removeAllChildrenWithCleanup(true);
}

