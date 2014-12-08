
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
	music = true;
	effect = true;
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
	if (music)
	{
		audioEngine->playBackgroundMusic("Tetris.wav");
	}
}

void DiscJockey::playClickEffect()
{
	if (effect)
	{
		audioEngine->playEffect("buttons.wav");
	}
}

void DiscJockey::playMoveEffect()
{
	if (effect)
	{
		audioEngine->playEffect("buttons.wav");
	}
}

void DiscJockey::playLockOnEffect()
{
	if (effect)
	{
		audioEngine->playEffect("figurestop.wav");
	}
}

void DiscJockey::playClearLineEffect()
{
	if (effect)
	{
		audioEngine->playEffect("deletechips.wav");
	}
}

bool DiscJockey::isMusicOn()
{
	return getMusicOn();
}

bool DiscJockey::isEffectOn()
{
	return getEffectOn();
}