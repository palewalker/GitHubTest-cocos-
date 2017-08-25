#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;



class CUnit
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;
	
	



public:
	CUnit();
	virtual ~CUnit();

	virtual void Create();
	virtual void SetScene(Node *tpNode);
	virtual void Hide();
	virtual void Show();
	virtual void SetPosition(Vec2 tVec);
	virtual Vec2 GetPosition();


	

	


};

