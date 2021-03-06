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
#include "Track.hpp"
#include "BlockManager.hpp"
#include "Player.hpp"

//#include "GameLayerVar.h"

class GameLayer : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    Track track;
    BlockManager bmr;
    Player* playerreal;
    
    cocos2d::CCArray * bg;//背景层

    float distance;
    float trackvar;
    float blockvar;
    
    float blocktimevar;
    
    cocos2d::Label * distancelabel;
    cocos2d::Label * distancevarlabel;
    cocos2d::Label * mark;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback2(cocos2d::Ref* pSender);
    void menuCloseCallback3(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    void labelSetString(cocos2d::Label * label,float distance);
    void createGameScreen();
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    
    Player * createPlayer();

};
#endif /* GameLayer_hpp */
