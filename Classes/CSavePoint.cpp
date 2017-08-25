
#include "CSavePoint.h"



CSavePoint::CSavePoint()
{

}

CSavePoint::~CSavePoint()
{

}

void CSavePoint::Create(CMap *tpMap,Layer *tpLayer, int ObjectNum)
{
	mpSprite = Sprite::create("save.png");
	mpSprite->setPosition(tpMap->SavePointPos(ObjectNum));
	mVec = mpSprite->getPosition();
	tpLayer->addChild(mpSprite, 1);
	
}
void CSavePoint::SetScene(Node *tpNode)
{
	mpNode = tpNode;
}
void CSavePoint::Hide()
{
	mpSprite->setVisible(false);
}
void CSavePoint::Show()
{
	mpSprite->setVisible(true);
}
void CSavePoint::SetPosition(Vec2 tVec)
{

}
Vec2 CSavePoint::GetPosition()
{
	return mVec;
}

Sprite* CSavePoint::GetSprite()
{
	return mpSprite;
}
