#pragma once

class DiscJockeyDelegate
{
public:

	virtual void playBackgroundMusic() = 0;

	virtual void playClickEffect() = 0;

	virtual void playMoveEffect() = 0;

	virtual void playLockOnEffect() = 0;

	virtual void playClearLineEffect() = 0;

	virtual bool isMusicOn() = 0;

	virtual bool isEffectOn() = 0;
};