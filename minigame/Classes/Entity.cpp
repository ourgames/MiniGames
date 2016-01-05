//
//  Entity.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Entity.hpp"

Entity::Entity()
{
    //actor = new Sprite::create();
    actor = new Sprite();
    
    filename = nullptr;
    
    _width = 65;
    _height = 65;
    
    w_index = 0;
    h_index = 0;
    
    moveUpDown = {0,false,0,0};
    moveLeftRight = {0,false,0,0};
}

Entity::~Entity()
{
    
}
bool Entity::setActor(cocos2d::Ref *actor)
{
    actor = actor;
}
