//
//  mainLayer.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/23.
//
//

#include "mainLayer.hpp"
#include "HelloWorldScene.h"
#include <GameLayer.hpp>
USING_NS_CC;

Scene* MainLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroud = Sprite::create("yejing.jpg");
    backgroud->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroud,0);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainLayer::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
  

    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
   
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");

    Sprite * new_game_on;
    Sprite * new_game_off;
    
    new_game_on = Sprite::createWithSpriteFrameName("btn_new_on.png");
    new_game_off = Sprite::createWithSpriteFrameName("btn_new_off.png");
    
    MenuItemSprite * startGameItem = MenuItemSprite::create(new_game_on,new_game_off, CC_CALLBACK_1(MainLayer::menuCloseCallback2, this));
    
    startGameItem->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    startGameItem->setScale(2.0, 2.0);
    
    auto menu2 = Menu::create(startGameItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);
    
    //this->addChild(startGameItem,1);
    
    
    return true;
}

void MainLayer::menuCloseCallback2(Ref* pSender)
{
    auto scene = this->getParent();
    this->removeFromParent();
    auto gamelayer = GameLayer::create();
    scene->addChild(gamelayer);
//    Director::getInstance()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

void MainLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
