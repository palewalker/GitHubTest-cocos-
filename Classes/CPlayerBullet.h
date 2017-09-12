#pragma once

#include "cocos2d.h"
#include "config.h"
#include "CPlayer.h"
#include "CSavePoint.h"



using namespace cocos2d;
using namespace std;
class CBoss;
class CProgress;
class CPlayerBullet
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node* mpNode = NULL;
	
	int BulletDir = 1;

	
	
	int mState = DEAD;


public:
	CPlayerBullet();
	virtual ~CPlayerBullet();

	void Create(CPlayer* tPlayer);
	void SetScene(Node *tpNode);
	void FireSetPosition(CPlayer* tPlayer);
	void FireMove();
	void DirSet(int Dir);
	bool CollisionWithSavePoint(CSavePoint *tSavePtr);
	void CollisionWithBoss(CBoss *tBoss, CProgress *tProgress);




};

