//
//  BlockManager.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/5.
//
//

#ifndef BlockManager_hpp
#define BlockManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "game.h"
#include "Block.hpp"
USING_NS_CC;

class BlockManager
{
    int * blockcreatechance;
    CCDictionary * dict;
//    static CCDictionary * dict;
    
    CC_SYNTHESIZE(float, blockDistance, BlockDistance);
    CC_SYNTHESIZE(float, blockCreateDistance, BlockCreateDistance);
    CC_SYNTHESIZE(float, blockTime, BlockTime);
    CC_SYNTHESIZE(float, blockReduce, BlockReduce);
public:
    
    BlockManager();
    ~BlockManager();
    
    Block * createBlock();
    //CCDictionary * initDict();
    void initDict();
    void setBlockCreateChance(int * num);
};
#endif /* BlockManager_hpp */
