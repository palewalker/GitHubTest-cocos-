#pragma once

#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
using namespace std;



/*

created by pokpoongryu


��������Ʈ �ִϸ��̼��� ����ϴ� Ŭ����.


*/
class AnimationBox
{
protected:
	Node *mpNode = NULL;


	string mAniName = "";

	int mTotalFrameCount = 0;
	float mDelayTime = 0.0f;

	//���ڽ���ü
	Sprite *tSpriteC = NULL;
	Repeat *tRepeatForeverC = NULL;



	cocos2d::Vector<SpriteFrame *> tSpriteFrameVec;


public:
	AnimationBox();
	~AnimationBox();

	void Create(string tAniName, int tTotalFrameCount, float tDelayTime);
	void Destroy();

	void Build();       //HelloWorld�� addChild�Ѵ�.
	void UnBuild();     //HelloWorld���� removeChild�Ѵ�.


	void SetScene(Node *tpNode);


	void SetPosition(Vec2 tVec);

	void RunAni();
	void StopAni();

	void Show();
	void Hide();

	bool IsShow();
};
