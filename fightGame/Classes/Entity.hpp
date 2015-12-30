//
//  Entity.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef Entity_hpp
#define Entity_hpp

#include <string.h>
#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum {
    block,
    item,//障碍和道具可以合并
    player
};

typedef struct {
    int type;//上下，左右
    int direction;
    float speed;
} Movement;

class Entity : public cocos2d::Sprite{
//    float speed;// 下降速度
//    int w_index;
//    int h_index;
//    bool m_isAtive;//是否碰撞
public:
//    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(string, filename, Filename);//图片文件名字
    //CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
   //大小
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    //位置
    CC_SYNTHESIZE(int, w_index, W_index);
    CC_SYNTHESIZE(int, h_index, H_index);
    
    //CC_SYNTHESIZE(int, occupyNum, OccupyNum); //占道位宽
    
//    CC_SYNTHESIZE(float, score, Score);//角色得分
//    CC_SYNTHESIZE(float, energe, Energe);//角色体力
//    CC_SYNTHESIZE(float, timeEffect, TimeEffect); //影响时间
//    CC_SYNTHESIZE(float, distanceEffect, DistanceEffect);
    
    CC_SYNTHESIZE(Movement, moveUpDown, MoveUpDown); //上下移动
    CC_SYNTHESIZE(Movement, moveLeftRight, MoveLeftRight);
    CC_SYNTHESIZE(float, PickUpDistance, PickUpDistance);
    
//    Entity(void);
//    ~Entity(void);
    
    //static ItemRes * create(void);
    CREATE_FUNC(Entity);
    
    virtual void update(float dt);
    virtual bool init();
    bool isCollasion();
    bool isNear();
    //    virtual void isCollasionCallback(cocos2d::Ref* pSender);
    //    virtual void isNearCallback(cocos2d::Ref* pSender);
    void show();
    void hide();
    bool isAlive();
    
    inline virtual void place()//放置位置
    {
        //this->setPosition(origin.x + w_index * 128,origin.y + h_index * 128 + 64 + visibleSize.height);
    }
    inline int left() {
        return this->getPositionX() - _width * 0.5f;
    }
    
    //
    inline int right() {
        return this->getPositionX() + _width * 0.5f;
    }
    
    //
    inline int top() {
        return this->getPositionY() ;
    }
    
    //
    inline int bottom() {
        return this->getPositionY() - _height ;
    }
    
    
};

#endif /* Entity_hpp */
