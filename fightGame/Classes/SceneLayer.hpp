//
//  SceneLayer.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef SceneLayer_hpp
#define SceneLayer_hpp

#include <stdio.h>
#include "Track.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Entity.hpp"

class SceneLayer : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    float distance;
    float time;
    
    Track * track;
    Player * player;
    Vector<Entity *> entityManager;//障碍道具管理器
    
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback2(cocos2d::Ref* pSender);
    void menuCloseCallback3(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneLayer);
    
    void createGameScreen();
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    
};
#endif /* SceneLayer_hpp */
