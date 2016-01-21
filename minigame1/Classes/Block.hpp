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
    void update(float dt);
    
protected:
    Node * actor;
    BlockType mBlockType;
    float mScore;
    float mStamina;
    float mTime;
    std::vector<int> mBlockEffectList;
};
#endif /* Block_hpp */
