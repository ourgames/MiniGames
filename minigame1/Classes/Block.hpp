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
    BaseBlock(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed,BlockType type);
    BaseBlock(BlockType type);
    ~BaseBlock();
    BlockType getType();
    
protected:
    BlockType mBlockType;
    float mScore;
    float mStamina;
    float mTime;
    
};
#endif /* Block_hpp */
