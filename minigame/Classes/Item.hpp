//
//  Item.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
//#include "game.h"
#include "Entity.hpp"

class Item : public Entity
{
    //int itemcreatechance[4];
    int * itemcreatechance;
public:
    CC_SYNTHESIZE(ItemType, type, Type);
    CC_SYNTHESIZE(bool, isActive, IsActive);
    
    CC_SYNTHESIZE(float, itemDistance, ItemDistance);
    CC_SYNTHESIZE(float, itemBlockDistance, ItemBlockDistance);
    
    //Vector<Entity> entitylist;
    
    Item();
    virtual ~Item();
    
};
#endif /* Item_hpp */
