#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
    //cocos2d::Sprite bg1;
    //cocos2d::Sprite bg2;
    cocos2d::CCArray * bg;
    cocos2d::Sprite * player;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::CCArray * w;
    cocos2d::CCArray * h;
    //cocos2d::Vector<int> w;
    //cocos2d::Vector<int> h;
    cocos2d::CCArray * clouds;
    //int[] w;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void createGameScreen();
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    
    void createObstacle(int fre,cocos2d::Node * render_node);
};

#endif // __HELLOWORLD_SCENE_H__
