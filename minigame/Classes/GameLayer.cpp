//
//  GameLayer.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/5.
//
//

#include "GameLayer.hpp"
#include <sstream>
#include "Block.hpp"
//#include "GameLayerVar.h"
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
    
    distance = 0;
    trackvar = 0;
    blockvar = 0;
    blocktimevar = 0;
//    delay = 1.5;
//    totletime = 0;
    
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
Player * GameLayer::createPlayer()
{
    Player * player = Player::create();
    player->retain();
    
    player->setFilename("xiaobai.jpg");
    Sprite * playeractor = Sprite::create("xiaobai.jpg");
    
    
    playeractor->setAnchorPoint(ccp(0,0));
    playeractor->setScale(0.3, 0.3);
    //player->setPosition(origin.x + 20 + track->getCircuitWidth() * (2 + (int)track->getTrackState()), origin.y + playeractor->getContentSize().height * 0.3/2);
    playeractor->setPosition(origin.x + 20 + track.getCircuitWidth() * (2 + (int)track.getTrackState()), origin.y + playeractor->getContentSize().height * 2);
    //playeractor->retain();
    player->setActor(playeractor);
    
    Movement playermv1 = {0,false,0,0};
    Movement playermv2 = {1,false,0,3};
    player->setMoveUpDown(playermv1);
    player->setMoveLeftRight(playermv2);
    //player->addChild(playeractor);
    
    return player;
}

void GameLayer::createGameScreen()
{
    
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    
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
    
    playerreal = createPlayer();
    this->addChild(playerreal,1);
    
    distancelabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    distancelabel->setPosition(origin.x + visibleSize.width - distancelabel->getContentSize().width, origin.y + visibleSize.height - distancelabel->getContentSize().height);
    labelSetString(distancelabel,distance);
    this->addChild(distancelabel,1);
    
    mark = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    mark->setPosition(origin.x + visibleSize.width - distancelabel->getContentSize().width, origin.y + visibleSize.height - distancelabel->getContentSize().height * 3);
    labelSetString(mark,(float)track.getTrackState());
    this->addChild(mark,1);
    
    distancevarlabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    distancevarlabel->setPosition(origin.x + visibleSize.width - distancevarlabel->getContentSize().width, origin.y + visibleSize.height - distancevarlabel->getContentSize().height * 2);
    labelSetString(distancevarlabel,trackvar);
    this->addChild(distancevarlabel,1);
    
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
    playerreal->release();
    CCLayer::onExit();
}

