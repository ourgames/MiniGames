//
//  Effect.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include <string>

#include "Effect.hpp"

//using namespace std;

class IDisplayObject;

class IAttribute : public  cocos2d::Ref
{
public:
    //virtual bool isLockIncrease() = 0;
    //virtual bool isLockDecrease() = 0;
    virtual void addEffect(IEffect * ) = 0;
    virtual void removeEffect(IEffect * ) = 0;
    virtual AttributeType getKey() = 0;
    virtual float getBaseValue() = 0;
    virtual void setBaseValue(float ) = 0;
    virtual float getAfterEffectValue() = 0;
    virtual void setAfterEffectValue(float) = 0;
    
    virtual void calculateAfterEffectValue() = 0; //或有effect加入、有effect失效时计算，标记一个attributeDirty
    //virtual bool isAttributeDirty() = 0;
    
    virtual void setLockIncrease(bool isLock) = 0; //是否禁止属性增加
    virtual void setLockDecrease(bool isLock) = 0; //是否禁止属性减少
    
    virtual bool isLockIncrease() = 0;
    virtual bool isLockDecrease() = 0;
    
    virtual void update(float dt) = 0;
    
    virtual void setDisplayObject(IDisplayObject * ) = 0;
    
    virtual IDisplayObject * getDisplayObject() = 0;
    
    virtual ~IAttribute() {}
    
};

class Attribute : public  IAttribute
{
    
public:
    
    Attribute(AttributeType key, float baseValue);
    virtual ~Attribute();
    
    static Attribute* create(AttributeType key, float baseValue) {}
    virtual bool init() {}
    virtual void addEffect(IEffect * pEffect) ;
    virtual void removeEffect(IEffect * pEffect) ;
    virtual AttributeType getKey();
    virtual float getBaseValue();
    
    virtual float getAfterEffectValue();
    
    void setBaseValue(float baseValue);
    void setAfterEffectValue(float);
   
    
    virtual void calculateAfterEffectValue() ; //每帧计算，或有effect加入、有effect失效时计算，标记一个attributeDirty
    
    
    virtual void setLockIncrease(bool isLock); //是否禁止属性增加
    virtual void setLockDecrease(bool isLock); //是否禁止属性减少
    
    virtual bool isLockIncrease() ;
    virtual bool isLockDecrease() ;
    
    virtual void update(float dt);
    
    virtual void setDisplayObject(IDisplayObject * pDisplayObject) {mDisplayObject = pDisplayObject; }
    
    virtual IDisplayObject * getDisplayObject() {return mDisplayObject; }
    
private:
    //bool isAttributeDirty();
    void sortAllEffect();
    
    //std::list<IEffect * > mEffectList;
    cocos2d::Vector<IEffect*> mEffectList;
    AttributeType mAttributeKey;
    float mBaseValue;
    float mAfterEffectValue;
    bool mIsAttributeDirty;
    bool mIsLockIncrease;
    bool mIsLockDecrease;
    IDisplayObject * mDisplayObject;
};

#endif /* Attribute_hpp */
