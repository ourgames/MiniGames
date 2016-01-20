//
//  Block.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#include "Block.hpp"

BaseBlock::BaseBlock(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed,BlockType type):BaseDisplayObject(position, collisionSize, speed),mBlockType(type)
{
    
}

//BaseBlock::BaseBlock(BlockType type,cocos2d::Vec2 position) : BaseDisplayObject(position)
//{
//    
//}

BaseBlock::~BaseBlock()
{
    
}