void GameLayer::update(float dt)
{
    distance += dt * track.getCourseSpeed();
    trackvar += dt * track.getCourseSpeed();
    blockvar += dt * track.getCourseSpeed();
    blocktimevar += dt;
    
    if (playerreal->getIsMagnet()) {
        MagnetTimeVar += dt;
        if (MagnetTimeVar >= MagnetTime) {
            
            playerreal->setIsMagnet(false);
            playerreal->setPickUpDistance(playerreal->getPickUpDistance() - MagVal);
            //playerreal->setPickUpDistance(playerreal->getPickUpDistance()-Mag)
            MagnetTime = 0;
            MagnetTimeVar = 0;
            MagVal = 0;
        }
        
    }
    
    if (playerreal->getIsDizzy()) {
        BlockDizzyVar += dt;
        if (BlockDizzyVar >= BlockDizzy) {
            playerreal->setMoveLeftRightEnable(true);
            playerreal->setIsDizzy(false);
            BlockDizzy = 0;
            BlockDizzyVar = 0;
        }
    }
    
    if (playerreal->getIsUpSpeed()) {
        InvincibleTimeVar += dt;
        if (InvincibleTimeVar >= InvincibleTime) {
            playerreal->setIsUpSpeed(false);
            track.setCourseSpeed(track.getCourseSpeed() - InviVal);
            InviVal = 0;
            InvincibleTime = 0;
            InvincibleTimeVar = 0;
        }
    }
    if (true) {//游戏未结束
        
        // 背景移动
        bg->retain();
        Sprite * _bg;
        int _count = bg->count();
//        for (int i = 0; i < _count; i++) {
//            _bg = (Sprite * )bg->objectAtIndex(i);
//            _bg->setPositionY(_bg->getPositionY() - track.getCourseSpeed());
//            if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
//                Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 3) % 4);
//                _bg->setPositionY(next_bg->getPositionY() + next_bg->boundingBox().size.height);
//            }
//        }
        for (int i = 0; i < _count; i++) {
            _bg = (Sprite * )bg->objectAtIndex(i);
            //_bg->setPositionY(_bg->getPositionY() - track.getCourseSpeed());
            if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
                Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 2) % 3);
                //_bg->setPositionY(next_bg->getPositionY() + next_bg->boundingBox().size.height - track.getCourseSpeed() * dt);
                _bg->setPositionY(next_bg->getPositionY() + next_bg->boundingBox().size.height);
                _bg->setPositionY(_bg->getPositionY() - track.getCourseSpeed());
            }
            else
            {
                _bg->setPositionY(_bg->getPositionY() - track.getCourseSpeed());
            }
        }
        bg->release();
        
        //判断是否变道
        if (trackvar >= track.getChangeCourseDistance()) {
            trackvar -= track.getChangeCourseDistance();
            track.changeChannel();
            //trackvar -= track.getChangeCourseDistance();
//            playerreal->retain();
//            playerreal->getActor()->setPosition(origin.x + 20 + track.getCircuitWidth() * (2 + (int)track.getTrackState()), origin.y + playerreal->getActor()->getContentSize().height * 0.3 /2);
//            playerreal->release();
        }
        
        //显示距离
        labelSetString(distancelabel,distance);
        labelSetString(distancevarlabel,playerreal->getTotalStamina());
        labelSetString(mark,playerreal->getScore());
        
        //生成障碍并显示
        if (blockvar >= bmr.getBlockDistance()) {
            blockvar -= bmr.getBlockDistance();
            bmr.createManager(&track,this);
//            //int crnm = BlockCreateNumber[bmr.getCreateBlockType()];
//            
//            //for (int i = 0; i < crnm; i++) {
//                Block * block = bmr.createBlock();
//                Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
//                blockactor->setAnchorPoint(ccp(0,0));
//                blockactor->setScale(0.75, 1.0);
//                //blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() + visibleSize.height);
//                blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() * 0.5 );
//                this->addChild(block,1);
//            //}

        }
        
        if (blocktimevar >= bmr.getBlockTime()) {
            if (bmr.getBlockDistance() - bmr.getBlockReduce() <= 200) {
                bmr.setBlockDistance(200);
            }
            else
                bmr.setBlockDistance(bmr.getBlockDistance() - bmr.getBlockReduce());
            blocktimevar -= bmr.getBlockTime();
        }
        
        
        //障碍运动
        bmr.blockMove(&track, this);
        
        //主角移动
        Node * playeractor = playerreal->getActor();
        if (playerreal->getMoveLeftRightEnable())
        {
            switch (playerreal->getMoveLeftRight().direction) {
                case 0:
                    if (playeractor->getPositionX() - playerreal->getMoveLeftRight().speed < origin.x) {
                        playeractor->setPositionX(origin.x);
                    }
                    else
                        playeractor->setPositionX(playeractor->getPositionX() - playerreal->getMoveLeftRight().speed);
                    break;
                case 1:
                    if (playeractor->getPositionX() + playerreal->getMoveLeftRight().speed > visibleSize.width) {
                        playeractor->setPositionX(visibleSize.width);
                    }
                    else
                        playeractor->setPositionX(playeractor->getPositionX() + playerreal->getMoveLeftRight().speed);
                    break;
                default:
                    break;
            }
            
        }
        
        // 判断碰撞
        bmr.isCollision(playerreal,&track);
        
        bmr.deleteDeathBlock();

    }
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location = touch->getLocation();
    
    Node * playeractor = playerreal->getActor();
    float left = origin.x;
    float right = visibleSize.width;
    float up = 200;
    float down = origin.y;
    playerreal->setMoveLeftRightEnable(true);
    if (location.x <= visibleSize.width/2) {
        playerreal->setMoveLeftRightDir(0);
    }
    else{
        playerreal->setMoveLeftRightDir(1);
    }
    return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    playerreal->setMoveLeftRightEnable(false);
    
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



