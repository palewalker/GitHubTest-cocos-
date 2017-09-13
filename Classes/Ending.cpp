#include "Ending.h"
#include "SimpleAudioEngine.h"

#include "SoundBox.h"
#include "HelloWorldScene.h"




USING_NS_CC;


Scene* Ending::createScene()
{
	return Ending::create();
}

// on "init" you need to initialize your instance
bool Ending::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	SoundBox::GetInstance()->Create();
	SoundBox::GetInstance()->PlayBGM(6);

	
	
	
	BG = Sprite::create("Ending.png");
	BG->setPosition(Vec2(400, 240));
	this->addChild(BG);

	Label *CreditLbl = Label::createWithTTF("Thanks for Playing!", "fonts/retro.ttf", 40);


	Credit = MenuItemLabel::create(CreditLbl, CC_CALLBACK_0(Ending::StartScene, this));
	Credit->setPosition(Vec2(400, 550));
	Credit->setColor(Color3B(255, 255, 255));
	

	auto menu = Menu::create(Credit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Hero = Sprite::create("Guy.png");
	Hero->setPosition(Vec2(100, 170));
	this->addChild(Hero);

	Com = Sprite::create("computer2.png");
	Com->setPosition(Vec2(730, 160));
	this->addChild(Com);

	auto tMove = MoveTo::create(10.0f, Vec2(670, 170));
	auto tJump = JumpBy::create(3.0f, Vec2(0, 0), 30, 5);
	auto tSeq = Sequence::create(tMove, tJump, 
		CallFunc::create(CC_CALLBACK_0(Ending::CreditDown, this)),NULL);

	Hero->runAction(tSeq);
	


	
	return true;
}


void Ending::CreditDown()
{
	auto tMove = MoveTo::create(3.0f, Vec2(400, 240));

	Credit->runAction(tMove);
}

void Ending::StartScene()
{
	SoundBox::GetInstance()->Destroy();
	auto pScene = HelloWorld::create();
	Director::getInstance()->replaceScene(pScene);
}