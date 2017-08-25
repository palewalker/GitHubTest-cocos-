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
    
    auto tlblTitle = Label::createWithSystemFont("WheelJoint", "arial.ttf",14);
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
    
    
    
    b2WheelJointDef jd1;
    b2WheelJointDef jd2;
    
    mpBodyCar = this->addNewSprite(Point(340, 70), Size(100, 40), b2_dynamicBody, NULL, 0);
    b2Body *body1 = this->addNewSprite(Point(310, 50), Size(30, 30), b2_dynamicBody, NULL, 1);
    b2Body *body2 = this->addNewSprite(Point(370, 50), Size(30, 30), b2_dynamicBody, NULL, 1);
    
    b2Vec2 axis(0.0f, 1.0f);
    
    jd1.Initialize(mpBodyCar, body1, body1->GetPosition(), axis);
    jd1.motorSpeed = 30.0f;
    jd1.maxMotorTorque = 20.0f;
    jd1.enableMotor = true;
    jd1.frequencyHz = 4.0f;
    //jd1.dampingRatio = 0.7f;
    
    jd2.Initialize(mpBodyCar, body2, body2->GetPosition(), axis);
    jd2.motorSpeed = 30.0f;
    jd2.maxMotorTorque = 20.0f;
    jd2.enableMotor = true;
    jd2.frequencyHz = 4.0f;
    //jd2.dampingRatio = 1.0f;
    
    mWheel_0 = (b2WheelJoint*)_world->CreateJoint(&jd1);
    mWheel_1 = (b2WheelJoint*)_world->CreateJoint(&jd2);
    
    
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
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
    
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
    
    b2Vec2 p = mpBodyCar->GetPosition();
    //log("%f..%f", p.x, p.y);
    if (p.x < 1.6)
    {
        mWheel_0->SetMotorSpeed(-30.0f);
        mWheel_1->SetMotorSpeed(-30.0f);
    }
    else if (p.x > 13.4) {
        mWheel_0->SetMotorSpeed(30.0f);
        mWheel_1->SetMotorSpeed(30.0f);
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
