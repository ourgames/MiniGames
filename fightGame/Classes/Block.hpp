//
//  Block.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Entity.hpp"
#include "Effect.hpp"

typedef enum {
    NormalBlock,
    BigBlock,
    DizzyBlock,
    LeftBlock,
    RightBlock,
    TrackBlock,
    HighSpeedBlock
} BlockType;

typedef enum {
    block_hit,
    block_hard_hit,
    block_light_hit
} HPValue;

typedef enum {
    course_speed,
    block_move_speed,
    high_speed_block
} SpeedValue;

class Block: public Entity,public Effect
{
    int block_create_chance[7];
public:
    CC_SYNTHESIZE(BlockType, type, Type);
    
    CC_SYNTHESIZE(float, block_distance, BlockDistance);
    CC_SYNTHESIZE(float, block_create_distance, BlockCreateDistance);
    CC_SYNTHESIZE(float, block_time, BlockTime);
    CC_SYNTHESIZE(float, block_reduce, blockReduce);
    
    
//    Block();
//    ~Block(void);
    
    CREATE_FUNC(Block);
    
    virtual bool init();
    
};
#endif /* Block_hpp */
