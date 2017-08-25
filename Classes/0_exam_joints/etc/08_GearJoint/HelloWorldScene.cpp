#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto tlblTitle = Label::createWithSystemFont("GearJoint", "arial.ttf",14);
    tlblTitle->setPosition(Vec2(240,300));
    this->addChild(tlblTitle, 50);
    
    // 윈도우 크기를 구한다.
    winSize = Director::getInstance()->getWinSize();
    
    // 이미지의 텍스쳐를 구한다.
    texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");
    
    // 월드 생성
    if (this->createBox2dWorld(true))
    {
        this->schedule(schedule_selector(HelloWorld::tick));
    }
    
    
    return true;
}

bool HelloWorld::createBox2dWorld(bool debug)
{
    // 월드 생성 시작 --------------------------------------------------------------------------
    
    // 중력의 방향을 결정한다.
    b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
    
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    
    // 디버그 드로잉 설정
    if (debug) {
        // 적색 : 현재 물리 운동을 하는 것
        // 회색 : 현재 물리 운동량이 없는 것
        m_debugDraw = new GLESDebugDraw(PTM_RATIO);
        _world->SetDebugDraw(m_debugDraw);
        
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        //flags += b2Draw::e_aabbBit;
        //flags += b2Draw::e_pairBit;
        //flags += b2Draw::e_centerOfMassBit;
        m_debugDraw->SetFlags(flags);
    }
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body *groundBody = _world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;
    
    // 아래쪽.
    groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
    groundBody->CreateFixture(&boxShapeDef);
    // 왼쪽
    groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    // 위쪽
    groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
                   b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    // 오른쪽
    groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
                   b2Vec2(winSize.width / PTM_RATIO, 0));
    groundBody->CreateFixture(&boxShapeDef);
    
    // 월드 생성 끝   --------------------------------------------------------------------------
    
    
    
    b2GearJointDef tGearJointDef;
    
    b2RevoluteJointDef jointDef1;
    b2RevoluteJointDef jointDef2;
    b2RevoluteJoint *joint1;
    b2RevoluteJoint *joint2;
    
    
    /*
    b2Body *body0 = this->addNewSprite(Point(240, 160),      Size(160, 60), b2_staticBody, NULL, 0);
    b2Body *body1 = this->addNewSprite(Point(240 - 22, 160), Size(40, 40),  b2_dynamicBody, NULL, 1);
    b2Body *body2 = this->addNewSprite(Point(240 + 22, 160), Size(40, 40),  b2_dynamicBody, NULL, 1);
     */
    
    
    b2Body *body0 = this->addNewSprite(Point(240, 160),      Size(160, 60), b2_staticBody, NULL, 0);
    b2Body *body1 = this->addNewSprite(Point(240 - 22, 160), Size(40, 40),  b2_dynamicBody, "CloseNormal.png", 1);
    b2Body *body2 = this->addNewSprite(Point(240 + 22, 160), Size(40, 40),  b2_dynamicBody, "CloseNormal.png", 1);
    
    
    
    jointDef1.Initialize(body0, body1, body1->GetPosition());
    jointDef2.Initialize(body0, body2, body2->GetPosition());
    
    jointDef1.enableMotor = true;
    jointDef1.motorSpeed = 1;
    jointDef1.maxMotorTorque = 10;
    
    // joint1 생성전에 위 모터의 속성들이 정의되어야 한다.
    joint1 = (b2RevoluteJoint *)_world->CreateJoint(&jointDef1);
    joint2 = (b2RevoluteJoint *)_world->CreateJoint(&jointDef2);
    
        //body와 joint들을 이용하여 joint를 정의한다.
        tGearJointDef.bodyA = body1;
        tGearJointDef.bodyB = body2;
        
        tGearJointDef.joint1 = (b2Joint *)joint1;
        tGearJointDef.joint2 = (b2Joint *)joint2;
        
        //tGearJointDef = 2.0;
        tGearJointDef.ratio = 1.0;
    
    _world->CreateJoint(&tGearJointDef);
    
    
    return true;
}

HelloWorld::~HelloWorld()
{
    delete _world;
    _world = NULL;
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    Layer::draw(renderer, transform, flags);
    
    kmGLPushMatrix();
    
    _world->DrawDebugData();
    
    kmGLPopMatrix();
}

void HelloWorld::tick(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 3;
    
    // Step : 물리 세계를 시뮬레이션한다.
    _world->Step(dt, velocityIterations, positionIterations);
    
    // 만들어진 객체 만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            Sprite* spriteData = (Sprite *)b->GetUserData();
            
            spriteData->setPosition(Point(b->GetPosition().x * PTM_RATIO,
                                          b->GetPosition().y * PTM_RATIO));
            spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

b2Body* HelloWorld::addNewSprite(Point point, Size size, b2BodyType bodytype,
                                 const char* spriteName, int type)
{
    // 바디데프 만들고 속성들을 지정한다.
    b2BodyDef bodyDef;
    bodyDef.type = bodytype;
    bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
    
    if (spriteName){
        if (strcmp(spriteName, "test") == 0) {
            int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
            int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
            Sprite* sprite = Sprite::createWithTexture(texture,
                                                       Rect(32 * idx, 32 * idy, 32, 32));
            sprite->setPosition(point);
            this->addChild(sprite);
            
            bodyDef.userData = sprite;
        }
        else {
            Sprite* sprite = Sprite::create(spriteName);
            sprite->setPosition(point);
            this->addChild(sprite);
            
            bodyDef.userData = sprite;
        }
    }
    
    // 월드에 바디데프의 정보로 바디를 만든다.
    b2Body *body = _world->CreateBody(&bodyDef);
    
    // 바디에 적용할 물리 속성용 바디의 모양을 만든다.
    b2FixtureDef fixtureDef;
    b2PolygonShape dynamicBox;
    b2CircleShape circle;
    
    if (type == 0) {
        dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
        
        fixtureDef.shape = &dynamicBox;
    }
    else {
        circle.m_radius = (size.width / 2) / PTM_RATIO;
        
        fixtureDef.shape = &circle;
    }
    
    // Define the dynamic body fixture.
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;
    
    body->CreateFixture(&fixtureDef);
    
    return body;
}
