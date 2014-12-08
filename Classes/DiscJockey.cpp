
#include "DiscJockey.h"

DiscJockey* DiscJockey::_dj = nullptr;

DiscJockey* DiscJockey::getInstance()
{
	if (!_dj)
	{
		_dj = new DiscJockey();
		return _dj;
	}
	else
	{
		return _dj;
	}
}

DiscJockey::DiscJockey()
{
	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	isMusicOn = true;
	isEffectOn = true;
}

DiscJockey::~DiscJockey()
{
	CC_SAFE_DELETE(_dj);
}

void DiscJockey::preLoad()
{
	audioEngine->preloadBackgroundMusic("Tetris.wav");
	audioEngine->preloadEffect("buttons.wav");
	audioEngine->preloadEffect("deletechips.wav");
	audioEngine->preloadEffect("figurestop.wav");
}

void DiscJockey::unLoad(std::string file)
{
	audioEngine->unloadEffect(file.c_str());

}


void DiscJockey::playBackgroundMusic()
{
	if (isMusicOn)
	{
		audioEngine->playBackgroundMusic("Tetris.wav");
	}
}

void DiscJockey::playClickEffect()
{
	if (isEffectOn)
	{
		audioEngine->playEffect("buttons.wav");
	}
}

void DiscJockey::playMoveEffect()
{
	if (isEffectOn)
	{
		audioEngine->playEffect("buttons.wav");
	}
}

void DiscJockey::playLockOnEffect()
{
	if (isEffectOn)
	{
		audioEngine->playEffect("figurestop.wav");
	}
}

void DiscJockey::playClearLineEffect()
{
	if (isEffectOn)
	{
		audioEngine->playEffect("deletechips.wav");
	}
}