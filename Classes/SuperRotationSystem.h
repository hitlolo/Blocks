#ifndef BLOCKS_SRS
#define BLOCKS_SRS

#include "cocos2d.h"
#include "Tetromino.h"
USING_NS_CC;


class SuperRotationSystem
{
private:
	static SuperRotationSystem* _srs;

public:

	static SuperRotationSystem* getInstance();

	CC_SYNTHESIZE(class Tetromino*, curTetro, CurTetro);

	SuperRotationSystem();

	~SuperRotationSystem();

	void doRotation(Tetromino*);

	bool rotationTestByTetroType(TETROMINO_TYPE);

	bool rotationTestI();

	bool rotationTestOther();

	bool rotationTestBySRS(int x, int y);

	void setNewPositionAndRotate(int x, int y);

	bool srsOther0toR();

	bool srsOtherRto2();

	bool srsOther2toL();

	bool srsOtherLto0();

	bool srsI_0toR();

	bool srsI_Rto2();

	bool srsI_2toL();

	bool srsI_Lto0();

};
#endif