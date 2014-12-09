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
	if (!Block::init())
	{
		return false;
	}

	createByDef(getBlockDefinition());
	return true;

}



BlockElement::~BlockElement()
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


void BlockElement::lockOn()
{
	Point point = this->toBoardCoordinate();


	if (point.x >= FIELD_LEFT_BOARD && point.x <= FIELD_RIGHT_BOARD && point.y >= FIELD_BOTTOM && point.y <= FIELD_TOP)
	{
		this->getGameBoard()->switchShowing(point);
		if (point.y > this->getGameBoard()->getCurTop() && point.y <= FIELD_TOP)
		{
			this->getGameBoard()->setCurTop(point.y);
			this->getGameBoard()->checkClear();
		}
	}

	if (point.y > FIELD_TOP)
	{
		this->getGameBoard()->setCurTop(point.y);

		return;
	}

	
}

void BlockElement::reShowing(BlockDef& def)
{
	this->setBlockDefinition(def);
	std::string file_name = this->getBlockFileName();
	auto newFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name);
	this->setSpriteFrame(newFrame);
}
