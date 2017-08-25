
#include "CPlatform.h"



CPlatform::CPlatform()
{

}

CPlatform::~CPlatform()
{

}

void CPlatform::Create(CMap *tpMap, Layer *tpLayer, int ObjectNum)
{
	mpSprite = Sprite::create("float.png");
	mpSprite->setPosition(tpMap->PlatformPos(ObjectNum));
	mOriginVec = mpSprite->getPosition();
	tpLayer->addChild(mpSprite, 1);
}
void CPlatform::SetScene(Node *tpNode)
{
	mpNode = tpNode;
}
void CPlatform::Hide()
{
	mpSprite->setVisible(false);
}
void CPlatform::Show()
{
	mpSprite->setVisible(true);
}
void CPlatform::SetPosition(Vec2 tVec)
{

}
Vec2 CPlatform::GetPosition()
{
	return mpSprite->getPosition();
}

Sprite* CPlatform::GetSprite()
{
	return mpSprite;
}

void CPlatform::FallAndReset(Node *tpNode)
{
	if (mState == 0)
	{
		auto tFall = MoveBy::create(2.0f, Vec2(0.0f, -150.0f));
		tFall->retain();

		auto tSequence = Sequence::create(
			tFall,
			CallFunc::create(CC_CALLBACK_0(CPlatform::SetOriginPos, this)),
			NULL);
		mpSprite->runAction(tSequence);
		mState = 1;
	}
}

void CPlatform::SetOriginPos()
{
	mpSprite->setPosition(mOriginVec);
	mState = 0;
}

