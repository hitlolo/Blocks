#include "Tetromino.h"

bool Tetromino::init()
{

	if (!Sprite::init())
	{
		return false;
	}
	
//	this->setAnchorPoint(Point(0.5, 0.5));
#if 0
	auto grid = Sprite::create("grid1.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
#endif


	initBlocks();

	return true;
}



Tetromino* Tetromino::create(TETROMINO_TYPE type,bool ghost)
{
	Tetromino *tetromino = new Tetromino(type, ghost);
	if (tetromino && tetromino->init())
	{
		tetromino->autorelease();
		return tetromino;
	}
	else
	{
		CC_SAFE_DELETE(tetromino);
		tetromino = NULL;
		return NULL;
	}

}

Tetromino::Tetromino(TETROMINO_TYPE type, bool ghost)
{
	this->setContentSize(Size(BLOCK_WIDTH * PIECE_SIZE, BLOCK_HEIGHT * PIECE_SIZE));
	shapesVector.resize(SHAPE_SIZE);
	blocksVector.resize(PIECE_SIZE);
	for (int i = 0; i < PIECE_SIZE; i++)
		blocksVector[i].resize(PIECE_SIZE);
	setShapesByType(type);

	this->setIsGhost(ghost); 
}

Tetromino::~Tetromino()
{

}

void Tetromino::initBlocks()
{
	char16_t mask = 0x8000;
	TETROMINO_TYPE type =  getType();
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			shapeMatrix[y][x] = (bool)(mask & shapesVector[curShape]);
			mask = mask >> 1;
			if (getIsGhost())
			{
				BlockDef blockDef = { TETROMINO, shapeMatrix[y][x], type, x, y, true };
				auto blockCell = BlockGhost::create(blockDef);
				this->addChild(blockCell);
				blocksVector[y][x] = blockCell;
			}
			else
			{
				BlockDef blockDef = { TETROMINO, shapeMatrix[y][x], type, x, y ,false};
				auto blockCell = BlockElement::create(blockDef);
				this->addChild(blockCell);
				blocksVector[y][x] = blockCell;
			}
			

		}
	}
}

