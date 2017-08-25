#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Stage1.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
protected:

	
public:
	
	void doReplaceScene(Ref *pSender);
	

public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
