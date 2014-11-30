#ifndef BLOCK_BLOCK_ELEMENT
#define BLOCK_BLOCK_ELEMENT

#include "cocos2d.h"
#include "GameData.h"

USING_NS_CC;

class BlockElement :public Sprite
{
public:
	
	virtual bool init() override;

	static BlockElement* create(BlockDef&);

	BlockElement(BlockDef&);
	
	~BlockElement();

private:

	void createByType(const BlockDef&);

	CC_SYNTHESIZE_PASS_BY_REF(BlockDef, blockDef, BlockDefinition);



};
#endif