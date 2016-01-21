//
//  Effect.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef DisplayObject_hpp
#define DisplayObject_hpp



#include <string> 
#include "Attribute.hpp"
#include "Effect.hpp"

using namespace std;


class IDisplayObject : public cocos2d::Node
{
public:
    virtual void updateAttribute(float ) = 0;
    
    virtual void updatePosition(float ) = 0;
    
    //virtual void checkCollision(float, IDisplayObject *  ) = 0;
    
    virtual cocos2d::Rect getCollisionBox() = 0;
    
    virtual void addAttribute(IAttribute * ) = 0;
    
    virtual void addEffect(IEffect * ) = 0;
    
    virtual void onCollision(IDisplayObject * pCollisionTarget) = 0;
    
    virtual ~IDisplayObject() {}
   
};




class BaseDisplayObject : public IDisplayObject
{
public:
    BaseDisplayObject(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed) : mPosition(position)
    {
        mCollisionBox.size.width = collisionSize.width;
        mCollisionBox.size.height = collisionSize.height;
        mCollisionBox.origin.x = mPosition.x - mCollisionBox.size.width * 0.5;
        mCollisionBox.origin.y = mPosition.y - mCollisionBox.size.height * 0.5;
        
        IAttribute * pXSpeedAttribute = Attribute::create(AttributeType::SPEED_X, speed.x);
        addAttribute(pXSpeedAttribute);
        IAttribute * pYSpeedAttribute = Attribute::create(AttributeType::SPEED_Y, speed.y);
        addAttribute(pYSpeedAttribute);
        IAttribute * pXSizeAttribute = Attribute::create(AttributeType::COLLISION_SIZE_X, collisionSize.width);
        addAttribute(pXSizeAttribute);
        IAttribute * pYSizeAttribute = Attribute::create(AttributeType::COLLISION_SIZE_Y, collisionSize.height);
        addAttribute(pYSizeAttribute);
    }
    
    BaseDisplayObject();
    
    virtual bool init(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed);
   
    //CREATE_FUNC(BaseDisplayObject);
    
    //static BaseDisplayObject * create();
    
    //virtual bool init();
    
    virtual ~BaseDisplayObject()
    {
        mAttributeList.clear();
        mAttributeKeyList.clear();
    }
    
    virtual cocos2d::Rect getCollisionBox() {return mCollisionBox; }
    
    virtual void addAttribute(IAttribute * );
    
    virtual void addEffect(IEffect * );
    
    virtual void updatePosition(float dt)
    {
        float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
        float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
        mPosition.x = mPosition.x + dt * xSpeed;
        mPosition.y = mPosition.y + dt * ySpeed;
        float xSize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_X);
        float ySize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_Y);
        mCollisionBox.origin.x = mPosition.x - xSize * 0.5;
        mCollisionBox.origin.y = mPosition.y - ySize * 0.5;
    }

    virtual void updateAttribute(float dt)
    {
        for(auto iter = mAttributeKeyList.begin(); iter != mAttributeKeyList.end(); ++iter)
        {
            int key = *(iter);
            IAttribute * pAttribute = mAttributeList.at(key);
            if(pAttribute)
            {
                pAttribute->update(dt);
            }
        }
    }
    //virtual void onCollision(IDisplayObject *pCollisionTarget);
    
    virtual void setAlive(bool value)
    {
        mAlive = value;
    }
    virtual bool getAlive()
    {
        return mAlive;
    }
protected:
    float getAttributeValueByKey(AttributeType key)
    {
        IAttribute * pAttribute =  mAttributeList.at(key);
        if(pAttribute)
        {
            return pAttribute->getAfterEffectValue();
        }
        return -1;
    }
    cocos2d::Vec2 mPosition;
    cocos2d::Rect mCollisionBox;
    //cocos2d::Size mCollisionSize;
    cocos2d::Map<int, IAttribute*> mAttributeList;
    std::vector<int> mAttributeKeyList;
    bool mAlive;
};

//in layer.update

#endif /* DisplayObject_hpp */
