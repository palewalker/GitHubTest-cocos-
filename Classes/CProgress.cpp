
#include "CProgress.h"


CProgress::CProgress()
{
	Clear();
}
CProgress::~CProgress()
{
	Destroy();
}


void CProgress::Clear()
{
	mCurHP = 0.0f;
	mMaxHP = 0.0f;

	mHPUIRatio = 0.0f;


	mpParentNode = NULL;

	mpSprGuageBar = NULL;
	mpProgressTimer = NULL;
}

void CProgress::Create(float tCurHP, float tMaxHP)
{
	//data
	mCurHP = tCurHP;
	mMaxHP = tMaxHP;

	//ui
	mpSprGuageBar = Sprite::create("progress.png"); 
	
	mpSprGuageBar->retain();

	mpProgressTimer = ProgressTimer::create(mpSprGuageBar);
	mpProgressTimer->retain();

	mpProgressTimer->setAnchorPoint(Vec2(0, 0));
	mpProgressTimer->setScale(0.2f);

	mpProgressTimer->setType(ProgressTimer::Type::BAR);
	mpProgressTimer->setMidpoint(Vec2(0, 0));//
	mpProgressTimer->setBarChangeRate(Vec2(1, 0));

	mpProgressTimer->setReverseDirection(false);

	mpProgressTimer->setPercentage(100.0f);

}
void CProgress::Destroy()
{
	if (NULL != mpProgressTimer)
	{
		mpProgressTimer->release();
		mpProgressTimer = NULL;
	}


	Clear();
}

void CProgress::SetScene(Node *tpParentNode)
{
	mpParentNode = tpParentNode;
}

void CProgress::AddToScene()
{
	mpParentNode->addChild(mpProgressTimer);
}
void CProgress::RemoveFromScene()
{
	mpParentNode->removeChild(mpProgressTimer);
}

void CProgress::SetPosition(Vec2 tVec)
{
	mpProgressTimer->setPosition(tVec);
}



void CProgress::BuildGuageWithDamage(float tDamage)
{
	//build data
	mCurHP = mCurHP - tDamage;


	//tDamage : mMaxHP = x : 100

	float tRatio = (100.0f*mCurHP) / mMaxHP;




	//build ui
	//clean
	//build

	//auto tpAction = ProgressTo::create(1, tRatio);//100);
	//mpProgressTimer->runAction(RepeatForever::create(tpAction));

	mpProgressTimer->setPercentage(tRatio);
}
