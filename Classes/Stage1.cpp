#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage1.h"
#include "SoundBox.h"



USING_NS_CC;


Scene* Stage1::createScene()
{
	return Stage1::create();
}

// on "init" you need to initialize your instance
bool Stage1::init()
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
	this->addChild(mpLayerForWorld);

	mpLayerForJoyPad = Layer::create();
	this->addChild(mpLayerForJoyPad, 100);

	

	StageInit();//�������� ������ �ʿ��� ��ü�� ������ ����ִ� �Լ�

	winSize = Director::getInstance()->getWinSize();
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(Stage1::ObjectReset), 2.0f);


	
	return true;
}

void Stage1::update(float dt)
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

	
}

void Stage1::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerTouchAllAtOnce::create();

	

	mpListener->onTouchesBegan = CC_CALLBACK_2(Stage1::onTouchesBegan, this);
	mpListener->onTouchesMoved = CC_CALLBACK_2(Stage1::onTouchesMoved, this);
	mpListener->onTouchesEnded = CC_CALLBACK_2(Stage1::onTouchesEnded, this);
	mpListener->onTouchesCancelled = CC_CALLBACK_2(Stage1::onTouchesCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	//mpKeyListener = EventListenerKeyboard::create();
	//mpKeyListener->onKeyPressed = CC_CALLBACK_2(Stage1::onKeyPressed, this);
	//mpKeyListener->onKeyReleased = CC_CALLBACK_2(Stage1::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mpKeyListener, this);
}

void Stage1::onExit()
{
	Scene::onExit();
}

void Stage1::StageInit()
{
	mMap = new CMap();
	mMap->Create(mpLayerForWorld, 1);

	mpPlayer = new CPlayer();
	mpPlayer->SetScene(this);
	mpPlayer->Create(mMap);
	mpPlayer->SaveInit();

	joypad = new JoyStick();
	joypad->create(mpLayerForJoyPad, Vec2(80, 240));
	
	mpGameOver = new CGameOver();
	mpGameOver->Create(this);

	CInterFace::GetInstance()->SetScene(this);
	CInterFace::GetInstance()->SetInterFace();
	
	SoundBox::GetInstance()->Create();
	SoundBox::GetInstance()->PlayBGM(1, true);




	//���� ������ �ʿ��� ��ü ����


}

//void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyPressed(keyCode, event);
//}
//void Stage1::onKeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyReleased(keyCode, event);
//}

void Stage1::ObjectReset(float dt)
{
	for (int i = 0; i < mMap->GetJumpPointNum(); i++)
	{
		mMap->GetJumpPtr(i)->Reset();
	}

	//more jump �����
}

void Stage1::onTouchesBegan(const vector<Touch*>&touches, Event *unused_event)
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

					mpGameOver->Hide(1);
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
void Stage1::onTouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesMoved(touches, unused_event);
}
void Stage1::onTouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesEnded(touches, unused_event);
	
}
void Stage1::onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesCancelled(touches, unused_event);
}


void Stage1::ReplaceNextStage()
{
	if (true == mMap->NextStage(mpPlayer->GetPosition()))
	{
		SoundBox::GetInstance()->Destroy();
		//bug_stageskip
		auto tpScene = Stage2::createScene();
		Director::getInstance()->pushScene(tpScene);
	}
}
