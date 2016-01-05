//
//  Block.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "game.h"
#include "Entity.hpp"

class Block : public Entity
{
    int createnumber;
    //int blockcreatechance[7];
    int * blockcreatechance;
public:
    CC_SYNTHESIZE(BlockType, type, Type);
    CC_SYNTHESIZE(bool, isActive, IsActive);
    
    CC_SYNTHESIZE(float, blockDistance, BlockDistance);
    CC_SYNTHESIZE(float, blockCreateDistance, BlockCreateDistance);
    CC_SYNTHESIZE(float, blockTime, BlockTime);
    CC_SYNTHESIZE(float, blockReduce, BlockReduce);
    
    //Vector<Entity> entitylist;
    
    Block(void);
    virtual ~Block();
};
#endif /* Block_hpp */
