
#include "CPlayerBullet.h"




CPlayerBullet::CPlayerBullet()
{

}

CPlayerBullet::~CPlayerBullet()
{

}


void CPlayerBullet::Create(CPlayer* tPlayer)
{
	mpSprite = Sprite::create("Bullet.png");
	mpSprite->setPosition(tPlayer->GetPosition());
	mpSprite->setVisible(false);
	
	mpNode->addChild(mpSprite);
}

void CPlayerBullet::SetScene(Node *tpNode)
{
	mpNode = tpNode;
}

void CPlayerBullet::FireSetPosition(CPlayer* tPlayer)
{
	mpSprite->setPosition(tPlayer->GetPosition()+Vec2(0,(tPlayer->GetSprite()->getContentSize().height / 2)));
	mState = ALIVE;
}

void CPlayerBullet::FireMove()
{
	
	Vec2 tVec = mpSprite->getPosition();

	if(mState == ALIVE)
	{
		mpSprite->setVisible(true);
		tVec.x = tVec.x + 10 * BulletDir;
		mpSprite->setPositionX(tVec.x);
		if (BulletDir == 0)
		{
			mState = DEAD;
		}

		if (tVec.x < 1 || tVec.x >799)
		{
			mState = DEAD;
		
		}

		
	}

	if (mState == DEAD)
	{
		mpSprite->setVisible(false);
	}
}

void CPlayerBullet::DirSet(int Dir)
{
	BulletDir = Dir;
}

bool CPlayerBullet::CollisionWithSavePoint(CSavePoint *tSavePtr)
{
	if (mState == ALIVE)
	{
		Sprite* tpBulletSpr = mpSprite;
		Vec2 tVec = mpSprite->getPosition();
		float tBulletR = mpSprite->getContentSize().width * 0.5f;

		Rect tSavePoint = tSavePtr->GetSprite()->getBoundingBox();
		bool tf = tSavePoint.intersectsCircle(tVec, tBulletR);
		
		if (tf == true)
		{
			mState = DEAD;
		}

		return tf;
	}
	
}