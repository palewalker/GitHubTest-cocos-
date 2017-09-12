
#include "CScroll.h"



CScroll::CScroll()
{
	mpLayer = NULL;

	mpSpriteA = NULL;
	AVec = Vec2(0, 0);

	mpSpriteB = NULL;
	BVec = Vec2(0, 0);

	mScrollSpeed = 0.0f;
	mZOrder = 0.0f;
}

CScroll::~CScroll()
{

}

void CScroll::Create(float tScrollSpeed, float tZOrder)
{
	mScrollSpeed = tScrollSpeed;
	mZOrder = tZOrder;

	auto tSpriteSrc = Sprite::create("bg.png");
	auto tTexture = tSpriteSrc->getTexture();

	auto tSpriteSrcB = Sprite::create("BackGround5.png");
	auto tTextureB = tSpriteSrcB->getTexture();




	mpSpriteA = Sprite::createWithTexture(tTexture);
	//mpSpriteA = Sprite::create("bg.png");
	mpSpriteA->retain();
	mpSpriteA->setAnchorPoint(Vec2(0.0f, 0.0f));


	mpSpriteB = Sprite::createWithTexture(tTexture);
	//mpSpriteB = Sprite::create("bg.png");
	mpSpriteB->retain();
	mpSpriteB->setAnchorPoint(Vec2(0.0f, 0.0f));

	mpSpriteC = Sprite::createWithTexture(tTextureB);
	mpSpriteC->retain();
	mpSpriteC->setAnchorPoint(Vec2(0.0f, 0.0f));
	
	mpSpriteD = Sprite::createWithTexture(tTextureB);
	mpSpriteD->retain();
	mpSpriteD->setAnchorPoint(Vec2(0.0f, 0.0f));




	AVec.x = 0.0f;
	AVec.y = 0.0f;
	mpSpriteA->setPosition(AVec);

	BVec.x = 0.0f;
	BVec.y = mpSpriteA->getContentSize().height;
	mpSpriteB->setPosition(BVec);

	tHeight = mpSpriteA->getContentSize().height;

	CVec.x = 0.0f;
	CVec.y = 0.0f;
	mpSpriteC->setPosition(CVec);

	DVec.x = 0.0f;
	DVec.y = mpSpriteD->getContentSize().height;
	mpSpriteD->setPosition(DVec);

	tHeightB = mpSpriteC->getContentSize().height;
}
void CScroll::SetScene(Layer *tpNode)
{
	mpLayer = tpNode;
}
void CScroll::Build()
{
	mpLayer->addChild(mpSpriteA, mZOrder);
	mpLayer->addChild(mpSpriteB, mZOrder);

	mpLayer->addChild(mpSpriteC, mZOrder-1);
	mpLayer->addChild(mpSpriteD, mZOrder-1);
}
void CScroll::UnBuild()
{
	mpLayer->removeChild(mpSpriteA, mZOrder);
	mpLayer->removeChild(mpSpriteB, mZOrder);
}
void CScroll::UpdateScroll(float dt)
{
	AVec.y = AVec.y - mScrollSpeed * dt*2;
	mpSpriteA->setPosition(AVec);

	BVec.y = BVec.y - mScrollSpeed *dt*2;
	mpSpriteB->setPosition(BVec);

	if (AVec.y <= -tHeight)
	{
		AVec.y = tHeight;
	}

	if (BVec.y <= -tHeight)
	{
		BVec.y = tHeight;
	}

	CVec.y = CVec.y - mScrollSpeed * dt/2;
	mpSpriteC->setPosition(CVec);

	DVec.y = DVec.y - mScrollSpeed *dt/2;
	mpSpriteD->setPosition(DVec);

	if (CVec.y <= -tHeightB)
	{
		CVec.y = tHeightB;
	}

	if (DVec.y <= -tHeightB)
	{
		DVec.y = tHeightB;
	}
}
