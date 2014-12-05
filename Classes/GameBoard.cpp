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

	curTop = FIELD_BOTTOM;
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
	for (int y = FIELD_TOP; y >= FIELD_BOTTOM; y--) //19-0
	{
		for (int x = FIELD_LEFT_BOARD; x <= FIELD_RIGHT_BOARD; x++)   //0-9
		{
#if 0
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

void GameBoard::gameOver()
{
	this->curTetromino->stopFalling();
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

void GameBoard::checkClear()
{
	for (int y = 0; y < getCurTop(); y++)
	{
		for (int x = 0; x <= FIELD_RIGHT_BOARD; x++)
		{
			if (playFieldVector[y][x]->isMeEmpty())
			{
				break;
			}
			if (x == FIELD_RIGHT_BOARD)
			{
				CCLOG("need to be cleared!");
				clearLine(y);
			}
		}
	}
}

void GameBoard::clearLine(int line)
{
	Vector<FiniteTimeAction*> vector_action;
	int tem = line;
	tem >>= 1;
	tem <<= 1;
	if (tem == line)
	{

		for (int x = FIELD_LEFT_BOARD; x <= FIELD_RIGHT_BOARD; x++)
		{
			auto action = Sequence::create(DelayTime::create(0.1f), CCCallFunc::create(CC_CALLBACK_0(BlockElement::switchShowing, playFieldVector[line][x])), nullptr);
			vector_action.pushBack(action);
		}
	}
	else
	{
		for (int x = FIELD_RIGHT_BOARD; x >= FIELD_LEFT_BOARD; x--)
		{
			auto action = Sequence::create(DelayTime::create(0.1f), CCCallFunc::create(CC_CALLBACK_0(BlockElement::switchShowing, playFieldVector[line][x])), nullptr);
			vector_action.pushBack(action);
		}
	}
	//clear

	auto fall = CCCallFunc::create(CC_CALLBACK_0(GameBoard::fallLine, this, line));
	vector_action.pushBack(fall);
	auto action = Sequence::create(vector_action);
	//fall
	
	this->runAction(action);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("deletechips.wav");
}

void GameBoard::fallLine(int line)
{
	for (int y = line; y <= getCurTop(); y++)
	{
		for (int x = 0; x <= FIELD_RIGHT_BOARD; x++)
		{
			BlockDef def = playFieldVector[y + 1][x]->getBlockDefinition();
			def._coordinateY -= 1;
			playFieldVector[y][x]->reShowing(def);
		}
	}
}