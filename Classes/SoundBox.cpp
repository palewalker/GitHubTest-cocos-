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
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);

	mStringBGMArray[0] = "Sounds/title.mp3";
	mStringBGMArray[1] = "Sounds/Stage1.mp3";
	mStringBGMArray[2] = "Sounds/Stage2.mp3";
	mStringBGMArray[3] = "Sounds/Stage3.mp3";
	mStringBGMArray[4] = "Sounds/Stage4.mp3";
	mStringBGMArray[5] = "Sounds/Stage5.mp3";
	mStringBGMArray[6] = "Sounds/Ending.mp3";
	mStringEffectArray[0] = "Sounds/shoot.wav";
	mStringEffectArray[1] = "Sounds/gameover.mp3";
	mStringEffectArray[2] = "Sounds/Jump.wav";
	

	int ti = 0;
	int tCount = 0;

	tCount = 7;

	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(mStringBGMArray[ti].c_str());
	}

	tCount = 3;
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
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}



void SoundBox::PlayEffect(int tIndex)
{
	SimpleAudioEngine::getInstance()->playEffect(mStringEffectArray[tIndex].c_str());
}
void SoundBox::StopAllEffects()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundBox::ResumeBGM()
{
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}