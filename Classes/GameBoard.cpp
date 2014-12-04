#include "GameBoard.h"

bool GameBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//Point originPoint = Director::getInstance()->getVisibleOrigin();
	//Size visibleSize = Director::getInstance()->getVisibleSize();

	//this->ignoreAnchorPointForPosition(true);	
	//this->setAnchorPoint(Point(0, 0));
	this->setPosition(BOARD_AT);
#if 1
	auto grid = Sprite::create("grid.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setOpacity(100);
#endif
	gameStart();
	return true;
}

GameBoard::GameBoard()
{
	this->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));

	playFieldVector.resize(BOARD_HEIGHT);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		playFieldVector[i].resize(BOARD_WIDTH);

	curTetromino = nullptr;
	initPlayField();
}


GameBoard::~GameBoard()
{
	playFieldVector.clear();
	this->removeAllChildrenWithCleanup(true);
	
}


void GameBoard::initPlayField()
{
	for (int y = BOARD_HEIGHT - 1; y >= 0; y--) //19-0
	{
		for (int x = 0; x < BOARD_WIDTH; x++)   //0-9
		{
#if 1
			if (y == 16 && x == 8)
			{
				BlockDef blockDef = { PLAYFIELD, OCCUPIED, TETROMINO_TYPE::Z, x, y };
				auto blockCell = BlockElement::create(blockDef);
				this->addChild(blockCell);
				playFieldVector[y][x] = blockCell;
			}
			else
#endif
			{
				BlockDef blockDef = { PLAYFIELD, EMPTY, TETROMINO_TYPE::NOTHING, x, y };
				auto blockCell = BlockElement::create(blockDef);
				this->addChild(blockCell);
				playFieldVector[y][x] = blockCell;
			}
			
		}
	}

}


bool GameBoard::isPointOccupied(Point point)
{
	return playFieldVector[point.y][point.x]->getBlockDefinition()._isOccupOrEmpty;
}

void GameBoard::switchShowing(Point point)
{
	playFieldVector[point.y][point.x]->switchShowing();
}


void GameBoard::gameStart()
{

	auto tetro = Tetromino::create((TETROMINO_TYPE)RandomGenerator::getInstance()->getItemfromBag());	
	tetro->setInitStateToTetro();
	this->addChild(tetro);

	this->setCurTetromino(tetro);
	
	auto preTetro = Tetromino::create((TETROMINO_TYPE)RandomGenerator::getInstance()->getItemfromBag());	
	preTetro->setInitStateToPre();
	this->addChild(preTetro);
	this->setNextTetromino(preTetro);

#if 0
	auto blocks = tetro->getChildren();
	for (auto block : blocks)
	{
		if (dynamic_cast<BlockElement*>(block))
		{
			CCLOG("x=%f,y=%f,", dynamic_cast<BlockElement*>(block)->toBoardCoordinate().x, dynamic_cast<BlockElement*>(block)->toBoardCoordinate().y);
		}
	}

#endif	
}

void GameBoard::switchTetromino()
{
	this->curTetromino->switchState();
	this->nextTetromino->switchState();

	auto tem = this->curTetromino;

	this->setCurTetromino(nextTetromino);
	this->setNextTetromino(tem);
}

void GameBoard::onLeft()
{
	curTetromino->onLeft();
}

void GameBoard::onRight()
{
	curTetromino->onRight();
}

void GameBoard::onRotate() 
{
	curTetromino->onRotate();
}

void GameBoard::onDown()
{
	curTetromino->onDown();
}

void GameBoard::onHardDrop() 
{

}

void GameBoard::onHold()
{

}

void GameBoard::onSoftDropStart()
{
	bool isSoftDroping = curTetromino->isFalling();
	if (isSoftDroping)
	{
		this->curTetromino->stopFalling();
	}
	else
	{
		return;
	}
	
}

void GameBoard::onSoftDropStop()
{
	bool isSoftDroping = curTetromino->isFalling();
	if (!isSoftDroping)
	{
		this->curTetromino->startFalling();
	}
	else
	{
		return;
	}

}