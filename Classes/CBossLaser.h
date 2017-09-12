#pragma once
#include "cocos2d.h"


#include "Map.h"
#include "config.h"

#include "AnimationBox.h"



using namespace cocos2d;
using namespace std;

class CPlayer;

class CBossLaser 
{
protected:
	Vec2 mVec;

	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;

	AnimationBox *mpLaser = NULL;
	AnimationBox *mpLaserFire = NULL;

	
	

	
public:
	

public:
	CBossLaser();
	virtual ~CBossLaser();

	

	void Create();
	void SetScene(Node *tpNode);
	void Hide();
	void Show();
	void SetPosition(Vec2 tVec);
	Vec2 GetPosition();
	void Build();
	void UnBuild();
	void Destroy();
	void RunAni();
	void StopAni();
	void RunDef();
	void RunFire();
	void CollisionWithPlayer(CPlayer *tPlayer);

	//A*
	
	
	
	
	

	
	

	


};

