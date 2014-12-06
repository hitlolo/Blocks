#include "BlockGhost.h"

BlockGhost* BlockGhost::create(BlockDef& def)
{
	BlockGhost *block = new BlockGhost(def);
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

BlockGhost::BlockGhost(BlockDef& def)
{
	this->setBlockDefinition(def);
}

bool BlockGhost::init()
{
	if (!Block::init())
	{
		return false;
	}

	createByDef(getBlockDefinition());
	return true;

}



BlockGhost::~BlockGhost()
{

}

std::string BlockGhost::getBlockFileName()
{
	std::string file_name;

	if (getBlockDefinition()._isOccupOrEmpty == EMPTY)
	{
		file_name = "blockEmpty.png";
		
	}
	else
	{
		file_name = "blockGhost.png";
	}
	return file_name;
}