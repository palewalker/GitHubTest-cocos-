#pragma once
#include "cocos2d.h"
#include "CUnit.h"

#include "Map.h"
#include "config.h"

#include "AnimationBox.h"



using namespace cocos2d;
using namespace std;
class CPlayer;


class CPacMan 
{
protected:
	Vec2 mVec;
	Vec2 OriginVec;

	Sprite *mpSprite = NULL;
	Node *tpNode = NULL;
	
	AnimationBox *PacMan_UP = NULL;
	AnimationBox *PacMan_DOWN = NULL;
	AnimationBox *PacMan_LEFT = NULL;
	AnimationBox *PacMan_RIGHT = NULL;
	int mState = LEFT;

	float mSpeed = 64.0f;

	int mRow = 0;
	int mCol = 0;

	

	
public:
	bool mIsMove = false;
	int mCurTargetIndex = 0;
	vector<Vec2> m_RoadVec;


public:
	CPacMan();
	virtual ~CPacMan();

	

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
	void SetOrigin(Vec2 tVec);

	//A*
	void BeginMove();
	void UpdateMove(float dt);
	
	void StopMove();

	int GetCol();
	int GetRow();

	void CollisionWithPlayer(CPlayer *tpPlayer);
	void ResetPos();

	
	
	
	

	
	

	


};

