#pragma once

#include "cocos2d.h"
#include "CInterFace.h"
#include "config.h"

using namespace cocos2d;

class CGameOver 
{
private:
	
	Sprite* mGameOverSpr = NULL;
	LayerColor *mBackLayer = NULL;
	Size winSize;
	int mCount = 0;
	int mState = DEAD;
	
	

public:
	CGameOver();
	~CGameOver();

	void Create(Node* tpNode);

	Sprite* GetSprite();
	
	int GetState();


	void Show();
	void Hide(int StageNum);
	bool IsShow();

};