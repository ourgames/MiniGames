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
    
    //void update(float dt,cocos2d::Node * render_node,IDisplayObject *pCollisionTarget);
    void update(float dt,IDisplayObject * render_node,IDisplayObject *pCollisionTarget);
    void updateBaseBlockPosition(float dt);
    void testCollision(IDisplayObject *pCollisionTarget);
    void testAvoid(IDisplayObject *pCollisionTarget);
    void setArray();
    
    BlockType generateBlockType();
    //void generateBlock(cocos2d::Node * render_node);
    void generateBlock(IDisplayObject * render_node);
    
    void removeBlock(BaseBlock * pBaseBlock);
    void removeTrackBlock(BaseBlock * pBaseBlock);
    void addTouchEffect(TouchDirection dir);
    
    float getDisTime()
    {
        return mDisTimer;
    }
    cocos2d::Vector <BaseBlock *> mBaseBlockArray;//生成的常规道具的管理list
    cocos2d::Vector<BaseBlock *> mTrackBlockArray;//生成的追踪道具的管理list
protected:
    std::vector<float> mChanceArray;//生成各种障碍的概率数组
    std::vector<int> mGenerateNumArray;//一次生成各种道具个数的数组
//    cocos2d::Vector <BaseBlock *> mBaseBlockArray;
//    cocos2d::Vector<BaseBlock *> mTrackBlockArray;
    float mDisTimer;//记录移动距离的自变量
    float mTimTimer;//记录经过时间的自变量
};
#endif /* BlockManager_hpp */
