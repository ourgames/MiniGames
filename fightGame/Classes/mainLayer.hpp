//
//  mainLayer.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/23.
//
//

#ifndef mainLayer_hpp
#define mainLayer_hpp

#include <stdio.h>
class MainLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback2(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
};

#endif /* mainLayer_hpp */
