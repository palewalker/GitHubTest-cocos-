
#include "CJumpPoint.h"



CJumpPoint::CJumpPoint()
{

}

CJumpPoint::~CJumpPoint()
{

}

void CJumpPoint::Create(CMap *tpMap, Layer *tpLayer, int ObjectNum)
{
	mpSprite = Sprite::create("multijump.png");
	mpSprite->setPosition(tpMap->JumpPointPos(ObjectNum));
	mVec = mpSprite->getPosition();
	mpSprite->setAnchorPoint(Vec2(0.5f, 0));
	tpLayer->addChild(mpSprite, 1);
}
void CJumpPoint::SetScene(Node *tpNode)
{
	mpNode = tpNode;
}
void CJumpPoint::Hide()
{
	mpSprite->setVisible(false);
}
void CJumpPoint::Show()
{
	mpSprite->setVisible(true);
}
void CJumpPoint::SetPosition(Vec2 tVec)
{

}
Vec2 CJumpPoint::GetPosition()
{
	return mVec;
}

Sprite* CJumpPoint::GetSprite()
{
	return mpSprite;
}

void CJumpPoint::Reset()
{
	if (DEAD == mState)
	{
		mState = ALIVE;
		mpSprite->setVisible(true);
	}
}
int CJumpPoint::GetState()
{
	return mState;
}
void CJumpPoint::SetUsed()
{
	mpSprite->setVisible(false);
	mState = DEAD;
}

