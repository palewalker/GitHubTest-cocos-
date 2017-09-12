#pragma once

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;


class CProgress
{
protected:
	//data
	float mCurHP = 0.0f;
	float mMaxHP = 0.0f;

	float mHPUIRatio = 0.0f;

protected:
	//ui
	Node *mpParentNode = NULL;

	cocos2d::Sprite* mpSprGuageBar = NULL;
	ProgressTimer *mpProgressTimer = NULL;

public:
	CProgress();
	~CProgress();

	void Clear();
	void Clean();

	void Create(float tCurHP, float tMaxHP);
	void Destroy();

	void SetScene(Node *tpParentNode);

	void AddToScene();
	void RemoveFromScene();


	void SetPosition(Vec2 tVec);


	void BuildGuageWithDamage(float tDamage);
};

