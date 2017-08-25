#include "JoyStick.h"

USING_NS_CC;
using namespace cocos2d;



JoyStick::JoyStick()
{

}

JoyStick::~JoyStick()
{

}

void JoyStick::create(Layer *layer, Vec2 tVec)
{
	auto sprite = Sprite::create("joystick_control_circle.png");
	sprite->setPosition(tVec);
	sprite->setScale(1);
	sprite->setOpacity(100);
	StickPad = sprite;
	layer->addChild(sprite);

	sprite = Sprite::create("joystick_limit_circle.png");
	sprite->setPosition(tVec);
	sprite->setScale(1);
	sprite->setOpacity(150);
	layer->addChild(sprite);
	Stick = sprite;

	StartPoint = tVec;
	JoyStickIsTouched = false;
}

float JoyStick::getDLength()
{
	JoyStickPoint = Stick->getPosition();

	return DLength = sqrtf((StartPoint.x - JoyStickPoint.x)*(StartPoint.x - JoyStickPoint.x) +
		(StartPoint.y - JoyStickPoint.y) *(StartPoint.y - JoyStickPoint.y));


}

float JoyStick::getDPoint()
{
	JoyStickPoint = Stick->getPosition();
	
	if (JoyStickPoint.x <StartPoint.x )//- StickPad->getContentSize().width / 2)
	{
		Dir = -2;
	}
	else if (JoyStickPoint.x > StartPoint.x )//+ StickPad->getContentSize().width / 2)
	{
		Dir = 2;
	}

	else
	{
		Dir = 0;
	}
	

	return Dir;
	
}

void JoyStick::TouchesBegan(const vector<Touch*>&touches, Event *unused_event)
{
	vector<Touch *>::const_iterator it = touches.begin();
	Touch* touch;
	Vec2 tap;

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch *)(*it);
		if (touch) {
			tap = touch->getLocation();

			if (StickPad->getBoundingBox().containsPoint(tap) && JoyStickIsTouched == -1)
			{
				Stick->setPosition(touch->getLocation());
				JoyStickIsTouched = touch->getID();
			}
		}
		it++;
	}
}
void JoyStick::TouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	vector<Touch *>::const_iterator it = touches.begin();
	Touch* touch;
	Vec2 tap;
	Vec2 ntap;

	if (JoyStickIsTouched != -1) {
 
		
		touch = touches[JoyStickIsTouched];
			 {
				tap = touch->getLocation();
				CCLOG("%f , %f", tap.x, StartPoint.x + (StickPad->getContentSize().width / 2));

				if (tap.x>StartPoint.x + (StickPad->getContentSize().width / 2)) {
					ntap.x = StartPoint.x + (StickPad->getContentSize().width / 2);
				}
				else if (tap.x<StartPoint.x - (StickPad->getContentSize().width / 2)) {
					ntap.x = StartPoint.x - (StickPad->getContentSize().width / 2);
				}
				else {
					ntap.x = tap.x;
				}



				if (tap.y>StartPoint.y + (StickPad->getContentSize().height / 2)) {
					ntap.y = StartPoint.y + (StickPad->getContentSize().height / 2);
				}
				else if (tap.y<StartPoint.y - (StickPad->getContentSize().height / 2)) {
					ntap.y = StartPoint.y - (StickPad->getContentSize().height / 2);
				}
				else {
					ntap.y = tap.y;
				}


				Stick->setPosition(ntap);



			}
			
		}
	


}
void JoyStick::TouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	vector<Touch *>::const_iterator it = touches.begin();

	
	
	for (it; it < touches.end(); it++)
	{
		if ((*it)->getID() == JoyStickIsTouched)
		{
			JoyStickIsTouched = -1;
			Stick->setPosition(StartPoint);
		}
	}
}
void JoyStick::TouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	Stick->setPosition(StartPoint);
	JoyStickIsTouched = -1;
}


