//
//  test.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
class test : public cocos2d::Layer
{
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(test);
    
    void createGameScreen();
    void onEnter();
    void onExit();
    void update(float dt);
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * event);
    
    void createObstacle(int fre,cocos2d::Node * render_node);
};
#endif /* test_hpp */
