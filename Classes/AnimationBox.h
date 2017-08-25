#pragma once

#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
using namespace std;



/*

created by pokpoongryu


스프라이트 애니메이션을 담당하는 클래스.


*/
class AnimationBox
{
protected:
	Node *mpNode = NULL;


	string mAniName = "";

	int mTotalFrameCount = 0;
	float mDelayTime = 0.0f;

	//코코스객체
	Sprite *tSpriteC = NULL;
	Repeat *tRepeatForeverC = NULL;



	cocos2d::Vector<SpriteFrame *> tSpriteFrameVec;


public:
	AnimationBox();
	~AnimationBox();

	void Create(string tAniName, int tTotalFrameCount, float tDelayTime);
	void Destroy();

	void Build();       //HelloWorld에 addChild한다.
	void UnBuild();     //HelloWorld에서 removeChild한다.


	void SetScene(Node *tpNode);


	void SetPosition(Vec2 tVec);

	void RunAni();
	void StopAni();

	void Show();
	void Hide();

	bool IsShow();
};
