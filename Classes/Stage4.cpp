#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage4.h"
#include "CBgLight.h"
#include "LightEffect.h"
#include "EffectSprite.h"
#include "Stage5.h"
#include "SoundBox.h"

using namespace cocos2d;
using namespace std;


Scene* Stage4::createScene()
{
	return Stage4::create();
}

// on "init" you need to initialize your instance
bool Stage4::init()
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

	


	mpLayerForJoyPad = Layer::create();
	this->addChild(mpLayerForJoyPad, 103);

	winSize = Director::getInstance()->getWinSize();

	StageInit();//�������� ������ �ʿ��� ��ü�� ������ ����ִ� �Լ�
	
	
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(Stage4::ObjectReset), 2.0f);


	
	return true;
}

void Stage4::update(float dt)
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

void Stage4::onEnter()
{
	Scene::onEnter();

	mpListener = EventListenerTouchAllAtOnce::create();

	

	mpListener->onTouchesBegan = CC_CALLBACK_2(Stage4::onTouchesBegan, this);
	mpListener->onTouchesMoved = CC_CALLBACK_2(Stage4::onTouchesMoved, this);
	mpListener->onTouchesEnded = CC_CALLBACK_2(Stage4::onTouchesEnded, this);
	mpListener->onTouchesCancelled = CC_CALLBACK_2(Stage4::onTouchesCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);

	//mpKeyListener = EventListenerKeyboard::create();
	//mpKeyListener->onKeyPressed = CC_CALLBACK_2(Stage4::onKeyPressed, this);
	//mpKeyListener->onKeyReleased = CC_CALLBACK_2(Stage4::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mpKeyListener, this);
}

void Stage4::onExit()
{
	Scene::onExit();
}

void Stage4::StageInit()
{
	mMap = new CMap();
	mMap->Create(mpLayerForWorld, 4);

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

	ShaderInit(); 


	SoundBox::GetInstance()->Create();
	SoundBox::GetInstance()->PlayBGM(4, true);
	//���� ������ �ʿ��� ��ü ����


}

//void Stage4::onKeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyPressed(keyCode, event);
//}
//void Stage4::onKeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	mpPlayer->KeyReleased(keyCode, event);
//}

void Stage4::ObjectReset(float dt)
{
	for (int i = 0; i < mMap->GetJumpPointNum(); i++)
	{
		mMap->GetJumpPtr(i)->Reset();
	}

	//more jump �����
}

void Stage4::onTouchesBegan(const vector<Touch*>&touches, Event *unused_event)
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

					mpGameOver->Hide(4);
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
void Stage4::onTouchesMoved(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesMoved(touches, unused_event);
}
void Stage4::onTouchesEnded(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesEnded(touches, unused_event);
	
}
void Stage4::onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event)
{
	joypad->TouchesCancelled(touches, unused_event);
}


void Stage4::ReplaceNextStage()
{
	if (true == mMap->NextStage(mpPlayer->GetPosition()))
	{
		SoundBox::GetInstance()->Destroy();
		//bug_stageskip
		auto tpScene = Stage5::createScene();
		Director::getInstance()->pushScene(tpScene);
	}
}

void Stage4::ShaderInit()
{
	Size tWinSize = Director::getInstance()->getWinSize();
	mpRender = RenderTexture::create(800, 480, Texture2D::PixelFormat::RGBA8888);
	mpRender->retain();
	mpRender->setPosition(Vec2(400, 240));
	mpRender->setScaleX(0.5f);
	BGTexture = mpRender->getSprite()->getTexture();

	this->addChild(mpRender, 100);

	//ryu_test
	mpLayerForWorld->setScaleY(-1.0f);

	
	


	_screenW = Director::getInstance()->getWinSize().width;
	_screenH = Director::getInstance()->getWinSize().height;
	_scale = _screenW / 1920;

	_effect = LightEffect::create();
	_effect->retain();

	_lightPos = Vec3(_screenW - 100, _screenH - 100, 102);
	_effect->setLightPos(_lightPos);
	_effect->setLightCutoffRadius(1000);
	_effect->setBrightness(2.0);

	_lightSprite = Sprite::create("BossBullet.png");
	_lightSprite->setPosition(_lightPos.x, _lightPos.y);
	this->addChild(_lightSprite, 102);

	
	addBackGroundTile();

}

EffectSprite* Stage4::addBackGroundTile()
{
	EffectSprite* background = EffectSprite::createWithTexture(BGTexture);
	background->setColor(_effect->getAmbientLightColor());
	background->setAnchorPoint(Vec2(0, 0));
	background->setScale(1.0f);
	background->setEffect(_effect, BGTexture);
	this->addChild(background,102);

	return background;
}

void Stage4::UpdateRender()
{
	mpRender->begin();
	mpLayerForWorld->visit();
	mpRender->end();

	
	
	_lightPos.set(mpPlayer->GetPosition().x, mpPlayer->GetPosition().y, _lightPos.z);
	_effect->setLightPos(_lightPos);
	
}
