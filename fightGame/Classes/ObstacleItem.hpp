//
//  ObstacleItem.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef ObstacleItem_hpp
#define ObstacleItem_hpp

#include <stdio.h>
#include "Entity.hpp"

typedef enum {
    Block,
    Item
} Type;

typedef enum {
    NormalBlock,
    BigBlock,
    DizzyBlock,
    LeftBlock,
    RightBlock,
    TrackBlock,
    HighSpeedBlock
} BlockType;

typedef enum{
    Coin,
    Invincible,
    HP,
    Magnet
} ItemType;

class ObstacleItem : public Entity
{
public:
    CC_SYNTHESIZE(Type, OItype, OItype);
    //CC_SYNTHESIZE(<#varType#>, <#varName#>, <#funName#>)
    CC_SYNTHESIZE(float, HPEffect, HPEffect);
    CC_SYNTHESIZE(float, ScoreEffect, ScoreEffect);
    CC_SYNTHESIZE(float, EffectTime, EffectTime);
    CC_SYNTHESIZE(float, EffectDistance, EffectDistance);
    
    CC_SYNTHESIZE(float, PickUpDistance, PickUpDistance);
    
};

#endif /* ObstacleItem_hpp */
