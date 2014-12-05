#include "BlockElement.h"



BlockElement* BlockElement::create(BlockDef& def)
{ 
	BlockElement *block = new BlockElement(def);
	if (block && block->init())
	{ 
		block->autorelease();
		return block;
	} 
	else 
	{ 
		CC_SAFE_DELETE(block);
		block = NULL;
		return NULL; 
	} 

}

BlockElement::BlockElement(BlockDef& def)
{	
	this->setBlockDefinition(def);
}

bool BlockElement::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	createByDef( getBlockDefinition() );

	return true;

}


void BlockElement::createByDef(const BlockDef& block_def)
{
	float positionX = (block_def._coordinateX) * BLOCK_WIDTH;
	float positionY = ((block_def._coordinateY)) * BLOCK_WIDTH;
	this->setPosition(positionX, positionY);
	this->initWithSpriteFrameName(getBlockFileName());
	this->setAnchorPoint(Point(0, 0));
	
}

BlockElement::~BlockElement()
{

}

void BlockElement::createByFieldLaw(const BlockDef& block_def)
{
	float positionX = (block_def._coordinateX) * BLOCK_WIDTH;
	float positionY = (PIECE_SIZE - (block_def._coordinateY)) * BLOCK_WIDTH;
	this->setPosition(positionX, positionY);
	this->initWithSpriteFrameName(getBlockFileName());
	this->setAnchorPoint(Point(0, 1));
	if (blockDef._isFieldOrTetro == TETROMINO)
	{
		this->setParentCenter();
	}
}

void createByTetroLaw()
{


}


std::string BlockElement::getBlockFileName()
{
	TETROMINO_TYPE type = this->getBlockDefinition()._tetroType;
	std::string file_name;

	if (getBlockDefinition()._isOccupOrEmpty == EMPTY)
	{
		file_name = "blockEmpty.png";
		return file_name;
	}
	else
	{
		switch (type)
		{
		case TETROMINO_TYPE::O:
			file_name = "blockYellowO.png";

			break;
		case TETROMINO_TYPE::I:
			file_name = "blockCyanI.png";
			break;
		case TETROMINO_TYPE::J:
			file_name = "blockBlueJ.png";
			break;
		case TETROMINO_TYPE::L:
			file_name = "blockOrangeL.png";
			break;
		case TETROMINO_TYPE::T:
			file_name = "blockPurpleT.png";
			break;
		case TETROMINO_TYPE::S:
			file_name = "blockGreenS.png";
			break;
		case TETROMINO_TYPE::Z:
			file_name = "blockRedZ.png";
			break;
		default:
			break;
		}
	}
	return file_name;
}


void BlockElement::switchShowing()
{
	this->resetOccupySituation();

	if (getBlockDefinition()._isFieldOrTetro == PLAYFIELD)
	{
	
		this->resetShowingSituation(PLAYFIELD);
	}
	else if (getBlockDefinition()._isFieldOrTetro == TETROMINO)
	{
		this->resetShowingSituation(TETROMINO);
	}

	std::string file_name = this->getBlockFileName();
	auto newFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	this->setSpriteFrame(newFrame);
}

void BlockElement::resetOccupySituation()
{
	auto newDef = this->getBlockDefinition();
	newDef._isOccupOrEmpty = !newDef._isOccupOrEmpty;
	this->setBlockDefinition(newDef);
}

void BlockElement::resetShowingSituation(FieldOrTetro isField)
{
	auto curDef = this->getBlockDefinition();

	if (isField && curDef._isOccupOrEmpty == OCCUPIED)
	{
		curDef._tetroType = (dynamic_cast<GameBoard*>(getParent()))->getCurTetromino()->getType();
		this->setBlockDefinition(curDef);
	
	}
	else if (isField && curDef._isOccupOrEmpty == EMPTY)
	{
		curDef._tetroType = TETROMINO_TYPE::NOTHING;
		this->setBlockDefinition(curDef);
	}

	if (!isField && curDef._isOccupOrEmpty == OCCUPIED)
	{
		curDef._tetroType = (dynamic_cast<Tetromino*>(getParent()))->getType();
		this->setBlockDefinition(curDef);

	}
	else if (!isField && curDef._isOccupOrEmpty == EMPTY)
	{
		curDef._tetroType = TETROMINO_TYPE::NOTHING;
		this->setBlockDefinition(curDef);

	}
	
}

//void BlockElement::reShowing()
//{
//	
//}
Point BlockElement::toBoardCoordinate()
{

	this->setParentCenter();
	Point center = this->getParentCenter();
//	CCLOG("%f,%f,my getParentCenter", center.x, center.y);
	int coodinate_x = getBlockDefinition()._coordinateX < 2 ?
		center.x - (2 - getBlockDefinition()._coordinateX) :
		center.x + (getBlockDefinition()._coordinateX - 2);
	int coodinate_y = getBlockDefinition()._coordinateY < 2 ?
		center.y + (getBlockDefinition()._coordinateY -2) :
		center.y - (2 -getBlockDefinition()._coordinateY );

	//CCLOG("%d,%d,my coodinate", coodinate_x, coodinate_y);
	return Point(coodinate_x, coodinate_y);
}

