#ifndef BLOCK_GHOST_PIECE
#define BLOCK_GHOST_PIECE

#include "Block.h"
#include "cocos2d.h"

USING_NS_CC;

class BlockGhost:public Block
{
public:

	static BlockGhost* create(BlockDef&);

	virtual bool init() override;

	BlockGhost(BlockDef&);

	~BlockGhost();

private:
	virtual std::string getBlockFileName() override;
};

#endif