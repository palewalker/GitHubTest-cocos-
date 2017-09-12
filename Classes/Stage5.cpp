#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage5.h"
#include "CBoss.h"
#include "CScroll.h"
#include "CProgress.h"
#include "SoundBox.h"


USING_NS_CC;


Scene* Stage5::createScene()
{
	return Stage5::create();
}

// on "init" you need to initialize your instance
bool Stage5::init()
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

	//게임에 필요한 레이어 생성(게임 월드, 조이패드, 인터페이스)
	mpLayerForWorld = Layer::create();
	this->addChild(mpLayerForWorld);

	mpLayerForJoyPad = Layer::create();
	this->addChild(mpLayerForJoyPad, 100);

	

	StageInit();//스테이지 구성에 필요한 객체의 생성이 들어있는 함수

	winSize = Director::getInstance()->getWinSize();
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(Stage5::ObjectReset), 2.0f);
	this->scheduleOnce(schedule_selector(Stage5::PhaseOn), 3.0f);
	this->schedule(schedule_selector(Stage5::LaserFire), 2.0f);
	

	

	
	return true;
}

void Stage5::update(float dt)
{
	//플레이어 관련 함수
	mpPlayer->Jump(mMap);
	/*mpPlayer->MoveByKeyboard(mMap);*/
	mpPlayer->Move(mMap, joypad->getDPoint());
	mpPlayer->Collision(mMap);
	mpPlayer->ObjectCollision(mMap);
	mpPlayer->StateCheck();
	mpPlayer->FireMove();
	//플레이어 사망시 게임오버 레이어 표시
	
	//플레이어의 상태를 체크하여 DEAD이면 게임오버 표시
	if (DEAD == mpPlayer->GetState() && false == mpGameOver->IsShow() )
	{
		mpGameOver->Show();
	}

	//mpGameOver->SetVisible(mpPlayer->GetState());

	//인터페이스 deadcount 업데이트

	CInterFace::GetInstance()->Update(dt);

	//bug_stageskip
	ReplaceNextStage();
	//플레이어의 위치 체크해서 true일시 다음 맵으로 신 전환

	mpBoss->Move();
	mpBoss->PhaseCheck();
	mpBoss->FireMove();

	if (mpBoss->GetPhase() == AIMING)
	{
		tCount = tCount + 1;
		if (tCount > 80)
		{
			FireSet(dt);
			tCount = 0;
		}
	}
	else if (mpBoss->GetPhase() == RAPID)
	{
		tCount = tCount + 1;
		if (tCount > 10)
		{
			FireSet(dt);
			tCount = 0;
		}
	}
	mpBoss->CollisionWithPlayer(mpPlayer);
	mpPlayer->ColiisionWithBoss(mpBoss, mpProgress);

	mpScroll->UpdateScroll(dt);
	mpProgress->SetPosition(mpBoss->GetPosition() - Vec2(60, mpBoss->GetSprite()->getContentSize().height/2+20));

	
}

void Stage5::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerTouchAllAtOnce::create();

	

	mpListener->onTouchesBegan = CC_CALLBACK_2(Stage5::onTouchesBegan, this);
	mpListener->onTouchesMoved = CC_CALLBACK_2(Stage5::onTouchesMoved, this);
	mpListener->onTouchesEnded = CC_CALLBACK_2(Stage5::onTouchesEnded, this);
	mpListener->onTouchesCancelled = CC_CALLBACK_2(Stage5::onTouchesCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	//mpKeyListener = EventListenerKeyboard::create();
	//mpKeyListener->onKeyPressed = CC_CALLBACK_2(Stage5::onKeyPressed, this);
	//mpKeyListener->onKeyReleased = CC_CALLBACK_2(Stage5::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mpKeyListener, this);
}

void Stage5::onExit()
{
	Scene::onExit();
}

void Stage5::StageInit()
{
	mMap = new CMap();
	mMap->Create(mpLayerForWorld, 5);

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

	mpBoss = new CBoss();
	mpBoss->Create(this);

	mpScroll = NULL;
	mpScroll = new CScroll();

	mpScroll->Create(100.0f, 1);
	mpScroll->SetScene(mpLayerForWorld);
	mpScroll->Build();

	mpProgress = new CProgress();
	mpProgress->Create(100, 100);
	mpProgress->SetScene(this);
	mpProgress->SetPosition(Vec2(400, 50));
	mpProgress->AddToScene();
	
	SoundBox::GetInstance()->Create();
	SoundBox::GetInstance()->PlayBGM(5, true);


	//게임 구성에 필요한 객체 생성


}

//void Stage5::onKeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyPressed(keyCode, event);
//}
//void Stage5::onKeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyReleased(keyCode, event);
//}

void Stage5::ObjectReset(float dt)
{
	for (int i = 0; i < mMap->GetJumpPointNum(); i++)
	{
		mMap->GetJumpPtr(i)->Reset();
	}

	//more jump 재생성
}

void Stage5::onTouchesBegan(const vector<Touch*>&touches, Event *unused_event)
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

					mpGameOver->Hide(5);
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
void Stage5::onTouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesMoved(touches, unused_event);
}
void Stage5::onTouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesEnded(touches, unused_event);
	
}
void Stage5::onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesCancelled(touches, unused_event);
}


void Stage5::ReplaceNextStage()
{
	if (true == mMap->NextStage(mpPlayer->GetPosition()))
	{
		SoundBox::GetInstance()->Destroy();
		//bug_stageskip
		auto tpScene = Stage2::createScene();
		Director::getInstance()->pushScene(tpScene);
	}
}

void Stage5::PhaseOn(float dt)
{
	mpBoss->PhaseOn();
}

void Stage5::FireSet(float dt)
{
	mpBoss->FireSetPosition(mpPlayer);
}

void Stage5::LaserFire(float dt)
{
	mpBoss->LaserFire();
}

