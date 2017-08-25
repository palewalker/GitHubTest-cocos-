#pragma once
#include "cocos2d.h"
#include "CObject.h"


using namespace cocos2d;
using namespace std;

class CMap;

class CSavePoint : public CObject
{
protected:
	Vec2 mVec;
	Sprite *mpSprite = NULL;
	Node *mpNode = NULL;
	
	



public:
	CSavePoint();
	virtual ~CSavePoint();

	virtual void Create(CMap *tpMap, Layer *tpLayer, int ObjectNum);
	virtual void SetScene(Node *tpNode);
	virtual void Hide();
	virtual void Show();
	virtual void SetPosition(Vec2 tVec);
	virtual Vec2 GetPosition();
	Sprite* GetSprite();


	

	


};

