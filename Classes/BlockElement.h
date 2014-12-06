#ifndef BLOCK_BLOCK_ELEMENT
#define BLOCK_BLOCK_ELEMENT

#include "cocos2d.h"

#include "Block.h"

USING_NS_CC;


class BlockElement :public Block
{
public:
	
	static BlockElement* create(BlockDef&);

	virtual bool init() override;

	BlockElement(BlockDef&);
	
	~BlockElement();

	void reShowing(BlockDef&);

	void lockOn();
private:

	virtual std::string getBlockFileName() override;

};
#endif