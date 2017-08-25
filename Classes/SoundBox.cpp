#include "SoundBox.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

SoundBox *SoundBox::mpInstance = NULL;

SoundBox::SoundBox()
{
}

SoundBox::~SoundBox()
{
}

SoundBox *SoundBox::GetInstance()
{
	if (NULL == mpInstance)
	{
		mpInstance = new SoundBox();
		return  mpInstance;
	}
	return mpInstance;
}

void SoundBox::Create()
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	mStringBGMArray[0] = "Sounds/tothemoon.mp3";
	mStringBGMArray[1] = "Sounds/background.mp3";
	mStringBGMArray[2] = "Sounds/Athletic.mp3";
	mStringBGMArray[3] = "Sounds/start.mp3";
	mStringEffectArray[0] = "Sounds/effect2.mp3";
	mStringEffectArray[1] = "Sounds/flip.wav";
	

	int ti = 0;
	int tCount = 0;

	tCount = 4;

	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(mStringBGMArray[ti].c_str());
	}

	tCount = 2;
	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(mStringEffectArray[ti].c_str());
	}

}
void SoundBox::Destroy()
{
	SimpleAudioEngine::getInstance()->unloadEffect(mStringEffectArray[0].c_str());
	
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::end();
	
}


void SoundBox::PlayBGM(int tIndex, bool tIsLoop)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(mStringBGMArray[tIndex].c_str(),
		tIsLoop);
}

void SoundBox::StopBGM()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundBox::PlayEffect(int tIndex)
{
	SimpleAudioEngine::getInstance()->playEffect(mStringEffectArray[tIndex].c_str());
}
void SoundBox::StopAllEffects()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}