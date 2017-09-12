
#include "CBossBullet.h"
#include "CPlayer.h"
#include "Stage5.h"




CBossBullet::CBossBullet()
{

}

CBossBullet::~CBossBullet()
{

}


void CBossBullet::Create(CBoss* tBoss, Node *tpNode)
{
	mpSprite = Sprite::create("kittyBullet.png");
	mpSprite->setPosition(tBoss->GetPosition());
	mVec = mpSprite->getPosition();
	mpSprite->setVisible(false);
	
	tpNode->addChild(mpSprite);

	RotateBy* tMove = RotateBy::create(1.0f, 360.0f);
	RepeatForever* tRep = RepeatForever::create(tMove);

	mpSprite->runAction(tRep);
}



void CBossBullet::FireSetPosition(CBoss* tBoss, int type, CPlayer* tPlayer)
{
	if (type == AIMING)
	{
		mpSprite->setPosition(tBoss->GetPosition() - Vec2(tBoss->GetSprite()->getContentSize().width/2, 0));
		float tDistance;
		Vec2 tPlayerVec = tPlayer->GetPosition();
		Vec2 tBulletVec = mpSprite->getPosition();
		tDistance = sqrt((tBulletVec.x - tPlayerVec.x)*(tBulletVec.x - tPlayerVec.x)
			+ (tBulletVec.y - tPlayerVec.y)*(tBulletVec.y - tPlayerVec.y));
		mBulletDirX = -((tBulletVec.x - tPlayerVec.x) / tDistance);
		mBulletDirY = -((tBulletVec.y - tPlayerVec.y) / tDistance);
		mState = ALIVE;
	}
	else if(type == RAPID)
	{
		mpSprite->setPosition(tBoss->GetPosition() - Vec2(tBoss->GetSprite()->getContentSize().width / 2, 0));
		Vec2 tBulletVec = mpSprite->getPosition();

		static float tPowerAngle = 18.0f;
		float tRadius = 8.0f;

		static float tTheta = 120;
		if (tTheta> 240)
		{
			tPowerAngle = -18.0f;
		}
		else if (tTheta < 120)
		{
			tPowerAngle = 18.0f;
		}

		mBulletDirX = tRadius * cos((3.14f / 180.0f) * tTheta);
		mBulletDirY = tRadius * sin((3.14f / 180.0f) * tTheta);

		tTheta = tTheta + tPowerAngle;
		mState = ALIVE;
		
	}
}

void CBossBullet::FireMove(CBoss* tBoss)
{
	if (mState == ALIVE)
	{
		Vec2 tVec = mpSprite->getPosition();
		float tSpeed = mSpeed;
		if (tBoss->GetPhase() == AIMING)
		{
			tVec.x = tVec.x + mBulletDirX *tSpeed*10;
			tVec.y = tVec.y + mBulletDirY*tSpeed*10;
		}

		else if (tBoss->GetPhase() == RAPID)
		{
			tVec.x = tVec.x + mBulletDirX *tSpeed/2 ;
			tVec.y = tVec.y + mBulletDirY*tSpeed/2 ;
		}


		if ((mpSprite->getPosition().x > 5 && mpSprite->getPosition().x < 835) &&
			(mpSprite->getPosition().y > 5 && mpSprite->getPosition().y < 470))
		{
			mpSprite->setPosition(tVec);

		
		}
		else
		{
			mState = DEAD;
			mpSprite->setVisible(false);
			mpSprite->setPosition(mVec);
		}
	}

	
}

void CBossBullet::CheckState() //업데이트, in 보스 phasecheck 
{
	if(mState == DEAD)
	{
		mpSprite->setVisible(false);
	 }
	else if (mState == ALIVE)
	{
		mpSprite->setVisible(true);
	}
}

void CBossBullet::CollisionWithPlayer(CPlayer* tPlayer) //업데이트
{
	if (mState == ALIVE)
	{
		Vec2 PlayerVec = tPlayer->GetPosition();
		Vec2 BulletVec = mpSprite->getPosition();

		float tRadiusBullet = mpSprite->getContentSize().width*0.5f;

		Rect tPlayerRect = tPlayer->GetSprite()->getBoundingBox();

		if (true == tPlayerRect.intersectsCircle(BulletVec, tRadiusBullet))
		{
			tPlayer->DoDead();
			mState = DEAD;
			CInterFace::GetInstance()->DeadCountUP();
			auto tpScene = Stage5::createScene();
			Director::getInstance()->pushScene(tpScene);
		}
		
		
	}
}
