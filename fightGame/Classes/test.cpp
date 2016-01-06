//
//  test.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#include "test.hpp"
#include "LocalController.h"
USING_NS_CC;

enum
{
    kTagSprite = 1,
    kActionLayer = 2,
};

Scene* test::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = test::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool test::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    visibleSize = Director::getInstance()->getVisibleSize();
//    origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(test::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    CCDictionary * dict = LocalController::shared()->DBXMLManager()->getObjectByKey("200005");
    
    auto obj = dynamic_cast<CCString*>(dict->objectForKey("icon"));
    
    label->setString(obj->getCString());
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
  
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("yejing.jpg");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 1);
    this->addChild(label, 1);
    //createGameScreen();
    
    //this->schedule(schedule_selector(HelloWorld::update),0.1);
    //this->schedule(schedule_selector(HelloWorld::update));
    //this->scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(test::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(test::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    return true;
}

void test::createGameScreen()
{
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    

}

void test::createObstacle(int fre,cocos2d::Node * render_node)
{
    
}
void test::onEnter()
{
    CCLayer::onEnter();
}

void test::onExit()
{
    CCLayer::onExit();
}

void test::update(float dt)
{
}

bool test::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void test::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void test::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}