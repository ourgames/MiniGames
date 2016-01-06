//
//  Movement.h
//  minigame
//
//  Created by 葛富臻 on 16/1/6.
//
//

#ifndef Movement_h
#define Movement_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class MoveMent :public cocos2d::Ref
{
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(bool, enable, Enable);
    CC_SYNTHESIZE(int, direction, Direction);
    CC_SYNTHESIZE(float, speed, Speed);
public:
    MoveMent(int type,bool enable,int direction,float speed):type(type),enable(enable),direction(direction),speed(speed)
    {
    }
    static MoveMent * create(int type,bool enable,int direction,float speed)
    {
        MoveMent * movement1 = new MoveMent(type,enable,direction,speed);
        movement1->autorelease();
        return movement1;
    }
    ~MoveMent(){};
};

#endif /* Movement_h */
