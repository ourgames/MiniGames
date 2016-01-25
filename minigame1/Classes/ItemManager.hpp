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

class ItemManager
{
public:
    
    ItemManager();
    ~ItemManager();
    
    void update(float dt,cocos2d::Node * render_node);
    void updateItemPosition(float dt);
    void testCollision(IDisplayObject *pCollisionTarget);
    void testAvoid(IDisplayObject *pCollisionTarget);
    void setArray();
    
    ItemType generateItemType();
    void generateItem(cocos2d::Node * render_node);
    
    void removeItem(Item * pItem);

protected:
    std::vector<float> mChanceArray;
    std::vector<int> mGenerateNumArray;
    cocos2d::Vector <Item *> mItemArray;

};
#endif /* ItemManager_hpp */
