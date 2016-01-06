//
//  Entity.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Entity_hpp
#define Entity_hpp

#include <string.h>
#include <stdio.h>
#include "cocos2d.h"
#include "game.h"
//#include "Movement.h"

USING_NS_CC;
using namespace std;


class Entity : public cocos2d::Node{
    Node * actor;//节点类型
//    Movement * moveUpDown;
//    Movement * moveLeftRight;

    CC_SYNTHESIZE(string, filename, Filename);//图片文件名字
    //大小
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    //位置
    CC_SYNTHESIZE(int, w_index, W_index);
    CC_SYNTHESIZE(int, h_index, H_index);
    
    CC_SYNTHESIZE(Movement, moveUpDown, MoveUpDown); //上下移动
    CC_SYNTHESIZE(Movement, moveLeftRight, MoveLeftRight);
public:
    bool setActor(Node * actor);
    Node * getActor();
    bool addActor();
    
    CREATE_FUNC(Entity);
    
    //Entity(void);
    virtual ~Entity(void);
    virtual bool init();
    //virtual
//    virtual void update(float dt);
//    virtual bool init();
//    bool isCollasion();
//    bool isNear();
//    //    virtual void isCollasionCallback(cocos2d::Ref* pSender);
//    //    virtual void isNearCallback(cocos2d::Ref* pSender);
//    void show();
//    void hide();
//    bool isAlive();
//    
//    inline virtual void place()//放置位置
//    {
//        //this->setPosition(origin.x + w_index * 128,origin.y + h_index * 128 + 64 + visibleSize.height);
//    }
//    inline int left() {
//        return this->getPositionX() - _width * 0.5f;
//    }
//    
//    //
//    inline int right() {
//        return this->getPositionX() + _width * 0.5f;
//    }
//    
//    //
//    inline int top() {
//        return this->getPositionY() ;
//    }
//    
//    //
//    inline int bottom() {
//        return this->getPositionY() - _height ;
//    }
//    
    
};

#endif /* Entity_hpp */
