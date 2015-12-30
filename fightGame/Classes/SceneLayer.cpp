//
//  SceneLayer.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#include "SceneLayer.hpp"
USING_NS_CC;


Scene* SceneLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneLayer::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto closeItem2 = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(SceneLayer::menuCloseCallback2, this));
    
    closeItem2->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 3 / 2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    auto closeItem3 = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(SceneLayer::menuCloseCallback3, this));
    
    closeItem3->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 5 / 2,origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, closeItem2, closeItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    createGameScreen();
    
    //this->schedule(schedule_selector(HelloWorld::update),0.1);
    //this->schedule(schedule_selector(HelloWorld::update));
    this->scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SceneLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(SceneLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void SceneLayer::createGameScreen()
{
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    
}


void SceneLayer::onEnter()
{
    CCLayer::onEnter();
}

void SceneLayer::onExit()
{
    
    CCLayer::onExit();
}

void SceneLayer::update(float dt)
{
    
    
}

bool SceneLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void SceneLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location = touch->getLocation();
    
//    auto s = getChildByTag(kTagSprite);
//    //s->stopAllActions();
//    s->runAction(MoveTo::create(1, Vec2(location.x,location.y)));
//    float o = location.x - s->getPosition().x;
//    float a = location.y - s->getPosition().y;
//    float at = (float) CC_RADIANS_TO_DEGREES(atanf(o/a));
//    
//    if (a < 0) {
//        if (o < 0) {
//            at = 180 + fabs(at);
//        }
//        else
//            at = 180 - fabs(at);
//    }
    //s->runAction(RotateTo::create(1, at));
}

void SceneLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void SceneLayer::menuCloseCallback2(Ref* pSender)
{
    Director::getInstance()->pause();
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    exit(0);
    //#endif
}
void SceneLayer::menuCloseCallback3(Ref* pSender)
{
    Director::getInstance()->resume();
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    exit(0);
    //#endif
}
