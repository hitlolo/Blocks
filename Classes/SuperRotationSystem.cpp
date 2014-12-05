#include "SuperRotationSystem.h"

SuperRotationSystem* SuperRotationSystem::_srs = nullptr;


SuperRotationSystem* SuperRotationSystem::getInstance()
{
	if (_srs == nullptr)
	{
		_srs = new SuperRotationSystem();
		return _srs;
	}
	else
		return _srs;
}

SuperRotationSystem::SuperRotationSystem()
{
	curTetro = nullptr;
}

SuperRotationSystem::~SuperRotationSystem()
{
	CC_SAFE_DELETE(_srs);
}

bool SuperRotationSystem::doRotation(Tetromino* tetro)
{
	setCurTetro(tetro);
	TETROMINO_TYPE type = tetro->getType();
	bool is_rotated =  this->rotationTestByTetroType(type);
	return is_rotated;
}

bool SuperRotationSystem::rotationTestByTetroType(TETROMINO_TYPE type)
{
	if (type == TETROMINO_TYPE::I)
	{
		return rotationTestI();
	}
	else if (type == TETROMINO_TYPE::O)
	{
		return false;
	}
	else 
	{
		return rotationTestOther();
	}
}



bool SuperRotationSystem::rotationTestI()
{
	SHAPE_STATE curShape = (SHAPE_STATE)(getCurTetro()->curShape);
	if (curShape == SHAPE_STATE::SHAPE_0)
	{
		return srsI_0toR();
	}
	else if (curShape == SHAPE_STATE::SHAPE_R)
	{
		return srsI_Rto2();
	}
	else if (curShape == SHAPE_STATE::SHAPE_2)
	{
		return srsI_2toL();
	}
	else if (curShape == SHAPE_STATE::SHAPE_L)
	{
		return srsI_Lto0();
	}
	else return false;
}

//J, L, S, T, Z Tetromino Wall Kick Data
//        Test 1	Test 2	Test 3	   Test 4	Test 5
//0->R	  (0, 0)	(-1, 0)	(-1, +1)	(0, -2)	(-1, -2)
//R->0	  (0, 0)	(+1, 0)	(+1, -1)	(0, +2)	(+1, +2)
//R->2	  (0, 0)	(+1, 0)	(+1, -1)	(0, +2)	(+1, +2)
//2->R    (0, 0)	(-1, 0)	(-1, +1)	(0, -2)	(-1, -2)
//2->L    (0, 0)	(+1, 0)	(+1, +1)	(0, -2)	(+1, -2)
//L->2	  (0, 0)	(-1, 0)	(-1, -1)	(0, +2)	(-1, +2)
//L->0	  (0, 0)	(-1, 0)	(-1, -1)	(0, +2)	(-1, +2)
//0->L    (0, 0)	(+1, 0)	(+1, +1)	(0, -2)	(+1, -2)
bool SuperRotationSystem::rotationTestOther()
{	
	SHAPE_STATE curShape = (SHAPE_STATE)(getCurTetro()->curShape);
	if (curShape == SHAPE_STATE::SHAPE_0)
	{
		return srsOther0toR();
	}
	else if (curShape == SHAPE_STATE::SHAPE_R)
	{
		return srsOtherRto2();
	}
	else if (curShape == SHAPE_STATE::SHAPE_2)
	{
		return srsOther2toL();
	}
	else if (curShape == SHAPE_STATE::SHAPE_L)
	{
		return srsOtherLto0();
	}

	else return false;
}

bool SuperRotationSystem::rotationTestBySRS(int cood_x, int cood_y)
{
	int temShape = getCurTetro()->curShape + 1;
	if (temShape == 4)
	{
		temShape = 0;
	}
	char16_t mask = 0x8000;
	for (int y = PIECE_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < PIECE_SIZE; x++)
		{
			if (getCurTetro()->shapeMatrix[y][x] == (bool)(mask & getCurTetro()->shapesVector[temShape]))
			{
				mask = mask >> 1;
				continue;
			}
			else
			{
				bool is_rotateable = getCurTetro()->blocksVector[y][x]->rotateAble(cood_x, cood_y);
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


bool SuperRotationSystem::srsOther0toR()
{
	//0->R
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, 0))
	{
		setNewPositionAndRotate(-1, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, +1))
	{
		setNewPositionAndRotate(-1, +1);
		return true;
	}
	else if (rotationTestBySRS(0, -2))
	{
		setNewPositionAndRotate(0, -2);
		return true;
	}
	else if (rotationTestBySRS(-1, -2))
	{
		setNewPositionAndRotate(-1, -2);
		return true;
	}
	else
		return false;
}

//R->2	  (0, 0)	(+1, 0)	(+1, -1)	(0, +2)	(+1, +2)
bool SuperRotationSystem::srsOtherRto2()
{

	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, 0))
	{
		setNewPositionAndRotate(+1, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, -1))
	{
		setNewPositionAndRotate(+1, -1);
		return true;
	}
	else if (rotationTestBySRS(0, +2))
	{
		setNewPositionAndRotate(0, +2);
		return true;
	}
	else if (rotationTestBySRS(+1, +2))
	{
		setNewPositionAndRotate(+1, +2);
		return true;
	}
	else
		return false;
}

