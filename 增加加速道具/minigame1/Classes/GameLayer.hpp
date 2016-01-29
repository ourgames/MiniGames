//
//  GameLayer.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/5.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
#include "BlockManager.hpp"
#include "Player.hpp"
//#include "GameLayerVar.h"
#include "ItemManager.hpp"
#include "Track.hpp"

class GameLayer : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    //记录上一个触摸位置的position
    cocos2d::Vec2 touchPosition;
    
    //分值显示的label
    cocos2d::Label * label1;
    cocos2d::Label * label2;
    cocos2d::Label * label3;
    
    cocos2d::CCArray * bg;//背景层
    BlockManager blockmanager;
    ItemManager itemmanager;
    
    Player * player;
    float distance;
    
    Track * track;
    //cocos2d::Layer * globleVector;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback2(cocos2d::Ref* pSender);
    void menuCloseCallback3(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    void createGameScreen();
    void bgUpdate(float dt);
    void labelSetString(cocos2d::Label * label,float distance);
    
    
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch * touch,cocos2d::Event * event);

};
#endif /* GameLayer_hpp */
