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

	createByType( getBlockDefinition() );

	return true;

}


void BlockElement::createByType(const BlockDef& block_def)
{
//	this->setContentSize(Size(BLOCK_WIDTH, BLOCK_WIDTH));
	
	float positionX = (block_def._coordinateX) * BLOCK_WIDTH;
	float positionY = (PIECE_HEIGHT - (block_def._coordinateY)) * BLOCK_WIDTH;
	this->setPosition(positionX, positionY);

	if (block_def._isBlock == IS_BLOCK::EMPTY)
	{
		return;
	}

	TETROMINO_TYPE type = block_def._type;
	std::string file_name;
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
	}
	this->initWithSpriteFrameName(file_name);
//	this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name));
//	this->initWithFile("blockGreenS.png");
	this->setAnchorPoint(Point(0, 1));
}

BlockElement::~BlockElement()
{

}
