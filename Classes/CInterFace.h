#ifndef CInterFace_h
#define CInterFace_h
#include "cocos2d.h"
#include <stdio.h>
#include<iostream>



using namespace cocos2d;
using namespace std;

class CInterFace
{
private:
	

	
	
	static CInterFace *mpInstance;

	CInterFace();
	~CInterFace();
	
	Size winSize;
	Node *mpNode = NULL;
	Layer *InterFaceLayer = NULL;
	Label *mStageNumLbl = NULL;
	Label *mDeadCountLbl = NULL;
	Sprite *mJumpSpr = NULL;
	Sprite *mShotSpr = NULL;

	int mDeadCount = 0;
	int mStageNum = 0;






public:
	static CInterFace *GetInstance();


	void SetScene(Node *tpNode);
	void SetInterFace();
	void Update(float dt);
	Sprite* GetJumpBtn();
	Sprite* GetFireBtn();
	void DeadCountUP();
	void SetStageNum(int Stage);
	



};

#endif /* CInterFace_h */