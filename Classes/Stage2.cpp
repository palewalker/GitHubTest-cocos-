#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage2.h"

#include "CRyuPathFinder.hpp"
#include "Stage3.h"
#include "SoundBox.h"

USING_NS_CC;


Scene* Stage2::createScene()
{
	return Stage2::create();
}

// on "init" you need to initialize your instance
bool Stage2::init()
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
	this->schedule(schedule_selector(Stage2::ObjectReset), 2.0f);
	this->schedule(schedule_selector(Stage2::PacManAstar), 2.0f);


	
	return true;
}

void Stage2::update(float dt)
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

	//팩맨 STATE 체크(상태별 애니메이션 변경), A* 이동
	mpPacMan->Show();
	mpPacMan->UpdateMove(dt);

	ReplaceNextStage();
	mpPacMan->CollisionWithPlayer(mpPlayer);
	PacManReset();

	
}

void Stage2::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerTouchAllAtOnce::create();

	

	mpListener->onTouchesBegan = CC_CALLBACK_2(Stage2::onTouchesBegan, this);
	mpListener->onTouchesMoved = CC_CALLBACK_2(Stage2::onTouchesMoved, this);
	mpListener->onTouchesEnded = CC_CALLBACK_2(Stage2::onTouchesEnded, this);
	mpListener->onTouchesCancelled = CC_CALLBACK_2(Stage2::onTouchesCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	//mpKeyListener = EventListenerKeyboard::create();
	//mpKeyListener->onKeyPressed = CC_CALLBACK_2(Stage2::onKeyPressed, this);
	//mpKeyListener->onKeyReleased = CC_CALLBACK_2(Stage2::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mpKeyListener, this);
}

void Stage2::onExit()
{
	Scene::onExit();
}

void Stage2::StageInit()
{
	mMap = new CMap();
	mMap->Create(mpLayerForWorld, 2);

	mpPlayer = new CPlayer();
	mpPlayer->SetScene(this);
	mpPlayer->Create(mMap);
	mpPlayer->SaveInit();

	mpPacMan = new CPacMan();
	mpPacMan->Create();
	mpPacMan->SetScene(this);
	mpPacMan->Build();
	mpPacMan->SetPosition(mMap->PacManSpawn());
	mpPacMan->SetOrigin(mMap->PacManSpawn());
	mpPacMan->RunAni();

	joypad = new JoyStick();
	joypad->create(mpLayerForJoyPad, Vec2(80, 240));
	
	mpGameOver = new CGameOver();
	mpGameOver->Create(this);

	CInterFace::GetInstance()->SetScene(this);
	CInterFace::GetInstance()->SetInterFace();

	//A*
	//mpPathFinder = new CPathFinder();
	mpPathFinder = new CRyuPathFinder();
	mpPathFinder->Create();

	SoundBox::GetInstance()->Create();
	SoundBox::GetInstance()->PlayBGM(2, true);


	


	//게임 구성에 필요한 객체 생성


}

//void Stage2::onKeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyPressed(keyCode, event);
//}
//void Stage2::onKeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyReleased(keyCode, event);
//}

void Stage2::ObjectReset(float dt)
{
	for (int i = 0; i < mMap->GetJumpPointNum(); i++)
	{
		mMap->GetJumpPtr(i)->Reset();
	}

	//more jump 재생성
}

void Stage2::onTouchesBegan(const vector<Touch*>&touches, Event *unused_event)
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
				

					mpGameOver->Hide(2);
				

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
void Stage2::onTouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesMoved(touches, unused_event);
}
void Stage2::onTouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesEnded(touches, unused_event);


	
}
void Stage2::onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesCancelled(touches, unused_event);
}

void Stage2::PacManAstar(float dt)
{
	if (ALIVE == mpPlayer->GetState())
	{
		int tRow = 0;
		int tCol = 0;

		int iRow = 0;
		int iCol = 0;

		tRow = (480 - mpPlayer->GetPosition().y - 16) / 16;
		tCol = (mpPlayer->GetPosition().x) / 16;

		iRow = (480 - mpPacMan->GetPosition().y) / 16;
		iCol = (mpPacMan->GetPosition().x) / 16;

		Vec2 tVecBegin = Vec2::ZERO;
		tVecBegin.x = iCol;//mpPacMan->GetCol();
		tVecBegin.y = iRow; //mpPacMan->GetRow();

		Vec2 tVecEnd = Vec2::ZERO;
		tVecEnd.x = tCol;
		tVecEnd.y = tRow;

		mpPacMan->StopMove();

		mpPathFinder->InputClickData(tVecBegin, tVecEnd);
		mpPathFinder->FindPath(mMap);

		mpPathFinder->SetRoadData();




		int ti = 0;

		for (ti = 0; ti < mpPathFinder->m_RoadVec.size(); ti++)
		{
			Vec2 tVec = mpPathFinder->m_RoadVec[mpPathFinder->m_RoadVec.size() - 1 - ti];

			mpPacMan->m_RoadVec.push_back(tVec);
		}

		mpPacMan->BeginMove();
	}
}

void Stage2::ReplaceNextStage()
{
	if (true == mMap->NextStage(mpPlayer->GetPosition()))
	{
		SoundBox::GetInstance()->Destroy();
		//bug_stageskip
		auto tpScene = Stage3::createScene();
		Director::getInstance()->pushScene(tpScene);
	}
}

void Stage2::PacManReset()
{
	if (true == mpGameOver->IsShow())
	{
		mpPacMan->SetPosition(mMap->PacManSpawn());

	}
}