//2->L    (0, 0)	(+1, 0)	(+1, +1)	(0, -2)	(+1, -2)
bool SuperRotationSystem::srsOther2toL()
{
	
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, 0))
	{
		setNewPositionAndRotate(+1, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, +1))
	{
		setNewPositionAndRotate(+1, +1);
		return true;
	}
	else if (rotationTestBySRS(0, -2))
	{
		setNewPositionAndRotate(0, -2);
		return true;
	}
	else if (rotationTestBySRS(+1, -2))
	{
		setNewPositionAndRotate(+1, -2);
		return true;
	}
	else
		return false;
}

//L->0	  (0, 0)	(-1, 0)	(-1, -1)	(0, +2)	(-1, +2)
bool SuperRotationSystem::srsOtherLto0()
{
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, 0))
	{
		setNewPositionAndRotate(-1, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, -1))
	{
		setNewPositionAndRotate(-1, -1);
		return true;
	}
	else if (rotationTestBySRS(0, +2))
	{
		setNewPositionAndRotate(0, +2);
		return true;
	}
	else if (rotationTestBySRS(-1, +2))
	{
		setNewPositionAndRotate(-1, +2);
		return true;
	}
	else
		return false;
}


//I Tetromino Wall Kick Data
//      Test 1	Test 2	Test 3	Test 4	    Test 5
//0->R  (0, 0)	(-2, 0)	(+1, 0)	(-2, -1)	(+1, +2)
//R->0	(0, 0)	(+2, 0)	(-1, 0)	(+2, +1)	(-1, -2)
//R->2	(0, 0)	(-1, 0)	(+2, 0)	(-1, +2)	(+2, -1)
//2->R  (0, 0)	(+1, 0)	(-2, 0)	(+1, -2)	(-2, +1)
//2->L  (0, 0)	(+2, 0)	(-1, 0)	(+2, +1)	(-1, -2)
//L->2	(0, 0)	(-2, 0)	(+1, 0)	(-2, -1)	(+1, +2)
//L->0	(0, 0)	(+1, 0)	(-2, 0)	(+1, -2)	(-2, +1)
//0->L  (0, 0)	(-1, 0)	(+2, 0)	(-1, +2)	(+2, -1)
bool SuperRotationSystem::srsI_0toR()
{
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(-2, 0))
	{
		setNewPositionAndRotate(-2, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, 0))
	{
		setNewPositionAndRotate(+1, 0);
		return true;
	}
	else if (rotationTestBySRS(-2, -1))
	{
		setNewPositionAndRotate(-2, -1);
		return true;
	}
	else if (rotationTestBySRS(+1, +2))
	{
		setNewPositionAndRotate(+1, +2);
		return true;
	}
	else
		return false;
}

//R->2	(0, 0)	(-1, 0)	(+2, 0)	(-1, +2)	(+2, -1)
bool SuperRotationSystem::srsI_Rto2()
{
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, 0))
	{
		setNewPositionAndRotate(-1, 0);
		return true;
	}
	else if (rotationTestBySRS(+2, 0))
	{
		setNewPositionAndRotate(+2, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, +2))
	{
		setNewPositionAndRotate(-1, +2);
		return true;
	}
	else if (rotationTestBySRS(+2, -1))
	{
		setNewPositionAndRotate(+2, -1);
		return true;
	}
	else
		return false;
}

//2->L  (0, 0)	(+2, 0)	(-1, 0)	(+2, +1)	(-1, -2)
bool SuperRotationSystem::srsI_2toL()
{
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(+2, 0))
	{
		setNewPositionAndRotate(+2, 0);
		return true;
	}
	else if (rotationTestBySRS(-1, 0))
	{
		setNewPositionAndRotate(-1, 0);
		return true;
	}
	else if (rotationTestBySRS(+2, +1))
	{
		setNewPositionAndRotate(+2, +1);
		return true;
	}
	else if (rotationTestBySRS(-1, -2))
	{
		setNewPositionAndRotate(-1, -2);
		return true;
	}
	else
		return false;
}

//L->0	(0, 0)	(+1, 0)	(-2, 0)	(+1, -2)	(-2, +1)
bool SuperRotationSystem::srsI_Lto0()
{
	if (rotationTestBySRS(0, 0))
	{
		setNewPositionAndRotate(0, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, 0))
	{
		setNewPositionAndRotate(+1, 0);
		return true;
	}
	else if (rotationTestBySRS(-2, 0))
	{
		setNewPositionAndRotate(-2, 0);
		return true;
	}
	else if (rotationTestBySRS(+1, -2))
	{
		setNewPositionAndRotate(+1, -2);
		return true;
	}
	else if (rotationTestBySRS(-2, +1))
	{
		setNewPositionAndRotate(-2, +1);
		return true;
	}
	else
		return false;
}

void SuperRotationSystem::setNewPositionAndRotate(int x, int y)
{
	Point tetroCurPosition = getCurTetro()->getPosition();
	getCurTetro()->setPositionX(tetroCurPosition.x + x * BLOCK_WIDTH);
	getCurTetro()->setPositionY(tetroCurPosition.y + y * BLOCK_WIDTH);
	getCurTetro()->doRotation();
}