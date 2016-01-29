//
//  Track.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/29.
//
//

#ifndef Track_hpp
#define Track_hpp

#include <stdio.h>
#include "DisplayObject.hpp"


class Track : public IDisplayObject
{
public:
    Track();
    virtual ~Track();
    static Track * create();
    virtual bool init();
    
    void update(float dt);
    void updateAttribute(float dt);
    void updatePosition(float dt);

    void addAttribute(IAttribute * );
    void addEffect(IEffect *);

    cocos2d::Rect getCollisionBox()
    {
        cocos2d::Rect res;
        return res;
    }
    cocos2d::Rect getMagnetBox()
    {
        cocos2d::Rect res;
        return res;
    }
    void onCollision(IDisplayObject * pCollisionTarget)
    {
        
    }
    cocos2d::Vec2 getPosition()
    {
        cocos2d::Vec2 res;
        return res;
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
    cocos2d::Map<int, IAttribute*> mAttributeList;
    std::vector<int> mAttributeKeyList;
    
};
#endif /* Track_hpp */
