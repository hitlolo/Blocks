#include "Block.h"


bool Block::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;

}


void Block::createByDef(const BlockDef& block_def)
{
	float positionX = (block_def._coordinateX) * BLOCK_WIDTH;
	float positionY = ((block_def._coordinateY)) * BLOCK_WIDTH;
	this->setPosition(positionX, positionY);
	this->initWithSpriteFrameName(getBlockFileName());
	this->setAnchorPoint(Point(0, 0));

}

Point Block::getParentCenter()
{
	if (blockDef._isFieldOrTetro == TETROMINO)
	{
		return parentCenter;
	}
	else
		return Point(Point::ZERO);
}

void Block::setParentCenter()
{
	Point p_position = this->getParent()->getPosition();
	float p_position_x = p_position.x + BLOCK_WIDTH * 2;
	float p_position_y = p_position.y + BLOCK_HEIGHT * 2;

	int center_x = p_position_x / BLOCK_WIDTH;
	int center_y = p_position_y / BLOCK_WIDTH;

	parentCenter = (Point(center_x, center_y));
}

bool Block::isMeEmpty()
{
	return !(this->getBlockDefinition()._isOccupOrEmpty);
}

bool Block::leftAble()
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

bool Block::rightAble()
{
	Point curPosition = this->toBoardCoordinate();
	Point newPosition = Point(curPosition.x + 1, curPosition.y);
	if (newPosition.x <= FIELD_RIGHT_BOARD && newPosition.y <= FIELD_TOP)
	{
		bool isMoveable = !(this->getGameBoard()->isPointOccupied(newPosition));
		//CCLOG("can i move:%d.Point!:%f,%f", isMoveable, newPosition.x, newPosition.y);
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

bool Block::downAble()
{
	Point curPosition = this->toBoardCoordinate();
	Point newPosition = Point(curPosition.x, curPosition.y - 1);
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

bool Block::rotateAble(int x, int y)
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

BoardInterface* Block::getGameBoard()
{
	if (blockDef._isFieldOrTetro == PLAYFIELD)
	{
		return (dynamic_cast<BoardInterface*>(this->getParent()));
	}
	else
		return (dynamic_cast<BoardInterface*>((this->getParent())->getParent()));
}

Point Block::toBoardCoordinate()
{

	this->setParentCenter();
	Point center = this->getParentCenter();
	//	CCLOG("%f,%f,my getParentCenter", center.x, center.y);
	int coodinate_x = getBlockDefinition()._coordinateX < 2 ?
		center.x - (2 - getBlockDefinition()._coordinateX) :
		center.x + (getBlockDefinition()._coordinateX - 2);
	int coodinate_y = getBlockDefinition()._coordinateY < 2 ?
		center.y + (getBlockDefinition()._coordinateY - 2) :
		center.y - (2 - getBlockDefinition()._coordinateY);

	//CCLOG("%d,%d,my coodinate", coodinate_x, coodinate_y);
	return Point(coodinate_x, coodinate_y);
}

void Block::switchShowing()
{
	this->resetOccupySituation();
	this->resetShowingSituation();
	
	std::string file_name = this->getBlockFileName();
	auto newFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	this->setSpriteFrame(newFrame);
}


void Block::resetOccupySituation()
{
	auto newDef = this->getBlockDefinition();
	newDef._isOccupOrEmpty = !newDef._isOccupOrEmpty;
	this->setBlockDefinition(newDef);
}


void Block::resetShowingSituation()
{
	auto curDef = this->getBlockDefinition();

	if (curDef._isOccupOrEmpty == OCCUPIED)
	{
		curDef._tetroType = getGameBoard()->getTetroType();
		this->setBlockDefinition(curDef);

	}
	else if (curDef._isOccupOrEmpty == EMPTY)
	{
		curDef._tetroType = TETROMINO_TYPE::NOTHING;
		this->setBlockDefinition(curDef);
	}

}