#ifndef JoyStick_h
#define JoyStick_h
#include "cocos2d.h"
#include <stdio.h>
#include<iostream>

#include <vector>

using namespace cocos2d;
using namespace std;

#define PADSIZE 0.5
class Stage1;

class JoyStick
{
private:
	


public:

	JoyStick();
	~JoyStick();

	void initPad();
	void create(Layer *layer, Vec2 tVec);

	Vec2 StartPoint;
	Vec2 JoyStickPoint;
	Sprite *Stick = NULL;
	Sprite *StickPad = NULL;
	float Dir = 0;
	int JoyStickIsTouched = -1;


	Vec2 DPoint;
	float DLength = 0.0f;

	float getDPoint();
	float getDLength();

	virtual void TouchesBegan(const vector<Touch*>&touches, Event *unused_event);
	virtual void TouchesMoved(const vector<Touch*>&touches, Event *unused_event);
	virtual void TouchesEnded(const vector<Touch*>&touches, Event *unused_event);
	virtual void TouchesCancelled(const vector<Touch*>&touches, Event *unused_event);



	

};

#endif /* JoyStick_h */