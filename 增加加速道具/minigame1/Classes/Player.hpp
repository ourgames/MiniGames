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
    void addPositionXEffect(float value);
    void addPositionYEffect(float value);
    virtual void updatePosition(float dt);
    cocos2d::Rect getMagnetBox()
    {
        return mMagnetBox;
    }

protected:
    Node * actor;
    float mStanimaReduce;
};


#endif /* Player_hpp */
