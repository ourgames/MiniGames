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
    //int createnumber;
    //int blockcreatechance[7];
    //int * blockcreatechance;
    //CC_SYNTHESIZE(int, createnumber, CreateNumber);
    CC_SYNTHESIZE(BlockType, type, Type);
    CC_SYNTHESIZE(bool, isActive, IsActive);
    
//    CC_SYNTHESIZE(float, blockDistance, BlockDistance);
//    CC_SYNTHESIZE(float, blockCreateDistance, BlockCreateDistance);
//    CC_SYNTHESIZE(float, blockTime, BlockTime);
//    CC_SYNTHESIZE(float, blockReduce, BlockReduce);
public:
    //Vector<Entity> entitylist;
    //int * effectlist;
    CCArray * effectlist;
    
    //Block(void);
    virtual ~Block();
    
    CREATE_FUNC(Block);
    
    //void setBlockCreateChance(int * num);
    virtual bool init();
    bool isAlive();
    void setEffectlist(cocos2d::CCArray * array);
    CCArray * getEffectlist();
};
#endif /* Block_hpp */
