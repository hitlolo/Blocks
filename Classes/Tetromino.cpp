#include "Tetromino.h"

bool Tetromino::init()
{

	if (!Node::init())
	{
		return false;
	}
	
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
	this->setType(type);
	switch (type)
	{
		case TETROMINO_TYPE::O:
		{
			char16_t o_shape[4] = { 0x6600, 0x6600, 0x6600, 0x6600 };
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
	char16_t mask  = 0x8000;
	for (int y = 0; y < PIECE_HEIGHT; y++)
	{
		for (int x = 0; x < PIECE_WIDTH; x++)
		{
			matrix[y][x] = (bool)(mask & shapesVector[curShape]);
			mask = mask >> 1;
			if (matrix[y][x])
			{
				BlockDef blockDef = { type, (IS_BLOCK)(matrix[y][x]),x,y };
				auto blockCell = BlockElement::create(blockDef);
				this->addChild(blockCell);
				
			}
		}
	}
}

Tetromino::~Tetromino()
{

}