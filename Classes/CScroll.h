#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;



class CScroll
{
protected:

	Sprite *mpSpriteA = NULL;
	Vec2 AVec;

	Sprite *mpSpriteB = NULL;
	Vec2 BVec;

	Sprite *mpSpriteC = NULL;
	Vec2 CVec;

	Sprite *mpSpriteD = NULL;
	Vec2 DVec;

	Layer *mpLayer = NULL;

	float mScrollSpeed = 0.0f;

	float mZOrder = 0.0f;

	float tHeight = 0.0f;
	float tHeightB = 0.0f;



public:
	CScroll();
   ~CScroll();

   void Create(float tScrollSpeed, float tZOrder);
   void Destroy();

   void SetScene(Layer *parent);

   void Build();
   void UnBuild();

   void UpdateScroll(float dt);

	


	

	


};

