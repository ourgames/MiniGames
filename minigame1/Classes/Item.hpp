//
//  Item.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include "DisplayObject.hpp"
#include "CommonUtil.hpp"
#include "GlobalVar.hpp"
#include "Attribute.hpp"
#include "Effect.hpp"

typedef enum
{
    Coin,
    Invicible,
    Stamina,
    Magnet,
}ItemType;

class Item : public BaseDisplayObject
{
public:
    Item();
    
    static Item * create(ItemType type,cocos2d::Vec2 position);
    virtual bool init(ItemType type,cocos2d::Vec2 position);
    
    virtual ~Item();
    ItemType getType();
    
    void onCollision(IDisplayObject *pCollisionTarget);
    void onAvoid(IDisplayObject *pCollisionTarget);
    void update(float dt);
    void addCollisionEffect(IDisplayObject *pCollisionTarget);
    void addAvoidEffect(IDisplayObject *pCollisionTarget);
protected:
    Node * actor;
    ItemType mItemType;
    float mValue;
    float mTime;
    std::vector<int> mItemEffectList;
};

#endif /* Item_hpp */
