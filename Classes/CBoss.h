#pragma once
#include "cocos2d.h"
#include "CInterFace.h"
#include "config.h"
#include "CProgress.h"




using namespace cocos2d;
using namespace std;

class CBossBullet;
class CBossLaser;
class CPlayer;

class CBoss
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;
	int mMoveState = UP;
	int mHp = 1;
	int mBossPhase = PHASE_DEF;
	int mBulletIndex = 0;
	int mDeadCount = 0;
	
	CBossBullet *tBossBullet[20];
	CBossLaser *tBossLaser;

	




public:
	CBoss();
	~CBoss();

	void Create(Node* parent);
	Vec2 GetPosition();
	void SetPosition(Vec2 tVec);
	void Move();
	Sprite* GetSprite();
	void PhaseCheck();
	int GetPhase();
	void FireSetPosition(CPlayer *tpPlayer);
	void FireMove();
	void LaserFire();
	void CollisionWithPlayer(CPlayer* tpPlayer);
	void AttackedByPlayer(CProgress* tProgress);
	int GetHp();
	void PhaseOn();
	void DeadAction();
	void SkipEnding();
	







};