void Tetromino::setShapesByType(TETROMINO_TYPE type)
{
	this->setType(type);
	switch (type)
	{
	case TETROMINO_TYPE::O:
	{
		char16_t o_shape[SHAPE_SIZE] = { 0x6600, 0x6600, 0x6600, 0x6600 };
		//char16_t o_shape[4] = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = o_shape[i];
		break;
	}
	case TETROMINO_TYPE::I:
	{
		char16_t i_shape[SHAPE_SIZE] = { 0x0f00, 0x2222, 0x00f0, 0x4444 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = i_shape[i];
		break;
	}
	case TETROMINO_TYPE::T:
	{
		char16_t t_shape[SHAPE_SIZE] = { 0x4E00, 0x4640, 0x0E40, 0x4C40 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = t_shape[i];
		break;
	}
	case TETROMINO_TYPE::S:
	{
		char16_t s_shape[SHAPE_SIZE] = { 0x6C00, 0x4620, 0x06C0, 0x8C40 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = s_shape[i];
		break;
	}
	case TETROMINO_TYPE::Z:
	{
		char16_t z_shape[SHAPE_SIZE] = { 0xC600, 0x2640, 0x0C60, 0x4C80 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = z_shape[i];
		break;
	}
	case TETROMINO_TYPE::L:
	{
		char16_t l_shape[SHAPE_SIZE] = { 0x8E00, 0x6440, 0x0E20, 0x44C0 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = l_shape[i];
		break;
	}
	case TETROMINO_TYPE::J:
	{
		char16_t j_shape[SHAPE_SIZE] = { 0x2E00, 0x4460, 0x0E80, 0xC440 };
		for (int i = 0; i < SHAPE_SIZE; i++)
			this->shapesVector[i] = j_shape[i];
		break;
	}
	}

	this->curShape = 0;
}

void Tetromino::doCleanBeforeReset()
{


}

//mover
void Tetromino::onLeft()
{
	if (leftAble())
	{
		this->setPositionX(this->getPositionX() - BLOCK_WIDTH);
		
		if (downAble())
		{
			auto lock_on = this->getActionByTag(LOCK_DELAY_TAG);
			if (lock_on)
			{
				this->stopAction(lock_on);
			}
		}
	}
	
}

void Tetromino::onRight()
{

	if (rightAble())
	{
		
		this->setPositionX(this->getPositionX() + BLOCK_WIDTH);
		if (downAble())
		{
			auto lock_on = this->getActionByTag(LOCK_DELAY_TAG);
			if (lock_on)
			{
				this->stopAction(lock_on);
			}
		}
	}
	
}

void Tetromino::onRotate()
{
	/*if (rotateAble())
	{
		doRotation();
	}*/
	bool is_rotated = SuperRotationSystem::getInstance()->doRotation(this);
	if (is_rotated)
	{
		if (downAble())
		{
			auto lock_on = this->getActionByTag(LOCK_DELAY_TAG);
			if (lock_on)
			{
				this->stopAction(lock_on);
			}
		}
	}
	
}

void Tetromino::onDown()
{
	if (downAble())
	{
		this->setPositionY(this->getPositionY() - BLOCK_WIDTH);
	}
	else
	{
		auto lock_on = this->getActionByTag(LOCK_DELAY_TAG);
		if (lock_on)
		{
			this->stopAction(lock_on);

		}
		this->lockOn();
	
	}

}

void Tetromino::onHardDrop()
{
	Point newPosition = dynamic_cast<GameBoard*> (getParent())->getghostTetromino()->getPosition();
	this->setPosition(newPosition);

}

void Tetromino::onHold()
{
}


bool Tetromino::leftAble()
{
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			if (blocksVector[y][x]->isMeEmpty())
			{
				continue;
			}
		//	CCLOG("%d,%d,i am not empty",y,x);
			bool is_leftable = this->blocksVector[y][x]->leftAble();
			if (is_leftable)
			{
				break;
			}
			else if (!is_leftable)
			{
				return false;
			}
		}
	}
	return true;
}

bool Tetromino::rightAble()
{
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = PIECE_SIZE - 1; x >= 0; x--)
		{
			if (blocksVector[y][x]->isMeEmpty())
			{
				continue;
			}
			//CCLOG("%d,%d,i am not empty", y, x);
			bool is_rightable = this->blocksVector[y][x]->rightAble();
			if (is_rightable)
			{
				break;
			}
			else if (!is_rightable)
			{
				return false;
			}
		}
	}
	return true;
}


bool Tetromino::downAble()
{
	for (int x = 0; x < PIECE_SIZE; x++)
	{
		for (int y = 0; y < PIECE_SIZE; y++)
		{
			if (blocksVector[y][x]->isMeEmpty())
			{
				continue;
			}
		//	CCLOG("%d,%d,i am not empty", y, x);
			bool is_downable = this->blocksVector[y][x]->downAble();
			if (is_downable)
			{
				break;
			}
			else if (!is_downable)
			{
				return false;
			}
		}
	}
	return true;
}

bool Tetromino::rotateAble()
{
	int temShape = curShape + 1;
	if (temShape == 4)
	{
		temShape = 0;
	}
	char16_t mask = 0x8000;
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			if (shapeMatrix[y][x] == (bool)(mask & shapesVector[temShape]))
			{
				mask = mask >> 1;
				continue;
			}
			else
			{
				bool is_rotateable = blocksVector[y][x]->rotateAble();
				if (!is_rotateable)
				{
					return false;
				}
			}
			mask = mask >> 1;
		}
	}
	return true;
}

void Tetromino::doRotation()
{
	curShape++;
	if (curShape == 4)
	{
		curShape = 0;
	}

	char16_t mask = 0x8000;

	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			if (shapeMatrix[y][x] == static_cast<bool>(mask & shapesVector[curShape]))
			{
				mask = mask >> 1;
				continue;
			}
			else
			{
				shapeMatrix[y][x] = (bool)(mask & shapesVector[curShape]);
				
				blocksVector[y][x]->switchShowing();
			}	
			mask = mask >> 1;
		}
	}
}



void Tetromino::fallingDown(float time)
{
	if ( downAble() && getCurMobility() )
	{
		this->setPositionY(this->getPositionY() - BLOCK_HEIGHT);
	}
	else
	{
		runLockDelay();
	}
	
}

