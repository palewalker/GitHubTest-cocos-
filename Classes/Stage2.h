#pragma once

#include "cocos2d.h"
#include "CPlayer.h"
#include "Map.h"
#include "CGameOver.h"
#include "CInterFace.h"
#include"CPacMan.h"
#include "CPathFinder.h"

class CRyuPathFinder;
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


	
	/*EventListenerKeyboard *mpKeyListener = NULL;  Test*/
	EventListenerTouchAllAtOnce *mpListener = NULL;
	JoyStick *joypad = NULL;
	CGameOver* mpGameOver = NULL;

	//A*
	CPacMan *mpPacMan = NULL;
	//CPathFinder *mpPathFinder = NULL;
	CRyuPathFinder *mpPathFinder = NULL;

	

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

	void PacManAstar(float dt);
	void PacManReset();
	

	void ReplaceNextStage();
	


public:



	static cocos2d::Scene* createScene();


	virtual bool init();


	CREATE_FUNC(Stage2);

	
};