bool BlockElement::isMeEmpty()
{
	return !(this->getBlockDefinition()._isOccupOrEmpty);
}

bool BlockElement::leftAble()
{
	Point curPosition = this->toBoardCoordinate();
	Point newPosition = Point(curPosition.x - 1, curPosition.y);
	if (newPosition.x >= FIELD_LEFT_BOARD && newPosition.y <= FIELD_TOP)
	{
		bool isMoveable = !(this->getGameBoard()->isPointOccupied(newPosition));
		//CCLOG("can i move:%d.Point!:%f,%f", isMoveable, newPosition.x,newPosition.y);
		return isMoveable;
	}
	else if (newPosition.x < FIELD_LEFT_BOARD)
	{
		if (getBlockDefinition()._isOccupOrEmpty == OCCUPIED)
		{
			return false;
		}
		else
			return true;
	}
}

bool BlockElement::rightAble()
{
	Point curPosition = this->toBoardCoordinate();
	Point newPosition = Point(curPosition.x + 1, curPosition.y);
	if (newPosition.x <= FIELD_RIGHT_BOARD && newPosition.y <= FIELD_TOP)
	{
		bool isMoveable = !(this->getGameBoard()->isPointOccupied(newPosition));
		CCLOG("can i move:%d.Point!:%f,%f", isMoveable, newPosition.x, newPosition.y);
		return isMoveable;
	}
	else if (newPosition.x > FIELD_RIGHT_BOARD)
	{
		if (getBlockDefinition()._isOccupOrEmpty == OCCUPIED)
		{
			return false;
		}
		else
			return true;
	}
}

bool BlockElement::downAble()
{
	Point curPosition = this->toBoardCoordinate();
	Point newPosition = Point(curPosition.x , curPosition.y - 1);
	if (newPosition.y >= FIELD_BOTTOM && newPosition.y <= FIELD_TOP)
	{
		//CCLOG("can i move:.Point!:%f,%f", newPosition.x, newPosition.y);
		bool isMoveable = !(this->getGameBoard()->isPointOccupied(newPosition));
		
		return isMoveable;
	}
	else if (newPosition.y < FIELD_BOTTOM)
	{
		if (getBlockDefinition()._isOccupOrEmpty == OCCUPIED)
		{
			return false;
		}
		else
			return true;
	}
	else if (newPosition.y > FIELD_TOP)
	{
		return true;
	}
}

bool BlockElement::rotateAble(int x,int y)
{
	Point curPosition = this->toBoardCoordinate();
	curPosition.x += x;
	curPosition.y += y;
	//if (curPosition.x < 0 || curPosition.x > 9 || curPosition.y < 0 || curPosition.y > 19)
	if (curPosition.x < FIELD_LEFT_BOARD || curPosition.x > FIELD_RIGHT_BOARD || curPosition.y < FIELD_BOTTOM)
	{
		return false;
	}
	else if (curPosition.y > FIELD_TOP)
	{
		return true;
	}
	else
	{
		return !(this->getGameBoard()->isPointOccupied(curPosition));
	}
	
}


Point BlockElement::getParentCenter()
{
	if (blockDef._isFieldOrTetro == TETROMINO)
	{
		return parentCenter;
	}
	else
		return Point(Point::ZERO);
}
void BlockElement::setParentCenter()
{
	Point p_position = this->getParent()->getPosition();
	float p_position_x = p_position.x + BLOCK_WIDTH * 2;
	float p_position_y = p_position.y + BLOCK_HEIGHT * 2;

	int center_x = p_position_x / BLOCK_WIDTH;
	int center_y = p_position_y / BLOCK_WIDTH;

	parentCenter = (Point(center_x, center_y));
}

GameBoard* BlockElement::getGameBoard()
{
	return (dynamic_cast<GameBoard*>((dynamic_cast<Tetromino*>(getParent()))->getParent()));
}

void BlockElement::lockOn()
{
	Point point = this->toBoardCoordinate();
	if (point.x >= FIELD_LEFT_BOARD && point.x <= FIELD_RIGHT_BOARD && point.y >= FIELD_BOTTOM && point.y <= FIELD_TOP)
	{
		this->getGameBoard()->switchShowing(point);
		if (point.y > this->getGameBoard()->getCurTop() && point.y < FIELD_TOP)
		{
			this->getGameBoard()->setCurTop(point.y);
			this->getGameBoard()->checkClear();
		}

		if (point.y == FIELD_TOP)
		{
			this->getGameBoard()->gameOver();
		}
		
	}
	
}

void BlockElement::reShowing(BlockDef& def)
{
	this->setBlockDefinition(def);
	std::string file_name = this->getBlockFileName();
	auto newFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	this->setSpriteFrame(newFrame);
}
