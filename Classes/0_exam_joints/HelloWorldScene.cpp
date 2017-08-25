#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "CSceneMouseJt.h"
#include "CSceneRevouteJt.h"

#include "CSceneWeldJt.h"
#include "CScenePrismaticJt.h"

#include "CSceneDistanceJt.h"
#include "CSceneRopeJt.h"

#include "CSceneFrictionJt.h"
#include "CScenePulleyJt.h"

#include "CSceneGearJt.h"
#include "CSceneWheelJt.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto tBtnClose = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    tBtnClose->setPosition(Vec2(480 - 50 , 0 + 50));
    
    
    
    
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(tBtnClose, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    MenuItemFont::setFontSize(14);
    
    auto tBtnJointType_0 = MenuItemFont::create("00_MouseJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    
    tBtnJointType_0->setTag(100);
    
    auto tBtnJointType_1 = MenuItemFont::create("01_RevouteJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    
    tBtnJointType_1->setTag(101);
    
    auto tBtnJointType_2 = MenuItemFont::create("02_WeldJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_2->setTag(102);
    
    auto tBtnJointType_3 = MenuItemFont::create("03_PrismaticJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_3->setTag(103);
    
    auto tBtnJointType_4 = MenuItemFont::create("04_DistanceJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_4->setTag(104);
    
    
    auto tBtnJointType_5 = MenuItemFont::create("05_RopeJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_5->setTag(105);
    
    auto tBtnJointType_6 = MenuItemFont::create("06_FrictionJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_6->setTag(106);
    
    auto tBtnJointType_7 = MenuItemFont::create("07_PulleyJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_7->setTag(107);
    
    auto tBtnJointType_8 = MenuItemFont::create("08_GearJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_8->setTag(108);
    
    auto tBtnJointType_9 = MenuItemFont::create("09_WheelJoint",
                                                CC_CALLBACK_1(HelloWorld::OnClickBtnJointType, this) );
    tBtnJointType_9->setTag(109);
    
    
    
    auto tMenu = Menu::create(tBtnJointType_0,
                              tBtnJointType_1,
                              tBtnJointType_2,
                              tBtnJointType_3,
                              tBtnJointType_4,
                              tBtnJointType_5,
                              tBtnJointType_6,
                              tBtnJointType_7,
                              tBtnJointType_8,
                              tBtnJointType_9,
                              NULL);
    tMenu->setPosition(Vec2(240,160));
    this->addChild(tMenu, 100);
    
    tMenu->alignItemsVertically();
    
    
    

    
    return true;
}

void HelloWorld::OnClickBtnJointType(cocos2d::Ref* pSender)
{
    unsigned int tTag = ((MenuItemFont *)pSender)->getTag();
    
    switch( tTag )
    {
        case 100:
        {
            auto tpScene = CSceneMouseJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 101:
        {
            auto tpScene = CSceneRevouteJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 102:
        {
            auto tpScene = CSceneWeldJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 103:
        {
            auto tpScene = CScenePrismaticJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 104:
        {
            auto tpScene = CSceneDistanceJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 105:
        {
            auto tpScene = CSceneRopeJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 106:
        {
            auto tpScene = CSceneFrictionJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 107:
        {
            auto tpScene = CScenePulleyJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 108:
        {
            auto tpScene = CSceneGearJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
        case 109:
        {
            auto tpScene = CSceneWheelJt::createScene();
            Director::getInstance()->pushScene(tpScene);
        }
            break;
    }
}






void HelloWorld::menuCloseCallback(Ref* pSender)
{
    
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
}




