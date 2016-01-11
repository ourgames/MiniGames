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
    
    player->setFilename("xiabai.jpg");
    Node * playeractor =player->getActor();
    playeractor = Sprite::create("xiaobai.jpg");
    playeractor->setAnchorPoint(ccp(0,0));
    playeractor->setScale(0.3, 0.3);
    //player->setPosition(origin.x + 20 + track->getCircuitWidth() * (2 + (int)track->getTrackState()), origin.y + playeractor->getContentSize().height * 0.3/2);
    playeractor->setPosition(origin.x + 20 + track.getCircuitWidth() * (2 + (int)track.getTrackState()), origin.y + playeractor->getContentSize().height * 0.3/2);
    player->addChild(playeractor);
    
    return player;
}

void GameLayer::createGameScreen()
{
    
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    
    bg = CCArray::createWithCapacity(4);
    bg->retain();
    
    Sprite * _bg;
    for (int i = 0; i < 4; i++) {
        _bg = Sprite::create("yejing.jpg");
        _bg->setAnchorPoint(ccp(0,0));
        _bg->setPosition(origin.x,origin.y + i * _bg->getContentSize().height );
        this->addChild(_bg,-100);
        bg->addObject(_bg);
    }

    //
    player = Sprite::create("daxia.png");
    player->setAnchorPoint(ccp(0,0));
    player->setScale(0.07, 0.07);
    player->setPosition(origin.x + 40 + track.getCircuitWidth() * (2 + (int)track.getTrackState()), player->getContentSize().height * 0.05 /2);
    player->retain();
    //this->addChild(player,1);
    
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
    
    
//
//    auto moveTo1 = MoveTo::create(1.0, Point(origin.x + visibleSize.width * 0.5,origin.y + visibleSize.height * 0.85));
//    //player->runAction(moveTo1);
//    
//    
//    
//    
//    auto player2 = Sprite::create("xiaobai.jpg");
//    player2->setScale(0.5, 0.5);
//    player2->setPosition(origin.x + visibleSize.width * 0.5,origin.y + visibleSize.height * 0.75);
//    //this->addChild(player2,1,kTagSprite2);
//    
//    //    layer->addChild(player,10,kTagSprite);
//    //    createObstacle(10,layer);
}

void GameLayer::createObstacle(int num,cocos2d::Node * render_node)
{
    //clouds = CCArray::createWithCapacity(35);
    //clouds->retain();
//    
//    for (int i = 0; i < num; i++) {
//        int rand_w = rand() % 5;
//        int rand_h = rand() % 7;
//        
//        Sprite * _cloud = Sprite::createWithSpriteFrameName("cloud.png");
//        _cloud->setAnchorPoint(ccp(0,0));
//        _cloud->setPosition(origin.x + rand_w * 128,origin.y + rand_h * 128 + 64 + visibleSize.height);
//        
//        float distance = origin.y + rand_h * 128 + 64 + visibleSize.height + _cloud->getContentSize().height;
//        float time = distance / 30;
//        auto obstacle_moveTo = MoveTo::create(time, Point(origin.x + rand_w * 128,origin.y - _cloud->getContentSize().height));
//        _cloud->runAction(obstacle_moveTo);
//        
//        render_node->addChild(_cloud,10);
//    
//        //clouds->addObject(_cloud);
//        //w->addObject(rand_w);
//        
//    }
    
}

void GameLayer::labelSetString(cocos2d::Label * label,float distance)
{
    std::stringstream buffer;
    buffer << distance;
    std::string str = buffer.str();
    label->setString(str);
}

//bool GameLayer::isCollasion()
//{
////    auto s1 = getChildByTag(kTagSprite);
////    auto s2 = getChildByTag(kTagSprite2);
////    CCRect rect = s1->getBoundingBox();
////    CCPoint point = s2->getPosition();
////    return rect.containsPoint(point);
//}

void GameLayer::onEnter()
{
    CCLayer::onEnter();
}

void GameLayer::onExit()
{
    bg->release();
    player->release();
    //clouds->release();
    
    CCLayer::onExit();
}

void GameLayer::update(float dt)
{
    distance += dt * 80;
    trackvar += dt * 80;
    blockvar += dt * 80;
    
//    totletime += dt;
//    if (totletime >= delay) {
//        int number = rand() % 5;
//        createObstacle(number, this);
//        totletime = 0;
//    }
    if (true) {//游戏未结束
        
        // 背景移动
        bg->retain();
        Sprite * _bg;
        int _count = bg->count();
        for (int i = 0; i < _count; i++) {
            _bg = (Sprite * )bg->objectAtIndex(i);
            _bg->setPositionY(_bg->getPositionY() - track.getCourseSpeed());
            if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
                Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 2) % 3);
                _bg->setPositionY(next_bg->getPositionY() + next_bg->getContentSize().height - 20);
            }
        }
        bg->release();
        
        //判断是否变道
        if (trackvar >= track.getChangeCourseDistance()) {
            trackvar -= track.getChangeCourseDistance();
            track.changeChannel();
            //trackvar -= track.getChangeCourseDistance();
            player->retain();
            player->setPosition(origin.x + 40 + track.getCircuitWidth() * (2 + (int)track.getTrackState()), origin.y + player->getContentSize().height * 0.05 /2);
            player->release();
        }
        
        //显示距离
        labelSetString(distancelabel,distance);
        labelSetString(distancevarlabel,trackvar);
        labelSetString(mark,(float)track.getTrackState());
        
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
        
        //障碍运动
        bmr.blockMove(&track, this);
        
        
        
//        /*
//         auto s = getChildByTag(kActionLayer);
//         s->setPositionY(s->getPositionY() - 3);
//         if (s->getPositionY() + s->boundingBox().size.height < 0) {
//         ;
//         }
//         */
//        //        Sprite * _obstacle;
//        //        ///clouds->retain();
//        //        int _obstaclecount = clouds->count();
//        //        for (int i = 0; i < _obstaclecount; i++) {
//        //            _obstacle = (Sprite * )clouds->objectAtIndex(i);
//        //            _obstacle->setPositionY(_obstacle->getPositionY() - 20);
//        //            if (_obstacle->getPositionY() + _obstacle->boundingBox().size.height < 0) {
//        //                clouds->removeObjectAtIndex(i);
//        //            }
//        //        }
//        //clouds->release();
//        
//        
//        //player->setPositionX(player->getPositionX() - 2);
//        player->setPositionY(player->getPositionY() - 25);
//        
//        //        if (isCollasion()) {
//        //            auto s1 = getChildByTag(kTagSprite);
//        //            auto s2 = getChildByTag(kTagSprite2);
//        //            s2->setVisible(false);
//        //        }
    }
//    //    else
//    //    {
//    //        Sprite * _bg;
//    //        int _count = bg->count();
//    //        for (int i = 0; i < _count; i++) {
//    //            _bg = (Sprite * )bg->objectAtIndex(i);
//    //            _bg->stopAllActions();
//    //        }
//    //    }
    
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    auto location = touch->getLocation();
//    
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
//    //s->runAction(RotateTo::create(1, at));
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



