//
//  BlockManager.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#ifndef BlockManager_hpp
#define BlockManager_hpp

#include <stdio.h>
#include "Block.hpp"
#include "GlobalVar.hpp"
#include "CommonUtil.hpp"

class BlockManager
{
public:
    
    BlockManager();
    ~BlockManager();
    void update(float dt);
    void updateBaseBlockPosition(float dt);
    void setArray();
    BlockType generateBlockType();
    void generateBlock();
protected:
    std::vector<float> mChanceArray;
    std::vector<int> mGenerateNumArray;
    cocos2d::Vector <BaseBlock *> mBaseBlockArray;
    float distimer;
    float timtimer;
};
#endif /* BlockManager_hpp */
