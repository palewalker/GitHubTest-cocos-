#pragma once

#include "cocos2d.h"
#include "config.h"
#include "CBoss.h"
#include "CSavePoint.h"


using namespace cocos2d;
using namespace std;

class CPlayer;

class CBossBullet
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node* mpNode = NULL;
	
	float mBulletDirX = 0;
	float mBulletDirY = 0;
	float mSpeed = 1;


	
	
	int mState = DEAD;


public:
	CBossBullet();
	virtual ~CBossBullet();

	void Create(CBoss* tBoss, Node *tpNode);
	
	void FireSetPosition(CBoss* tBoss,int type,CPlayer* tPlayer );
	void FireMove(CBoss* tBoss);
	void CheckState();
	void CollisionWithPlayer(CPlayer* tPlayer);
	




};

