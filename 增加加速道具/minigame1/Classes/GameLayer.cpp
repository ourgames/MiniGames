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
    //总里程数
    distance = 0;
    //创建暂停 恢复 停止按钮
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
    
    
    //创建初始游戏场景
    createGameScreen();
    
    track = Track::create();
    //globleVector = cocos2d::Layer::create();
    this->addChild(track);
    //createGameScreen();
    this->scheduleUpdate();
    
    //添加事件监听
    this->setTouchEnabled(true);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameLayer::createGameScreen()
{
    //创建背景图片
    bg = CCArray::createWithCapacity(3);
    bg->retain();
    Sprite * _bg;
    for (int i = 0; i < 3; i++) {
        _bg = Sprite::create("yejing.jpg");
        _bg->setAnchorPoint(ccp(0,0));
        _bg->setPosition(origin.x,origin.y + i * _bg->boundingBox().size.height );
        this->addChild(_bg,-100);
        //track->addChild(_bg);
        bg->addObject(_bg);
    }
    
    //创建显示总里程数 得分值 体力值的显示Label
    label1 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label1->setPosition(origin.x + visibleSize.width - label1->getContentSize().width, origin.y + visibleSize.height - label1->getContentSize().height);
    this->addChild(label1,1);
    
    label2 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label2->setPosition(origin.x + visibleSize.width - label2->getContentSize().width, origin.y + visibleSize.height - label2->getContentSize().height * 2);
    this->addChild(label2,1);
    
    label3 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label3->setPosition(origin.x + visibleSize.width - label3->getContentSize().width, origin.y + visibleSize.height - label3->getContentSize().height * 3);
    this->addChild(label3,1);

    //创建玩家角色
    player = Player::create();
    this->addChild(player,1);
}
 //在label上显示数据的函数
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
    //里程数增加
    distance += dt * COURCESPEED;
    //背景移动
    bgUpdate(dt);
    //障碍管理更新
    //blockmanager.update(dt,this,player);
    blockmanager.update(dt,track,player);
    //道具管理更新
    //itemmanager.update(dt, this, player);
    itemmanager.update(dt, track, player);
    //角色管理更新
    player->update(dt);
    
    track->update(dt);
    //显示里程数 得分 体力
    labelSetString(label1, distance);
    labelSetString(label2, player->getAttributeValueByKey(AttributeType::SOCRE));
    labelSetString(label3, player->getAttributeValueByKey(AttributeType::STAMINA));
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchPosition = touch->getLocation();
//    
//    float left = origin.x;
//    float right = visibleSize.width;
//    float up = 200;
//    float down = origin.y;
//
//    TouchDirection dir;
//    
//    if (location.x <= visibleSize.width/2) {
//        dir = TouchDirection::LEFT;
//    }
//    else{
//        dir = TouchDirection::RIGHT;
//    }
//    player->addTouchEffect(dir);
//    
    return true;

}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //获取触摸点位置
    auto location = touch->getLocation();
    
    float left = origin.x;
    float right = visibleSize.width;
    float up = 200;
    float down = origin.y;
    
    TouchDirection dir;
    
    if (location.x <= visibleSize.width/2) {
        dir = TouchDirection::LEFT;
    }
    else{
        dir = TouchDirection::RIGHT;
    }
    //player->addTouchEffect(dir);
    //追踪障碍添加响应
    blockmanager.addTouchEffect(dir);
    //auto location = touch->getLocation();
//    player->setPositionX(location.x);
//    player->setPositionY(location.y);

}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //    auto location = touch->getLocation();
    //    player->setPositionX(location.x);
    //    player->setPositionY(location.y);
    //触摸move时，对角色位置属性添加立即生效的equal effect
    auto location = touch->getLocation();
    
    
    player->addPositionXEffect(location.x - touchPosition.x);
    player->addPositionYEffect(location.y - touchPosition.y);
    
    touchPosition = location;
    //player->setPosition(location);
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



