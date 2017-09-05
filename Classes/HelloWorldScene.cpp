#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
 
#include "SoundBox.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto NextScene = MenuItemFont::create
	("GameScene", CC_CALLBACK_1(HelloWorld::doReplaceScene, this));
	NextScene->setPosition(Vec2(400, 240));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NextScene, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/*
	auto mBackLayer = LayerColor::create(Color4B(0, 0, 255, 255), visibleSize.width, visibleSize.height);
	mBackLayer->setAnchorPoint(Vec2(0, 0));
	this->addChild(mBackLayer, 0);
	*/

	return true;

}

void HelloWorld::doReplaceScene(Ref *pSender)
{
	//bug_stageskip
	auto pScene = Stage1::create();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{

	
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
