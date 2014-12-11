#pragma once

#include "cocos2d.h"
#include "GameData.h"

USING_NS_CC;


class BoardInterface
{
public:

	virtual bool isPointOccupied(Point point) = 0;

	virtual TETROMINO_TYPE getTetroType() = 0;

	virtual void gameOver() = 0; 

	virtual void setCurTop(int) = 0;

	virtual int  getCurTop() = 0;

	virtual void switchShowingForCell(Point) = 0;

	virtual void checkClear() = 0;
};