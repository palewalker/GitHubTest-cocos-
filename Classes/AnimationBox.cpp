#include "AnimationBox.h"
#include "HelloWorldScene.h"


using namespace std;
USING_NS_CC;

AnimationBox::AnimationBox()
{
}

AnimationBox::~AnimationBox()
{

}

void AnimationBox::Create(string tAniName, int tTotalFrameCount, float tDelayTime)
{

	
	mAniName = tAniName + ".png";
	mTotalFrameCount = tTotalFrameCount;
	mDelayTime = tDelayTime;
	float tWidth = 0.0f;
	float tHeight = 0.0f;
	int tRow = 0;
	int tCol = 0;
	auto tSpriteSrc = Sprite::create(mAniName);
	
	auto tTexture = tSpriteSrc->getTexture();

	tWidth = ((tSpriteSrc->getContentSize().width) * 45) / 135;
	tHeight = ((tSpriteSrc->getContentSize().height) * 45) / 45;

	auto tAnimation = Animation::create();
	tAnimation->setDelayPerUnit(tDelayTime);

	for (int ti = 0; ti < mTotalFrameCount; ti++)
	{
	tRow = 0;
	tCol = ti % 3;
	tAnimation->addSpriteFrameWithTexture(tTexture, Rect(tCol*tWidth, tRow*tHeight, tWidth, tHeight));
	}
	tSpriteC = Sprite::create(mAniName, Rect(0, 0, tWidth, tHeight));
	tSpriteC->setScale(0.8f);
	tSpriteC->retain();

	auto tAnimate = Animate::create(tAnimation);
	tRepeatForeverC = RepeatForever::create(tAnimate);
	
	tRepeatForeverC->retain();
	


}
void AnimationBox::Destroy()
{
	if (tSpriteC != NULL)
	{
		tSpriteC->release();
		tSpriteC = NULL;
	}
	if (tRepeatForeverC != NULL)
	{
		tRepeatForeverC->release();
		tRepeatForeverC = NULL;

	}
	if (mpNode != NULL)
	{
		mpNode->release();
		mpNode = NULL;
	}

}

void AnimationBox::Build()
{
	mpNode->addChild(tSpriteC);
}//HelloWorld에 addChild한다.
void AnimationBox::UnBuild()
{

	mpNode->removeChild(tSpriteC);

}//HelloWorld에서 removeChild한다.


void AnimationBox::SetScene(Node *tpNode)
{
	mpNode = tpNode;
	mpNode->retain();
}


void AnimationBox::SetPosition(Vec2 tVec)
{
	tSpriteC->setPosition(tVec);
}

Vec2 AnimationBox::GetPosition()
{
	return tSpriteC->getPosition();
}

void AnimationBox::RunAni()
{
	
	tSpriteC->runAction(tRepeatForeverC);
}
void AnimationBox::StopAni()
{
	tSpriteC->stopAllActions();
}

void AnimationBox::Show()
{
	tSpriteC->setVisible(true);
}
void AnimationBox::Hide()
{
	tSpriteC->setVisible(false);
}

bool AnimationBox::IsShow()
{
	return tSpriteC->isVisible();
}