#pragma once

#include "cocos2d.h"
#include "CPlayer.h"
#include "Map.h"
#include "CGameOver.h"
#include "CInterFace.h"


class JoyStick;

USING_NS_CC;
class AnimationBox;
class Stage2 : public cocos2d::Scene
{

protected:
	Layer *mpLayerForWorld = NULL;
	Layer *mpLayerForJoyPad = NULL;
	Size winSize;
	CMap *mMap = NULL;
	CPlayer *mpPlayer = NULL;
	/*EventListenerKeyboard *mpKeyListener = NULL;*/
	EventListenerTouchAllAtOnce *mpListener = NULL;
	JoyStick *joypad = NULL;
	CGameOver* mpGameOver = NULL;
	


	
	

	

public:
	
	virtual void update(float dt);
	
	virtual void onEnter();
	virtual void onExit();

	/*virtual void onKeyPressed(EventKeyboard::KeyCode keyCode,
		Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,
		Event *event);*/

	virtual void onTouchesBegan(const vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesMoved(const vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesEnded(const vector<Touch*>&touches, Event *unused_event);
	virtual void onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event);


	void StageInit();
	void ObjectReset(float dt);



public:



	static cocos2d::Scene* createScene();


	virtual bool init();


	CREATE_FUNC(Stage2);

	
};

