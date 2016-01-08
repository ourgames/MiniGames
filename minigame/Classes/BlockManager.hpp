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
#include "Track.hpp"
#include "Player.hpp"

#define MAX_COUNT 100

USING_NS_CC;


class BlockManager
{
    int * blockcreatechance;
    CCDictionary * dict;
    CCDictionary * effectdict;
    
//    static CCDictionary * dict;
    
    CC_SYNTHESIZE(float, blockDistance, BlockDistance);
    CC_SYNTHESIZE(float, blockCreateDistance, BlockCreateDistance);
    CC_SYNTHESIZE(float, blockTime, BlockTime);
    CC_SYNTHESIZE(float, blockReduce, BlockReduce);
public:
    
    CCArray * blocklist;
    
    BlockManager();
    ~BlockManager();
    
    int getCreateBlockType();
    Block * createBlock();
    Block * createBlock(int type);
    Block * createClone(Block * obj);
    void displayBlock(Track *track,cocos2d::Node * render_node);
    void createManager(Track *track,cocos2d::Node * render_node);
    void createManager();
    void blockMove(Track *track,cocos2d::Node * render_node);
    
    //CCDictionary * initDict();
    void initDict();
    void initEffectDict();
    
    void isCollision(Player * player);
    
    void setBlockCreateChance(int * num);
};
#endif /* BlockManager_hpp */
