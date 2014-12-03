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
	auto tetro = Tetromino::create(TETROMINO_TYPE::O);
	tetro->setPosition(SPAWN_POINT);
	this->addChild(tetro);
	this->setCurTetromino(tetro);
	auto blocks = tetro->getChildren();
	for (auto block : blocks)
	{
		if (dynamic_cast<BlockElement*>(block))
		{
			CCLOG("x=%f,y=%f,", dynamic_cast<BlockElement*>(block)->toBoardCoordinate().x, dynamic_cast<BlockElement*>(block)->toBoardCoordinate().y);
		}
	}

#endif	

	

#if 1
	auto grid = Sprite::create("grid.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setOpacity(100);
#endif
	return true;
}

GameBoard::GameBoard()
{
	this->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));

	playFieldVector.resize(BOARD_HEIGHT);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		playFieldVector[i].resize(BOARD_WIDTH);


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