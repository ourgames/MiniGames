//
//  ItemRes.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/25.
//
//

#ifndef ItemRes_hpp
#define ItemRes_hpp

#include <string.h>
#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ItemRes : public cocos2d::Sprite{
    float speed;// 下降速度
    int w_index;
    int h_index;
//    cocos2d::Size visibleSize;
//    cocos2d::Vec2 origin;
    bool m_isAtive;//是否碰撞
public:
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(string, filename, Filename);//图片文件名字
    //CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(int, occupyNum, OccupyNum); //占道位宽
    CC_SYNTHESIZE(float, score, Score);//角色得分
    CC_SYNTHESIZE(float, energe, Energe);//角色体力
    CC_SYNTHESIZE(float, timeEffect, TimeEffect); //影响时间
    CC_SYNTHESIZE(float, distanceEffect, DistanceEffect);
    CC_SYNTHESIZE(int, moveType, MoveType); //左右移动
    
    ItemRes(void);
    ~ItemRes(void);
    
    //static ItemRes * create(void);
    CREATE_FUNC(ItemRes);
    
    virtual void update(float dt);
    virtual bool init();
    bool isCollasion();
    bool isNear();
    virtual void isCollasionCallback(cocos2d::Ref* pSender);
    virtual void isNearCallback(cocos2d::Ref* pSender);
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
#endif /* ItemRes_hpp */
