//
//  Block.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Block.hpp"

Block::Block()
{
    createnumber = 4;
    blockcreatechance = new int[7];
    
    type = NormalBlock;
    isActive = true;
    
    blockCreateDistance = 0;
    blockDistance = 0;
    blockTime = 0;
    blockReduce = 0;
    
    //entitylist = new Entity[5];
    
}

Block::~Block()
{
    
}