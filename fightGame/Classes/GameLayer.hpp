//
//  GameLayer.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/23.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
class GameLayer : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::CCArray * bg;
    cocos2d::Sprite * player;
    cocos2d::CCArray * clouds;
    
    float delay;
    float totletime;
    
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
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    
    void createObstacle(int fre,cocos2d::Node * render_node);
    
    bool isCollasion();
};
#endif /* GameLayer_hpp */
