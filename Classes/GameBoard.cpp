#include "GameBoard.h"

bool GameBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setIsPaused(false);
	this->setPosition(BOARD_AT);

	auto panel = Sprite::create("blue_panel.png");
	this->addChild(panel);
	panel->setAnchorPoint(Point::ZERO);
	panel->setPosition(Point(-5,-5));
#if 0
	auto grid = Sprite::create("grid.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setOpacity(100);
#endif
	setDJ(DiscJockey::getInstance());
	initPlayField();
	gameStart();
	return true;
}

GameBoard::GameBoard()
{
	this->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));

	playFieldVector.resize(BOARD_HEIGHT);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		playFieldVector[i].resize(BOARD_WIDTH);
	
	comboVector.resize(4);

	curTop = FIELD_BOTTOM;
	curTetromino = nullptr;
	
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

void GameBoard::setCurTop(int top)
{
	this->curTop = top;
}

int  GameBoard::getCurTop()
{
	return this->curTop;
}

bool GameBoard::isPointOccupied(Point point)
{
	return playFieldVector[point.y][point.x]->getBlockDefinition()._isOccupOrEmpty;
}

TETROMINO_TYPE GameBoard::getTetroType()
{
	return this->getCurTetroType();
}


void GameBoard::switchShowing(Point point)
{
	playFieldVector[point.y][point.x]->switchShowing();
}


void GameBoard::gameStart()
{

	auto tetro = Tetromino::create((TETROMINO_TYPE)RandomGenerator::getInstance()->getItemfromBag(),false);	
	tetro->setInitStateToTetro();
	this->addChild(tetro);
	this->setCurTetromino(tetro);
	this->setCurTetroType(tetro->getType());

	auto ghost = Tetromino::create(tetro->getType(),true);
	this->setghostTetromino(ghost);
	ghost->setInitStateToGhost();
	this->addChild(ghost);
	ghost->getHaunted();

	
	auto preTetro = Tetromino::create((TETROMINO_TYPE)RandomGenerator::getInstance()->getItemfromBag(),false);	
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

	getDJ()->playBackgroundMusic();
}

void GameBoard::gameOver()
{
	curTetromino->overGame();
	CCLOG("GAMEOVER!");
}

void GameBoard::switchTetromino()
{
	this->curTetromino->switchState();
	this->nextTetromino->switchState();

	auto tem = this->curTetromino;

	this->setCurTetromino(nextTetromino);
	this->setNextTetromino(tem);

	this->setCurTetroType(getCurTetromino()->getType());

	this->ghostTetromino->getHaunted();
}

void GameBoard::onLeft()
{
	getDJ()->playMoveEffect();
	curTetromino->onLeft();
	ghostTetromino->getHaunted();
}

void GameBoard::onRight()
{
	getDJ()->playMoveEffect();
	curTetromino->onRight();
	ghostTetromino->getHaunted();
}

void GameBoard::onRotate() 
{
	getDJ()->playMoveEffect();
	curTetromino->onRotate();
	ghostTetromino->getHaunted();
//	ghostTetromino->setCurShape(curTetromino->getCurShape());
}

void GameBoard::onDown()
{
	getDJ()->playMoveEffect();
	curTetromino->onDown();
}

void GameBoard::onHardDrop() 
{
	getDJ()->playMoveEffect();
	curTetromino->onHardDrop();
}

void GameBoard::onHold()
{
	getDJ()->playMoveEffect();
}

void GameBoard::onPause()
{
	this->getDJ()->playClickEffect();
	this->setIsPaused(!getIsPaused());
	if (getIsPaused())
	{
		this->curTetromino->pauseSchedulerAndActions();
	}
	else
	{
		this->curTetromino->resumeSchedulerAndActions();
	}

	
}
	

void GameBoard::onSoftDropStart()
{
	getDJ()->playMoveEffect();
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
	getDJ()->playMoveEffect();
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
	getDJ()->playLockOnEffect();

	for (int i = 0; i < 4; i++)
		comboVector[i] = -1;
	int index = 0;
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
				comboVector[index++] = y;
				
			}
		}
	}
	if (index == 0)
	{
		return;
	}
	else
	{
		clearLine(comboVector);
	}
	
}

void GameBoard::clearLine(std::vector<int> &lineVector)
{
	Vector<FiniteTimeAction*> vector_action;
	int combo = 0;
	for (int i = 0; i < 4; i++)
	{
		if (lineVector[i] == -1)
		{
			continue;
		}
		else
		{	
			combo++;
			int tem = lineVector[i];
			tem >>= 1;
			tem <<= 1;
			if (tem == lineVector[i])
			{
				for (int x = FIELD_LEFT_BOARD; x <= FIELD_RIGHT_BOARD; x++)
				{
					auto action = Sequence::create(DelayTime::create(0.1f), CCCallFunc::create(CC_CALLBACK_0(BlockElement::switchShowing, playFieldVector[lineVector[i] - (combo - 1)][x])), nullptr);
					vector_action.pushBack(action);
				}
			}
			else
			{
				for (int x = FIELD_RIGHT_BOARD; x >= FIELD_LEFT_BOARD; x--)
				{
					auto action = Sequence::create(DelayTime::create(0.1f), CCCallFunc::create(CC_CALLBACK_0(BlockElement::switchShowing, playFieldVector[lineVector[i] - (combo - 1)][x])), nullptr);
					vector_action.pushBack(action);
				}
			}
			
			auto fall = CCCallFunc::create(CC_CALLBACK_0(GameBoard::fallLine, this, lineVector[i] - (combo - 1)));
			vector_action.pushBack(fall);
			
		}
	}

	auto action = Sequence::create(vector_action);
	this->runAction(action);
	//fall
	CCLOG("%d,comBO", combo);
	getHUD()->addLine(combo);
	//fallLine(lineArray);
	

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
				
	this->setCurTop(getCurTop() - 1);
	this->ghostTetromino->getHaunted();
	this->curTetromino->checkAndStopLockon();
	getDJ()->playClearLineEffect();
}
