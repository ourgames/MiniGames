//
//  Player.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "DisplayObject.hpp"
#include "CommonUtil.hpp"
#include "GlobalVar.hpp"
#include "Attribute.hpp"
#include "Effect.hpp"


class Player : public BaseDisplayObject
{
public:
    Player();
    
    static Player * create();
    virtual bool init();
    
    virtual ~Player();
    
    void update(float dt);
    void onCollision(IDisplayObject *pCollisionTarget);
    void addTouchEffect(TouchDirection dir);
    void addStaminaReduceEffect();
    virtual void updatePosition(float dt);
    cocos2d::Rect getMagnetBox()
    {
        return mMagnetBox;
    }
//    virtual void updatePosition(float dt)
//    {
//        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
//        
//        float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
//        float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
//        
//        if (this->getPositionX() + dt * xSpeed < origin.x + mCollisionBox.size.width/2 ) {
//            this->setPositionX(origin.x + mCollisionBox.size.width/2);
//        }
//        else
//        {
//            if (this->getPositionX() + dt * xSpeed > visibleSize.width - mCollisionBox.size.width/2) {
//                this->setPositionX(visibleSize.width - mCollisionBox.size.width/2);
//            }
//            else
//            {
//                //mPosition.x = mPosition.x + dt * xSpeed;
//                this->setPositionX(this->getPositionX() + dt * xSpeed);
//            }
//        }
//        if (this->getPositionY() + dt * ySpeed < origin.y) {
//            mAlive = false;
//            this->setVisible(false);
//        }
//        else
//            this->setPositionY(this->getPositionY() + dt * ySpeed);
//        
//        
//        float xSize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_X);
//        float ySize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_Y);
//        mCollisionBox.origin.x = mPosition.x - xSize * 0.5;
//        mCollisionBox.origin.y = mPosition.y - ySize * 0.5;
//    }
protected:
    Node * actor;
//    float mScore;
//    float mStamina;
    float mStanimaReduce;
    //cocos2d::Rect mMagnetBox;
};


#endif /* Player_hpp */
