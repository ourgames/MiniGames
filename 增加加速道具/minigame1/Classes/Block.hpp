//
//  Block.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "DisplayObject.hpp"
#include "CommonUtil.hpp"
#include "GlobalVar.hpp"
#include "Attribute.hpp"
#include "Effect.hpp"

typedef enum
{
    NormalBlock,
    BigBlock,
    DizzyBlock,
    LeftBlock,
    RightBlock,
    TrackBlock,
    HighSpeedBlock,
    
}BlockType;

class BaseBlock : public BaseDisplayObject
{
public:
    //BaseBlock(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed,BlockType type);
    //BaseBlock(BlockType type,cocos2d::Vec2 position);
    BaseBlock();
    
    static BaseBlock * create(BlockType type,cocos2d::Vec2 position);
    //CREATE_FUNC(BaseBlock);
    //virtual bool init();
    virtual bool init(BlockType type,cocos2d::Vec2 position);
    
    virtual ~BaseBlock();
    BlockType getType();
   
    void onCollision(IDisplayObject *pCollisionTarget);
    void onAvoid(IDisplayObject *pCollisionTarget);
    void update(float dt);
    void addCollisionEffect(IDisplayObject *pCollisionTarget);
    void addAvoidEffect(IDisplayObject *pCollisionTarget);
    void setAvoid(bool var)
    {
        isAvoid = var;
    }
    bool getAvoid()
    {
        return isAvoid;
    }
protected:
    Node * actor;
    BlockType mBlockType;
    float mScore;//躲过获得的分数值
    float mStamina;//碰撞减少的体力值
    float mTime;//碰撞后效果的持续时间
    bool isAvoid;//标记角色是否已经躲过了障碍
    std::vector<int> mBlockEffectList;
};

//class TrackBlock : public BaseBlock
//{
//    static TrackBlock * create(BlockType type,cocos2d::Vec2 position);
//};
#endif /* Block_hpp */
