#pragma once
#include "cocos2d.h"
#include "CUnit.h"
#include "JoyStick.h"
#include "Map.h"
#include "config.h"
#include "CJumpPoint.h"
#include "CPlatform.h"
#include "CInterFace.h"




using namespace cocos2d;
using namespace std;

class CBoss;
class CProgress;

typedef vector<int> CIntVec;

class CPlayerBullet;

class CPlayer : public CUnit
{
protected:
	Vec2 mVec;
	Vec2 mVecSave;
	Sprite *mpSprite = NULL;
	Node *tpNode = NULL;
	Vec2 SaveVec = Vec2(70, 80);
	Label* mpTestLabel = NULL;
	

	CPlayerBullet *tPlayerBullet[30];
	
	int BulletIndex = 0;

	float mDirX = 0;
	float mDirY = 0;
	float mSpeedPower = 1.0f;//5;
	bool mKeyPressed = false;
	bool mIsCollision = false;
	int mState = ALIVE;
	int mJumpCount = 0;
	int mJumpCountSave = 0;
	float mJumpPower = 0;
	float mJumpPowerSave = 0;
	int mJumpState;
	int mJumpStateSave;
	int mBulletIndex = 0;
	int mDirState = RIGHT;
	bool IsSave = false;

	


	
	
	


	CIntVec mKeyInputCheckVec;




public:
	CPlayer();
	virtual ~CPlayer();

	


	virtual void Create(CMap *tpMap);
	virtual void SetScene(Node *tpNode);
	virtual void Hide();
	virtual void Show();
	virtual void SetPosition(Vec2 tVec);
	virtual Vec2 GetPosition();
	void Move(CMap *tpMap,float Dir);
	
	void JumpStart();
	void Jump(CMap *tpMap);
	void Collision(CMap *tpMap);
	/*void MoveByKeyboard(CMap *tpMap);*/

	void KeyPressed(EventKeyboard::KeyCode keyCode,
		Event *event);
	void KeyReleased(EventKeyboard::KeyCode keyCode,
		Event *event);

	void ObjectCollision(CMap *tpMap);
	void StateCheck();
	void FireMove();
	void SavePos();
	void LoadPos();
	int GetState();
	void FireStart(float Dir);
	Sprite* GetSprite();
	void SaveInit();
	void DoDead();
	void ColiisionWithBoss(CBoss *tpBoss, CProgress *tpProgress);


	


};

