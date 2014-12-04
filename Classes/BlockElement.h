#ifndef BLOCK_BLOCK_ELEMENT
#define BLOCK_BLOCK_ELEMENT

#include "cocos2d.h"
#include "GameData.h"
#include "GameBoard.h"
USING_NS_CC;

class BlockElement :public Sprite
{
public:
	
	static BlockElement* create(BlockDef&);

	virtual bool init() override;

	BlockElement(BlockDef&);
	
	~BlockElement();

	Point toBoardCoordinate();

	void reShowing();
private:

	void createByDef(const BlockDef&);

	CC_SYNTHESIZE_PASS_BY_REF(BlockDef, blockDef, BlockDefinition);

	Point parentCenter;

	Point getParentCenter();

	void setParentCenter();

	std::string getBlockFileName();

	void createByFieldLaw(const BlockDef& block_def);

	void createByTetroLaw(const BlockDef& block_def);

	bool isMeEmpty();

	bool leftAble();

	bool rightAble();

	bool downAble();

	bool rotateAble(int = 0,int = 0); 
	
	void resetOccupySituation();

	void resetSowingSituation(FieldOrTetro);

	class GameBoard* getGameBoard();
};
#endif