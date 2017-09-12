
#include "CBossLaser.h"
#include "CPlayer.h"


CBossLaser::CBossLaser()
{

}

CBossLaser::~CBossLaser()
{

}

void CBossLaser::Create()
{
	mpLaser = new AnimationBox();
	mpLaserFire = new AnimationBox();
	

	mpLaser->Create(2,"KITTYLASER", 7, 0.1f);
	mpLaserFire->Create(2,"KITTYLASERFIRE", 6, 0.1f);

	Hide();
	
	
}

void CBossLaser::SetScene(Node *tpNode)
{
	
	mpLaser->SetScene(tpNode);
	mpLaserFire->SetScene(tpNode);
	
}
void CBossLaser::Hide()
{
	mpLaser->Hide();
	mpLaserFire->Hide();
	
}

void CBossLaser::Show()
{
	mpLaser->Show();
	mpLaserFire->Show();
	
}

void CBossLaser::SetPosition(Vec2 tVec)
{
	mVec = tVec;


	mpLaser->SetPosition(tVec);
	mpLaserFire->SetPosition(tVec);

	
}

Vec2 CBossLaser::GetPosition()
{
	//return PacMan_UP->GetPosition();
	return mVec;
}

void CBossLaser::Build()
{
	mpLaser->Build();
	mpLaserFire->Build();
	
}
void CBossLaser::UnBuild()
{
	mpLaser->UnBuild();
	mpLaserFire->UnBuild();
	
}

void CBossLaser::Destroy()
{
	mpLaser->Destroy();
	mpLaserFire->Destroy();
	
}
void CBossLaser::RunAni()
{
	srand(time(NULL));
	int trandom = rand() % 2;
	switch (trandom)
	{
	case 0:
	{
		mpLaser->SetPosition(Vec2(400,330));
		mpLaserFire->SetPosition(Vec2(400, 330));
	}break;
	case 1:
	{
		mpLaser->SetPosition(Vec2(400, 150));
		mpLaserFire->SetPosition(Vec2(400, 150));
	}break;
	}
	
	Show();
	auto tSeq = Sequence::create(CallFunc::create(CC_CALLBACK_0(CBossLaser::RunDef, this)),
		DelayTime::create(1.0f),
		CallFunc::create(CC_CALLBACK_0(CBossLaser::RunFire, this)), NULL);
	
	mpLaser->RunAction(tSeq);
	
}
void CBossLaser::StopAni()
{
	mpLaser->StopAni();
	mpLaserFire->StopAni();

}

void CBossLaser::RunDef()
{
	mpLaser->RunAni();
}
void CBossLaser::RunFire()
{
	mpLaserFire->RunAni();
}

void CBossLaser::CollisionWithPlayer(CPlayer *tPlayer)
{
	Vec2 LaserVec = mpLaserFire->GetPosition();
	Vec2 PlayerVec = tPlayer->GetPosition();

	float tLaserWidth = mpLaserFire->GetSprite()->getContentSize().width*0.5f;
	float tLaserHeight = mpLaserFire->GetSprite()->getContentSize().height * 0.5f;

	float tPlayerWidth = tPlayer->GetSprite()->getContentSize().width *0.5f;
	float tPlayerHeight = tPlayer->GetSprite()->getContentSize().height *0.5f;

	if (LaserVec.x + tLaserWidth >= PlayerVec.x - tPlayerWidth &&
		LaserVec.x - tLaserWidth <= PlayerVec.x + tPlayerWidth)
	{
		if (LaserVec.y + tLaserHeight >= PlayerVec.y - tPlayerHeight &&
			LaserVec.y - tLaserHeight <= PlayerVec.y + tPlayerHeight)
		{
			tPlayer->DoDead();
		}
	}
}
