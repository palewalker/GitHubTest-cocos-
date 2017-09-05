#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage3.h"



USING_NS_CC;


Scene* Stage3::createScene()
{
	return Stage3::create();
}

// on "init" you need to initialize your instance
bool Stage3::init()
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


	// create menu, it's an autorelease object

	//���ӿ� �ʿ��� ���̾� ����(���� ����, �����е�, �������̽�)
	mpLayerForWorld = Layer::create();
	this->addChild(mpLayerForWorld, 99);

	mpBlock = Sprite::create("Block.png");
	mpBlock->setPosition(Vec2(400, 240));
	this->addChild(mpBlock, 100);
	

	mpLayerForJoyPad = Layer::create();
	this->addChild(mpLayerForJoyPad, 101);

	

	StageInit();//�������� ������ �ʿ��� ��ü�� ������ ����ִ� �Լ�

	winSize = Director::getInstance()->getWinSize();
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(Stage3::ObjectReset), 2.0f);


	
	return true;
}

void Stage3::update(float dt)
{
	//�÷��̾� ���� �Լ�
	mpPlayer->Jump(mMap);
	/*mpPlayer->MoveByKeyboard(mMap);*/
	mpPlayer->Move(mMap, joypad->getDPoint());
	mpPlayer->Collision(mMap);
	mpPlayer->ObjectCollision(mMap);
	mpPlayer->StateCheck();
	mpPlayer->FireMove();
	//�÷��̾� ����� ���ӿ��� ���̾� ǥ��
	
	//�÷��̾��� ���¸� üũ�Ͽ� DEAD�̸� ���ӿ��� ǥ��
	if (DEAD == mpPlayer->GetState() && false == mpGameOver->IsShow() )
	{
		mpGameOver->Show();
	}

	//mpGameOver->SetVisible(mpPlayer->GetState());

	//�������̽� deadcount ������Ʈ

	CInterFace::GetInstance()->Update(dt);

	//bug_stageskip
	ReplaceNextStage();
	//�÷��̾��� ��ġ üũ�ؼ� true�Ͻ� ���� ������ �� ��ȯ
	UpdateRender();

	
}

void Stage3::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerTouchAllAtOnce::create();

	

	mpListener->onTouchesBegan = CC_CALLBACK_2(Stage3::onTouchesBegan, this);
	mpListener->onTouchesMoved = CC_CALLBACK_2(Stage3::onTouchesMoved, this);
	mpListener->onTouchesEnded = CC_CALLBACK_2(Stage3::onTouchesEnded, this);
	mpListener->onTouchesCancelled = CC_CALLBACK_2(Stage3::onTouchesCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	//mpKeyListener = EventListenerKeyboard::create();
	//mpKeyListener->onKeyPressed = CC_CALLBACK_2(Stage3::onKeyPressed, this);
	//mpKeyListener->onKeyReleased = CC_CALLBACK_2(Stage3::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mpKeyListener, this);
}

void Stage3::onExit()
{
	Scene::onExit();
}

void Stage3::StageInit()
{
	mMap = new CMap();
	mMap->Create(mpLayerForWorld, 3);

	mpPlayer = new CPlayer();
	mpPlayer->SetScene(mpLayerForWorld);
	mpPlayer->Create(mMap);
	mpPlayer->SaveInit();

	joypad = new JoyStick();
	joypad->create(mpLayerForJoyPad, Vec2(80, 240));
	
	mpGameOver = new CGameOver();
	mpGameOver->Create(this);

	CInterFace::GetInstance()->SetScene(this);
	CInterFace::GetInstance()->SetInterFace();


	//���� �ؽ��ĸ� ���� ȭ�� ȸ�� ȿ�� ����
	Size tWinSize = Director::getInstance()->getWinSize();
	mpRender = RenderTexture::create(800, 480, Texture2D::PixelFormat::RGBA8888);
	mpRender->retain();
	mpRender->setPosition(Vec2(400, 240));
	mpRender->setScaleX(0.7f);

	auto RotateRender = RotateBy::create(15.0f, 360.0f);
	auto RepeatRender = RepeatForever::create(RotateRender);
	mpRender->runAction(RepeatRender);
	

	this->addChild(mpRender,100);








	//���� ������ �ʿ��� ��ü ����


}

//void Stage3::onKeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyPressed(keyCode, event);
//}
//void Stage3::onKeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyReleased(keyCode, event);
//}

void Stage3::ObjectReset(float dt)
{
	for (int i = 0; i < mMap->GetJumpPointNum(); i++)
	{
		mMap->GetJumpPtr(i)->Reset();
	}

	//more jump �����
}

void Stage3::onTouchesBegan(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesBegan(touches, unused_event);

	vector<Touch *>::const_iterator it = touches.begin();
	Touch* touch;
	Vec2 tap;

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		if (touch)
		{
			tap = touch->getLocation();

			if (mpGameOver->GetSprite()->getBoundingBox().containsPoint(tap))
			{
				if (true == mpGameOver->IsShow())
				{
					mpPlayer->LoadPos();

					mpGameOver->Hide();
				}
			}

			if (CInterFace::GetInstance()->GetJumpBtn()->getBoundingBox().containsPoint(tap))
			{
				mpPlayer->JumpStart();
			}

			if (CInterFace::GetInstance()->GetFireBtn()->getBoundingBox().containsPoint(tap))
			{
				mpPlayer->FireStart(joypad->getDPoint());
			}
			
		} 
		
		
		it++;
	}


}
void Stage3::onTouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesMoved(touches, unused_event);
}
void Stage3::onTouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesEnded(touches, unused_event);
	
}
void Stage3::onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesCancelled(touches, unused_event);
}


void Stage3::ReplaceNextStage()
{
	if (true == mMap->NextStage(mpPlayer->GetPosition()))
	{
		//bug_stageskip
		auto tpScene = Stage4::createScene();
		Director::getInstance()->pushScene(tpScene);
	}
}

void Stage3::UpdateRender()
{
	mpRender->begin();
	mpLayerForWorld->visit();
	mpRender->end();

	//���� �ؽ��ĸ� ������Ʈ �Լ��� �־ �Ű� ����ȭ

}
