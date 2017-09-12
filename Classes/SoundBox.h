
#ifndef SoundBox_hpp
#define SoundBox_hpp
#include "cocos2d.h"
#include <stdio.h>

#include <vector>

using namespace std;

class SoundBox
{
private:

	static SoundBox *mpInstance;

	SoundBox();
	~SoundBox();

	string mStringBGMArray[7] = { "" };
	string mStringEffectArray[3] = { "" };

public:
	static SoundBox *GetInstance();

	void Create();
	void Destroy();

	void PlayBGM(int tIndex, bool tIsLoop = true);
	void StopBGM();

	void PlayEffect(int tIndex);
	void StopAllEffects();

	void ResumeBGM();

};

#endif /* SoundBox_h */