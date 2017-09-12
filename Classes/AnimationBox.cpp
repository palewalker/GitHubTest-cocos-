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

void AnimationBox::Create(int type, string tAniName, int tTotalFrameCount, float tDelayTime)
{
	mType = type;
	if (1 == type)//스프라이트 시트로 만들기
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

		tAnimate = Animate::create(tAnimation);
		tRepeatForeverC = RepeatForever::create(tAnimate);

		tRepeatForeverC->retain();
	}
	else if (2 == type) //스프라이트 연속해서 붙여 만들기
	{
		tSpriteC = Sprite::create(tAniName + "_0.png");

		auto tAnimation = Animation::create();
		tAnimation->setDelayPerUnit(tDelayTime);

		char tStr[512];
		

		for (int i = 0; i < tTotalFrameCount; i++)
		{
			memset(tStr, 0, 512);
			string tFilePath = tAniName;
			char ti[8];
			memset(ti, 0, 8);
			sprintf(ti, "_%d.png", i);
			tFilePath.append(ti);
			log("%s", tFilePath);
			sprintf(tStr, "%s_%d.png", tAniName, i);
			tAnimation->addSpriteFrameWithFile(tFilePath);
		}
		tAnimate = Animate::create(tAnimation);
		
	}
	

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
	if (1 == mType)
	{
		tSpriteC->runAction(tRepeatForeverC);
	}
	else if (2 == mType)
	{
		tSpriteC->runAction(tAnimate);
	}
}

void AnimationBox::RunAction(Action* tpAction)
{
	tSpriteC->runAction(tpAction);
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

Sprite* AnimationBox::GetSprite()
{
	return tSpriteC;
}