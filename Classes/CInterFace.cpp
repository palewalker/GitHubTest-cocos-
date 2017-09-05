#include "CInterFace.h"



using namespace cocos2d;

#define CharacterType1 1
#define CharacterType2 2

CInterFace *CInterFace::mpInstance = NULL;

CInterFace::CInterFace()
{

}

CInterFace::~CInterFace()
{

}

CInterFace *CInterFace::GetInstance()
{
	if (NULL == mpInstance)
	{
		mpInstance = new CInterFace();
		return mpInstance;
	}

	return mpInstance;
}

void CInterFace::SetScene(Node *tpNode)
{
	mpNode = tpNode;
}

void CInterFace::SetInterFace()
{
	InterFaceLayer = Layer::create();
	mpNode->addChild(InterFaceLayer, 103);//인터페이스용 레이어

	winSize = Director::getInstance()->getWinSize();

	mStageNumLbl = Label::createWithTTF("Stage :", "fonts/Marker Felt.ttf", 24);
	mStageNumLbl->setColor(Color3B(255, 255, 255));
	mStageNumLbl->setPosition(Vec2(winSize.width/2, winSize.height/10 * 9.5));
	InterFaceLayer->addChild(mStageNumLbl);																											

	mDeadCountLbl = Label::createWithTTF("DeadCount :", "fonts/Marker Felt.ttf", 24);
	mDeadCountLbl->setColor(Color3B(255, 255, 255));
	mDeadCountLbl->setPosition(Vec2(winSize.width / 10 * 9 , winSize.height / 10 * 9.5));
	InterFaceLayer->addChild(mDeadCountLbl);

	

	mJumpSpr = Sprite::create("JumpBtn.png");
	mJumpSpr->setPosition(Vec2(winSize.width / 10 * 8, winSize.height/10 * 1.5f));
	mJumpSpr->setScale(1.5f);
	InterFaceLayer->addChild(mJumpSpr);


	mShotSpr = Sprite::create("ShotBtn.png");
	mShotSpr->setPosition(Vec2(winSize.width / 10 * 9, winSize.height / 10 * 1.5f));
	mShotSpr->setScale(1.5f);
	InterFaceLayer->addChild(mShotSpr);
	
	

	
}

void CInterFace::Update(float dt)
{
	char tStr[512];
	memset(tStr, 0, 512);
	sprintf(tStr, "DeadCount: %i", mDeadCount);
	mDeadCountLbl->setString(tStr);

}

Sprite* CInterFace::GetJumpBtn()
{
	return mJumpSpr;
}
Sprite* CInterFace::GetFireBtn()
{
	return mShotSpr;
}


void CInterFace::DeadCountUP()
{
	mDeadCount++;
}

