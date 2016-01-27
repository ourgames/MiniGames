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
    
    virtual cocos2d::Rect getMagnetBox() = 0;
    
    virtual void addAttribute(IAttribute * ) = 0;
    
    virtual void addEffect(IEffect * ) = 0;
    
    virtual void onCollision(IDisplayObject * pCollisionTarget) = 0;
    
    virtual cocos2d::Vec2 getPosition() = 0;
    
    virtual ~IDisplayObject() {}
   
};




class BaseDisplayObject : public IDisplayObject
{
public:
    BaseDisplayObject(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed) : mPosition(position)
    {
        mCollisionBox.size.width = collisionSize.width;
        mCollisionBox.size.height = collisionSize.height;
        mCollisionBox.origin.x = mPosition.x - collisionSize.width/2;
        mCollisionBox.origin.y = mPosition.y - collisionSize.height/2;
        
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
    
    virtual cocos2d::Rect getMagnetBox() {return mCollisionBox; }
    
    virtual void addAttribute(IAttribute * );
    
    virtual void addEffect(IEffect * );
    
//    virtual void updatePosition(float dt)
//    {
//        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
//        
//        float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
//        float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
//        
//        if (mPosition.x + dt * xSpeed < origin.x + mCollisionBox.size.width/2 ) {
//            mPosition.x = origin.x + mCollisionBox.size.width/2;
//        }
//        else
//        {
//            if (mPosition.x + dt * xSpeed > visibleSize.width - mCollisionBox.size.width/2) {
//                mPosition.x = visibleSize.width - mCollisionBox.size.width/2;
//            }
//            else
//            {
//                mPosition.x = mPosition.x + dt * xSpeed;
//                
//            }
//        }
//        if (mPosition.y + dt * ySpeed < origin.y) {
//            mAlive = false;
//        }
//        else
//            mPosition.y = mPosition.y + dt * ySpeed;
//        
//        
//        float xSize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_X);
//        float ySize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_Y);
//        mCollisionBox.origin.x = mPosition.x - xSize * 0.5;
//        mCollisionBox.origin.y = mPosition.y - ySize * 0.5;
//    }
    virtual void updatePosition(float dt)
    {
        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        
        float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
        float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
        
        if (this->getPositionX() + dt * xSpeed < origin.x + mCollisionBox.size.width/2 ) {
            this->setPositionX(origin.x + mCollisionBox.size.width/2);
        }
        else
        {
            if (this->getPositionX() + dt * xSpeed > visibleSize.width - mCollisionBox.size.width/2) {
                this->setPositionX(visibleSize.width - mCollisionBox.size.width/2);
            }
            else
            {
                //mPosition.x = mPosition.x + dt * xSpeed;
                this->setPositionX(this->getPositionX() + dt * xSpeed);
            }
        }
        if (this->getPositionY() + dt * ySpeed < origin.y) {
            mAlive = false;
            this->setVisible(false);
        }
        else
            this->setPositionY(this->getPositionY() + dt * ySpeed);
        
        
        float xSize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_X);
        float ySize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_Y);
        mCollisionBox.origin.x = this->getPositionX() - mCollisionBox.size.width/2;
        mCollisionBox.origin.y = this->getPositionY() - mCollisionBox.size.height/2;
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
    virtual cocos2d::Vec2 getPosition()
    {
        return mPosition;
    }
    float getAttributeValueByKey(AttributeType key)
    {
        IAttribute * pAttribute =  mAttributeList.at(key);
        if(pAttribute)
        {
            return pAttribute->getAfterEffectValue();
        }
        return -1;
    }
protected:
//    float getAttributeValueByKey(AttributeType key)
//    {
//        IAttribute * pAttribute =  mAttributeList.at(key);
//        if(pAttribute)
//        {
//            return pAttribute->getAfterEffectValue();
//        }
//        return -1;
//    }
    cocos2d::Vec2 mPosition;
    cocos2d::Rect mCollisionBox;
    cocos2d::Rect mMagnetBox;
    //cocos2d::Size mCollisionSize;
    cocos2d::Map<int, IAttribute*> mAttributeList;
    std::vector<int> mAttributeKeyList;
    bool mAlive;
};

//in layer.update

#endif /* DisplayObject_hpp */
