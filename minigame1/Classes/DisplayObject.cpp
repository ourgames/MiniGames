//
//  Effect.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "DisplayObject.hpp"

BaseDisplayObject::BaseDisplayObject()
{
    mAlive = true;
}

bool BaseDisplayObject::init(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed)
{
    bool result;
    
    mPosition = position;
    //this->setPosition(mPosition);
    this->setPositionX(position.x);
    this->setPositionY(position.y);
    
    mCollisionBox.size.width = collisionSize.width;
    mCollisionBox.size.height = collisionSize.height;
    mCollisionBox.origin.x = mPosition.x - collisionSize.width/2;
    mCollisionBox.origin.y = mPosition.y - collisionSize.height/2;
    
    IAttribute * pXSpeedAttribute = Attribute::create(AttributeType::SPEED_X, speed.x);
    IAttribute * pYSpeedAttribute = Attribute::create(AttributeType::SPEED_Y, speed.y);

    IAttribute * pXSizeAttribute = Attribute::create(AttributeType::COLLISION_SIZE_X, collisionSize.width);
    IAttribute * pYSizeAttribute = Attribute::create(AttributeType::COLLISION_SIZE_Y, collisionSize.height);

    
    if (pXSpeedAttribute && pYSpeedAttribute && pXSizeAttribute && pXSizeAttribute) {
        addAttribute(pXSpeedAttribute);
        addAttribute(pYSpeedAttribute);
        addAttribute(pXSizeAttribute);
        addAttribute(pYSizeAttribute);
        result = true;
    }
    else result = false;
    
    return result;
}

void BaseDisplayObject::addAttribute(IAttribute * pAttribute)
{
    if(pAttribute)
    {
        int key = pAttribute->getKey();
        if(mAttributeList.at(key) == nullptr)
        {
            mAttributeList.insert(key, pAttribute);
            pAttribute->setDisplayObject(this);
            mAttributeKeyList.push_back(key);
        }
        
    }
}

void BaseDisplayObject::addEffect(IEffect * pEffect)
{
    if(!pEffect)
        return;
    int key = pEffect->getAttributeKey();
    IAttribute * pAttribute = mAttributeList.at(key);
    if(pAttribute)
    {
        pAttribute->addEffect(pEffect);
    }
}

//void BaseDisplayObject::onCollision(IDisplayObject *pCollisionTarget)
//{
//    if (condition) {
//        statements
//    }
//}