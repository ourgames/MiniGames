//
//  GameLayer.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/5.
//
//

#include "GameLayer.hpp"
#include <sstream>

USING_NS_CC;


Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
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
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto closeItem2 = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(GameLayer::menuCloseCallback2, this));
    
    closeItem2->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 3 / 2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    auto closeItem3 = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(GameLayer::menuCloseCallback3, this));
    
    closeItem3->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 5 / 2,origin.y + closeItem->getContentSize().height/2));
    

    auto menu = Menu::create(closeItem, closeItem2, closeItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    createGameScreen();
    

    this->scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameLayer::createGameScreen()
{
    bg = CCArray::createWithCapacity(3);
    bg->retain();
    Sprite * _bg;
    for (int i = 0; i < 3; i++) {
        _bg = Sprite::create("yejing.jpg");
        _bg->setAnchorPoint(ccp(0,0));
        _bg->setPosition(origin.x,origin.y + i * _bg->boundingBox().size.height );
        this->addChild(_bg,-100);
        bg->addObject(_bg);
    }
    
    
    label1 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label1->setPosition(origin.x + visibleSize.width - label1->getContentSize().width, origin.y + visibleSize.height - label1->getContentSize().height);
    this->addChild(label1,1);
    
    label2 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label2->setPosition(origin.x + visibleSize.width - label2->getContentSize().width, origin.y + visibleSize.height - label2->getContentSize().height * 2);
    this->addChild(label2,1);
    
    label3 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label3->setPosition(origin.x + visibleSize.width - label3->getContentSize().width, origin.y + visibleSize.height - label3->getContentSize().height * 3);
    this->addChild(label3,1);

}

void GameLayer::labelSetString(cocos2d::Label * label,float distance)
{
    std::stringstream buffer;
    buffer << distance;
    std::string str = buffer.str();
    label->setString(str);
}


void GameLayer::onEnter()
{
    CCLayer::onEnter();
}

void GameLayer::onExit()
{
    bg->release();
    CCLayer::onExit();
}

void GameLayer::bgUpdate(float dt)
{
    // 背景移动
    Sprite * _bg;
    int _count = bg->count();
    for (int i = 0; i < _count; i++) {
        _bg = (Sprite * )bg->objectAtIndex(i);
        if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
            Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 2) % 3);
            _bg->setPositionY(next_bg->getPositionY() + next_bg->boundingBox().size.height);
            _bg->setPositionY(_bg->getPositionY() - 50 * dt);
        }
        else
        {
            _bg->setPositionY(_bg->getPositionY() - 50 * dt);
        }
    }
    
}

void GameLayer::update(float dt)
{
    bgUpdate(dt);
    blockmanager.update(dt,this);
    labelSetString(label1, blockmanager.getDisTime());
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void GameLayer::menuCloseCallback2(Ref* pSender)
{
    Director::getInstance()->pause();
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    exit(0);
    //#endif
}
void GameLayer::menuCloseCallback3(Ref* pSender)
{
    Director::getInstance()->resume();
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    exit(0);
    //#endif
}



