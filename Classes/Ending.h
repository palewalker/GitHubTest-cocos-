#pragma once

#include "cocos2d.h"


USING_NS_CC;

class Ending : public cocos2d::Scene
{

protected:
	MenuItemLabel* Credit = NULL;
	Sprite* BG = NULL;
	Sprite* Hero = NULL;
	Sprite* Com = NULL;
	

public:
	
	
	void CreditDown();
	void StartScene();


public:



	static cocos2d::Scene* createScene();


	virtual bool init();


	CREATE_FUNC(Ending);

	
};

