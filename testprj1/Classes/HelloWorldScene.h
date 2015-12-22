#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
    cocos2d::Sprite * player;
    cocos2d::CCArray * clouds;
    cocos2d::Size visibleSize;
    cocos2d::Sprite * terrain1;
    cocos2d::Sprite * terrain2;
    cocos2d::Sprite * terrain3;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float dt);
    //void onEnter();
    void onExit();
    
     //bool ccTouchBegan(cocos2d::CCTouch * pTouch,cocos2d::CCEvent * pEvent);
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
};

#endif // __HELLOWORLD_SCENE_H__
