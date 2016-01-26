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
    
    void update(float dt,cocos2d::Node * render_node,IDisplayObject *pCollisionTarget);
    void updateBaseBlockPosition(float dt);
    void testCollision(IDisplayObject *pCollisionTarget);
    void testAvoid(IDisplayObject *pCollisionTarget);
    void setArray();
    
    BlockType generateBlockType();
    void generateBlock(cocos2d::Node * render_node);
    
    void removeBlock(BaseBlock * pBaseBlock);
    void removeTrackBlock(BaseBlock * pBaseBlock);
    void addTouchEffect(TouchDirection dir);
    
    float getDisTime()
    {
        return mDisTimer;
    }
    cocos2d::Vector <BaseBlock *> mBaseBlockArray;
    cocos2d::Vector<BaseBlock *> mTrackBlockArray;
protected:
    std::vector<float> mChanceArray;
    std::vector<int> mGenerateNumArray;
//    cocos2d::Vector <BaseBlock *> mBaseBlockArray;
//    cocos2d::Vector<BaseBlock *> mTrackBlockArray;
    float mDisTimer;
    float mTimTimer;
};
#endif /* BlockManager_hpp */
