#pragma once
#include "cocos2d.h"
#include "CObject.h"

using namespace cocos2d;
using namespace std;



class CPlatform : public CObject
{
protected:
	Vec2 mVec;
	Vec2 mOriginVec;
	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;
	int mState = 0;
	
	



public:
	CPlatform();
	virtual ~CPlatform();

	virtual void Create(CMap *tpMap, Layer *tpLayer, int ObjectNum);
	virtual void SetScene(Node *tpNode);
	virtual void Hide();
	virtual void Show();
	virtual void SetPosition(Vec2 tVec);
	virtual Vec2 GetPosition();
	Sprite* GetSprite();
	void FallAndReset(Node *tpNode);
	void SetOriginPos();


	

	


};

