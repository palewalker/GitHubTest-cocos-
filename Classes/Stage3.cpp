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

	//게임에 필요한 레이어 생성(게임 월드, 조이패드, 인터페이스)
	mpLayerForWorld = Layer::create();
	this->addChild(mpLayerForWorld, 99);

	mpBlock = Sprite::create("Block.png");
	mpBlock->setPosition(Vec2(400, 240));
	this->addChild(mpBlock, 100);
	

	mpLayerForJoyPad = Layer::create();
	this->addChild(mpLayerForJoyPad, 101);

	

	StageInit();//스테이지 구성에 필요한 객체의 생성이 들어있는 함수

	winSize = Director::getInstance()->getWinSize();
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(Stage3::ObjectReset), 2.0f);


	
	return true;
}

void Stage3::update(float dt)
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


	//렌더 텍스쳐를 통해 화면 회전 효과 구현
	Size tWinSize = Director::getInstance()->getWinSize();
	mpRender = RenderTexture::create(800, 480, Texture2D::PixelFormat::RGBA8888);
	mpRender->retain();
	mpRender->setPosition(Vec2(400, 240));
	mpRender->setScaleX(0.7f);

	auto RotateRender = RotateBy::create(15.0f, 360.0f);
	auto RepeatRender = RepeatForever::create(RotateRender);
	mpRender->runAction(RepeatRender);
	

	this->addChild(mpRender,100);








	//게임 구성에 필요한 객체 생성


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

	//more jump 재생성
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

	//렌더 텍스쳐를 업데이트 함수에 넣어서 신과 동기화

}
