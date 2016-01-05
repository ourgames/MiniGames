//
//  Item.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Item.hpp"

Item::Item()
{
    itemcreatechance = new int[4];
    
    type = Coin;
    isActive = true;
    
    itemDistance = 0;
    itemBlockDistance = 0;
    
}

Item::~Item()
{
    
}