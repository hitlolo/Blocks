#pragma once

class HUDDelegate
{
public:
	virtual void addLine(int) = 0;

	virtual void addScore() = 0;

	virtual void addSpeed() = 0;

	virtual void addCombo() = 0;
};