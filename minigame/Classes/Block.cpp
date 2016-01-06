//
//  Block.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Block.hpp"

//Block::Block()
//{
//    createnumber = 4;
////    blockcreatechance = new int[7];
////    effectlist = new int[10];
//    
//    type = NormalBlock;
//    isActive = true;
//    
////    blockCreateDistance = 200;
////    blockDistance = 400;
////    blockTime = 1000;
////    blockReduce = 50;
//    
//    //entitylist = new Entity[5];
//    
//}

Block::~Block()
{
    //delete [] blockcreatechance;
    delete [] effectlist;
    
}
bool Block::init()
{
    if (Entity::init()) {
        setCreateNumber(4);
        setType(NormalBlock);
        setIsActive(true);
        effectlist = new int[10];
    }
    return true;
    //blockcreatechance = new int[7];

    
//    //初始化，后续读表设置 block_create_chance=[30,15,15,10,10,5,15]
//    blockcreatechance[0] = 30;
//    blockcreatechance[1] = 15;
//    blockcreatechance[2] = 15;
//    blockcreatechance[3] = 10;
//    blockcreatechance[4] = 10;
//    blockcreatechance[5] = 5;
//    blockcreatechance[6] = 15;
    
    
}

void Block::setEffectlist(CCArray * array)
{
    int count = array->count();
    for (int i = 0; i < count; i++) {
        CCInteger * obj =(CCInteger *)array->objectAtIndex(i);
        effectlist[i] = obj->getValue();
    }
}