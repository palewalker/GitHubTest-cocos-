
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

	string mStringBGMArray[4] = { "" };
	string mStringEffectArray[2] = { "" };

public:
	static SoundBox *GetInstance();

	void Create();
	void Destroy();

	void PlayBGM(int tIndex, bool tIsLoop = true);
	void StopBGM();

	void PlayEffect(int tIndex);
	void StopAllEffects();

};

#endif /* SoundBox_h */