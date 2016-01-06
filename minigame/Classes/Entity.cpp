//
//  Entity.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Entity.hpp"

//Entity::Entity()
//{
//    //actor = new Sprite::create();
//    //actor = new Sprite();
//    
//    filename = nullptr;
//    
//    _width = 65;
//    _height = 65;
//    
//    w_index = 0;
//    h_index = 0;
//    
//    moveUpDown = {0,false,0,0};
//    moveLeftRight = {0,false,0,0};
////    moveUpDown = Movement::create(0,false,0,0);
////    moveLeftRight = Movement::create(0,false,0,0);
//}

Entity::~Entity()
{
    
}

bool Entity::setActor(cocos2d::Node *actor)
{
    actor = actor;
}

Node * Entity::getActor()
{
    return actor;
}

bool Entity::addActor()
{
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    //actor = Sprite::create(filename);
    actor = Sprite::createWithSpriteFrameName(getFilename());
    actor->retain();
    this->addChild(dynamic_cast<Sprite*>(actor));
}

bool Entity::init()
{
    if (Node::init()) {
        setFilename("");
        setWidth(65);
        setHeight(65);
        setW_index(0);
        setH_index(0);
        moveUpDown = {0,false,0,0};
        moveLeftRight = {0,false,0,0};
    }
    return true;
    //actor = Sprite::create();

//    setMoveUpDown(<#Movement var#>);
//    setMoveLeftRight(<#Movement var#>);
}