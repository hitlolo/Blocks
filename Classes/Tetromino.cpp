#include "Tetromino.h"

bool Tetromino::init()
{

	if (!Sprite::init())
	{
		return false;
	}
	
//	this->setAnchorPoint(Point(0.5, 0.5));
#if 1
	auto grid = Sprite::create("grid1.png");
	grid->setAnchorPoint(Point(0, 0));
	this->addChild(grid);
	grid->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
#endif


	initBlocks();

	return true;
}



Tetromino* Tetromino::create(TETROMINO_TYPE type)
{
	Tetromino *tetromino = new Tetromino(type);
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

Tetromino::Tetromino(TETROMINO_TYPE type)
{
	this->setContentSize(Size(BLOCK_WIDTH * PIECE_SIZE, BLOCK_HEIGHT * PIECE_SIZE));
	this->setType(type);
	switch (type)
	{
		case TETROMINO_TYPE::O:
		{
			char16_t o_shape[4] = { 0x6600, 0x6600, 0x6600, 0x6600 };
			//char16_t o_shape[4] = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(o_shape[i]);
			break;
		}
		case TETROMINO_TYPE::I:
		{
			char16_t i_shape[4] = { 0x0f00, 0x2222, 0x00f0, 0x4444 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(i_shape[i]);
			break;
		}
		case TETROMINO_TYPE::T:
		{
			char16_t t_shape[4] = { 0x4E00, 0x4640, 0x0E40, 0x4C40 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(t_shape[i]);
			break;
		}
		case TETROMINO_TYPE::S:
		{
			char16_t s_shape[4] = { 0x6C00, 0x4620, 0x06C0, 0x8C40 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(s_shape[i]);
			break;
		}
		case TETROMINO_TYPE::Z:
		{
			char16_t z_shape[4] = { 0xC600, 0x2640, 0x0C60, 0x4C80 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(z_shape[i]);
			break;
		}
		case TETROMINO_TYPE::L:
		{
			char16_t l_shape[4] = { 0x8E00, 0x6460, 0x0E20, 0x44C0 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(l_shape[i]);
			break;
		}
		case TETROMINO_TYPE::J:
		{
			char16_t j_shape[4] = { 0x2E00, 0x4460, 0x0E80, 0xC440 };
			for (int i = 0; i < 4; i++)
				this->shapesVector.push_back(j_shape[i]);
			break;
		}
	}

	this->curShape = 0;
	
	blocksVector.resize(PIECE_SIZE);
	for (int i = 0; i < PIECE_SIZE; i++)
		blocksVector[i].resize(PIECE_SIZE);

}

Tetromino::~Tetromino()
{

}

void Tetromino::initBlocks()
{
	char16_t mask = 0x8000;

	//for (int y = 0; y < PIECE_SIZE; y++)
	//{
	//	for (int x = 0; x < PIECE_SIZE; x++)
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			shapeMatrix[y][x] = (bool)(mask & shapesVector[curShape]);
			mask = mask >> 1;
			
			BlockDef blockDef = { TETROMINO, shapeMatrix[y][x], getType(), x, y };
			auto blockCell = BlockElement::create(blockDef);
			this->addChild(blockCell);
			blocksVector[y][x] = blockCell;

			CCLOG("%f,%f,cell positon", blockCell->getPositionX(), blockCell->getPositionY());
			CCLOG("%f,%f,cell ANCHOR", blockCell->getAnchorPoint().x, blockCell->getAnchorPoint().y);
		}
	}
}



//mover
void Tetromino::onLeft()
{
	if (leftAble())
	{
		this->setPositionX(this->getPositionX() - BLOCK_WIDTH);
	}
	
}

void Tetromino::onRight()
{
	if (rightAble())
	{
		this->setPositionX(this->getPositionX() + BLOCK_WIDTH);
	}
	
}

void Tetromino::onRotate()
{
	/*if (rotateAble())
	{
		doRotation();
	}*/
	SuperRotationSystem::getInstance()->doRotation(this);
	
}

void Tetromino::onDown()
{
	if (downAble())
	{
		this->setPositionY(this->getPositionY() - BLOCK_WIDTH);
	}
}

void Tetromino::onHardDrop()
{}

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
			CCLOG("%d,%d,i am not empty",y,x);
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
			CCLOG("%d,%d,i am not empty", y, x);
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
			CCLOG("%d,%d,i am not empty", y, x);
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
			if (shapeMatrix[y][x] == (bool)(mask & shapesVector[curShape]))
			{
				mask = mask >> 1;
				continue;
			}
			else
			{
				shapeMatrix[y][x] = (bool)(mask & shapesVector[curShape]);
				
				blocksVector[y][x]->reShowing();
			}	
			mask = mask >> 1;
		}
	}
}