void Tetromino::lockOn()
{
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{		
			if (blocksVector[y][x]->isMeEmpty())
			{
				continue;
			}
			else
			{
				dynamic_cast<BlockElement*>(blocksVector[y][x])->lockOn();
			}
		}
	}

	dynamic_cast<GameBoard*> (getParent())->checkClear();
	
	dynamic_cast<GameBoard*> (getParent())->switchTetromino();
}

void Tetromino::runLockDelay()
{
	auto delay = DelayTime::create(0.25f);
	auto lockon = Sequence::createWithTwoActions(delay, CCCallFunc::create(CC_CALLBACK_0(Tetromino::lockOn,this)));
	lockon->setTag(LOCK_DELAY_TAG);
	this->runAction(lockon);
}

void Tetromino::startFalling()
{
	this->schedule(CC_SCHEDULE_SELECTOR(Tetromino::fallingDown), 1.0f);
}

void Tetromino::stopFalling()
{
	unschedule(CC_SCHEDULE_SELECTOR(Tetromino::fallingDown));
}

void Tetromino::setInitStateToTetro()
{
	this->setCurState(TETROMINO_STATE::SHOW);
	this->setPosition(SPAWN_POINT);
	this->setCurMobility(true);
	this->startFalling();
	
}

void Tetromino::setInitStateToPre()
{
	this->setCurState(TETROMINO_STATE::PRE);
	this->setCurMobility(false);
	this->setPosition(PRE_POINT);
}

void  Tetromino::setInitStateToGhost()
{
	this->setCurState(TETROMINO_STATE::GHOST);
	this->setCurMobility(false);
	this->setPosition(0,0);
}

void Tetromino::switchState()
{
	if (curState == TETROMINO_STATE::SHOW)
	{
		this->setInitStateToPre();
		this->stopFalling();
		this->reShowing();
	}
	else if (curState == TETROMINO_STATE::PRE)
	{
		setInitStateToTetro();
	}
}

void Tetromino::reShowing()
{
	TETROMINO_TYPE type = (TETROMINO_TYPE)RandomGenerator::getInstance()->getItemfromBag();
	this->setShapesByType(type);

	char16_t mask = 0x8000;

	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			shapeMatrix[y][x] = (bool)(mask & shapesVector[curShape]);
			mask = mask >> 1;
			BlockDef blockDef = { TETROMINO, shapeMatrix[y][x], getType(), x, y };
			dynamic_cast<BlockElement*>(blocksVector[y][x])->reShowing(blockDef);

		}
	}
}

bool Tetromino::isMoveAble()
{
	return this->getCurMobility();
}

bool Tetromino::isFalling()
{
	return isScheduled(CC_SCHEDULE_SELECTOR(Tetromino::fallingDown));
}


void Tetromino::getHaunted()
{
	if (!isGhost)
	{
		return;
	}
	TETROMINO_TYPE type = dynamic_cast<GameBoard*> (getParent())->getCurTetroType();
	int shape = dynamic_cast<GameBoard*> (getParent())->getCurTetromino()->curShape;
	if (this->getType() != type)
	{
		this->ghostRefreshType(type);
		this->ghostRefreshShape(shape);
	}
	
	if (shape!=this->curShape)
	{
		this->ghostRefreshShape(shape);
	}
		
	Point initPosition = dynamic_cast<GameBoard*> (getParent())->getCurTetromino()->getPosition();
	this->setPosition(initPosition.x, initPosition.y);
	while (downAble())
	{
		this->setPosition(initPosition.x, initPosition.y -= 32);
	};
	
}

void Tetromino::ghostRefreshType(TETROMINO_TYPE type)
{
	this->setShapesByType(type);
}

void Tetromino::ghostRefreshShape(int shape)
{
	char16_t mask = 0x8000;

	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			if (shapeMatrix[y][x] == static_cast<bool>(mask & shapesVector[shape]))
			{
				mask = mask >> 1;
				continue;
			}
			else
			{
				shapeMatrix[y][x] = (bool)(mask & shapesVector[shape]);

				blocksVector[y][x]->switchShowing();
			}
			mask = mask >> 1;
		}
	}

	this->setCurShape(shape);
}