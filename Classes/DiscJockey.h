#ifndef BLOCK_DJ
#define BLOCK_DJ

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "DiscJockeyDelegate.h"

USING_NS_CC;

//using namespace CocosDenshion;

class DiscJockey:public DiscJockeyDelegate
{
public:
	static DiscJockey* getInstance();

	DiscJockey();

	~DiscJockey();

	CC_SYNTHESIZE(bool, isMusicOn, MusicOn);

	CC_SYNTHESIZE(bool, isEffectOn, EffectOn);

	virtual void playBackgroundMusic() override;

	virtual void playClickEffect() override;

	virtual void playMoveEffect() override;

	virtual void playLockOnEffect() override;

	virtual void playClearLineEffect() override;

	void preLoad();

	void unLoad(std::string);

private:
	static DiscJockey* _dj;

	CocosDenshion::SimpleAudioEngine* audioEngine;

};


#endif