//
//  ItemManager.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#ifndef ItemManager_hpp
#define ItemManager_hpp

#include <stdio.h>
#include "Item.hpp"
#include "GlobalVar.hpp"
#include "CommonUtil.hpp"
//#include "BlockManager.hpp"

class ItemManager
{
public:
    
    ItemManager();
    ~ItemManager();
    
    void update(float dt,cocos2d::Node * render_node,IDisplayObject *pCollisionTarget);
    void updateItemPosition(float dt);
    void testCollision(IDisplayObject *pCollisionTarget);
    void testAvoid(IDisplayObject *pCollisionTarget);
    void setArray();
    
    ItemType generateItemType();
    void generateItem(cocos2d::Node * render_node);
    //bool isAvaliblePosition(cocos2d::Vec2 position,BlockManager * blockmanager);
    void removeItem(Item * pItem);

protected:
    std::vector<float> mChanceArray;
    std::vector<int> mGenerateNumArray;
    cocos2d::Vector <Item *> mItemArray;
    float mDistanceVar;
};
#endif /* ItemManager_hpp */
