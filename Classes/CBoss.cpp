#include "CBoss.h"
#include "CBossBullet.h"
#include "CBossLaser.h"
#include "Ending.h"
#include "SoundBox.h"


CBoss::CBoss()
{

}

CBoss::~CBoss()
{

}

void CBoss::Create(Node* parent)
{
	mpSprite = Sprite::create("Hello_Kitty_Sprite.png");
	mpSprite->setPosition(Vec2(650, 240));
	parent->addChild(mpSprite);
	mVec = mpSprite->getPosition();

	auto tAction_1 = RotateBy::create(1.0f, 10.0f);
	auto tAction_2 = tAction_1->reverse();

	auto tSeq = Sequence::create(tAction_1, tAction_2, NULL);

	auto tRep = RepeatForever::create(tSeq);

	mpSprite->runAction(tRep);

	for (int i = 0; i < 20; i++)
	{
		tBossBullet[i] = new CBossBullet();
		tBossBullet[i]->Create(this, parent);
	}
	tBossLaser = new CBossLaser();
	tBossLaser->Create();
	tBossLaser->SetScene(parent);
	tBossLaser->Build();
	tBossLaser->StopAni();
}

Vec2 CBoss::GetPosition()
{
	return mpSprite->getPosition();
}
void CBoss::SetPosition(Vec2 tVec)
{
	mpSprite->setPosition(tVec);
}

void CBoss::Move() // 업데이트
{
	if (mBossPhase != PHASE_DEAD)
	{
		Vec2 tVec;
		if (mMoveState == UP)
		{
			tVec = mVec;
			tVec.y = mVec.y + 2;
			if (tVec.y < 430)
			{
				mVec.y = mVec.y + 2;
				mpSprite->setPosition(mVec);
			}
			else
			{
				mMoveState = DOWN;
			}
		}
		else if (mMoveState == DOWN)
		{
			tVec = mVec;
			tVec.y = mVec.y - 2;
			if (tVec.y > 80)
			{
				mVec.y = mVec.y - 2;
				mpSprite->setPosition(mVec);
			}
			else
			{
				mMoveState = UP;
			}
		}
	}
}

Sprite* CBoss::GetSprite()
{
	return mpSprite;
}

void CBoss::FireSetPosition(CPlayer *tpPlayer)//스케쥴
{
	if (mBossPhase != PHASE_DEAD)
	{
		tBossBullet[mBulletIndex]->FireSetPosition(this, mBossPhase, tpPlayer);

		mBulletIndex = mBulletIndex + 1;

		if (mBulletIndex == 20)
		{
			mBulletIndex = 0;
		}
	}
}
void CBoss::FireMove()//업데이트
{
	for (int i = 0; i < 20; i++)
	{
		tBossBullet[i]->FireMove(this);
	}
}

void CBoss::PhaseCheck() //업데이트
{
	if (mHp < 50 && mHp >0)
	{
		mBossPhase = RAPID;
	}
	else if (mHp <= 0)
	{
		mBossPhase = PHASE_DEAD;
		if (mDeadCount == 0)
		{
			DeadAction();
		}
	}

	for (int i = 0; i < 20; i++)
	{
		tBossBullet[i]->CheckState();
	}
}

int CBoss::GetPhase()
{
	return mBossPhase;
}

void CBoss::LaserFire() //스케쥴
{
	if (mBossPhase == LASER)
	{
		tBossLaser->RunAni();
	}
}

void CBoss::CollisionWithPlayer(CPlayer* tpPlayer)
{
	for (int i = 0; i < 20; i++)
	{
		tBossBullet[i]->CollisionWithPlayer(tpPlayer);
	}
	
}

void CBoss::AttackedByPlayer(CProgress* tProgress)
{
	tProgress->BuildGuageWithDamage(1.0f);
	mHp = mHp - 1;
}

int CBoss::GetHp()
{
	return mHp;
}

void CBoss::PhaseOn()
{
	mBossPhase = AIMING;
}

void CBoss::DeadAction()
{
	mpSprite->stopAllActions();

	auto tMove = MoveTo::create(2.0f, Vec2(400, 240));
	auto tVib = MoveBy::create(0.1f, Vec2(-5, 0));
	auto tVibR = tVib->reverse();
	auto tVibSeq = Sequence::create(tVib, tVibR, NULL);
	auto tVibRep = Repeat::create(tVibSeq, 20);
	auto tFade = FadeOut::create(1.5f);

	auto tTotal = Sequence::create(tMove, tVibRep, tFade, DelayTime::create(5.0f),
		CallFunc::create(CC_CALLBACK_0(CBoss::SkipEnding, this)),NULL);

	mpSprite->runAction(tTotal);

	mDeadCount++;
}

void CBoss::SkipEnding()
{
	SoundBox::GetInstance()->Destroy();
	auto tpScene = Ending::createScene();
	Director::getInstance()->pushScene(tpScene);
}