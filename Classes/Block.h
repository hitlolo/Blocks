#ifndef BLOCK_BASE
#define BLOCK_BASE

#include "cocos2d.h"
#include "GameData.h"
#include "BoardInterface.h"

USING_NS_CC;

class Block:public Sprite
{
public:

	virtual bool init() override;

	Point toBoardCoordinate();

	void  switchShowing();

protected:

	CC_SYNTHESIZE_PASS_BY_REF(BlockDef, blockDef, BlockDefinition);

	void createByDef(const BlockDef&);

	virtual std::string getBlockFileName() = 0;

	Point parentCenter;

	Point getParentCenter();

	void  setParentCenter();

	bool  isMeEmpty();

	bool  leftAble();

	bool  rightAble();

	bool  downAble();

	bool  rotateAble(int = 0, int = 0);

	BoardInterface* getGameBoard();

	void resetOccupySituation();

	void resetShowingSituation();

};



#endif