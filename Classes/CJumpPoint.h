#pragma once
#include "cocos2d.h"
#include "CObject.h"
#include "config.h"

using namespace cocos2d;
using namespace std;



class CJumpPoint : public CObject
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;
	int mState = ALIVE;
	
	



public:
	CJumpPoint();
	virtual ~CJumpPoint();

	virtual void Create(CMap *tpMap, Layer *tpLayer, int ObjectNum);
	virtual void SetScene(Node *tpNode);
	virtual void Hide();
	virtual void Show();
	virtual void SetPosition(Vec2 tVec);
	virtual Vec2 GetPosition();
	Sprite* GetSprite();
	void Reset();
	int GetState();
	void SetUsed();


	

	


};

