//
//  Effect.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Attribute.hpp"

Attribute::Attribute(AttributeType key, float baseValue):mAttributeKey(key), mBaseValue(baseValue), mAfterEffectValue(baseValue),mIsAttributeDirty(false),mIsLockIncrease(false),mIsLockDecrease(false)
{
    
}

Attribute::~Attribute()
{
    mEffectList.clear();
}
Attribute * Attribute::create(AttributeType key, float baseValue)
{
    Attribute * attribute = new (std::nothrow)Attribute(key,baseValue);
    if (attribute && attribute->init()) {
        attribute->autorelease();
        return attribute;
    }
    CC_SAFE_DELETE(attribute);
    return nullptr;
}
bool Attribute::init()
{
    return true;
}
void Attribute::addEffect(IEffect * pEffect)
{
    if(pEffect)
    {
        /*
        if(pEffect->getDurationTime() <= 0.0) //即时效果
        {
            pEffect->calcuAttribute(this);
        }
        
        else 
         */
        pEffect->setTargetAttribute(this);
        {
            if(mEffectList.empty())
            {
                mEffectList.reserve(4);
            }
            mEffectList.pushBack(pEffect);
        }
        mIsAttributeDirty = true;
    }
}
void Attribute::removeEffect(IEffect * pEffect)
{
    if(pEffect)
    {
        
        if(!mEffectList.empty())
        {
            ssize_t index = mEffectList.getIndex(pEffect);
            mEffectList.erase(index);
            mIsAttributeDirty = true;
        }
        pEffect->setTargetAttribute(NULL);
    }
    pEffect->release();//
}

AttributeType Attribute::getKey()
{
    return mAttributeKey;
}


float Attribute::getBaseValue()
{
    return mBaseValue;
}


void Attribute::setBaseValue(float baseValue)
{
    if(mBaseValue != baseValue)
    {
        if(mBaseValue > baseValue)
        {
            if(mIsLockDecrease)
                return;
        }
        if(mBaseValue < baseValue)
        {
            if(mIsLockIncrease)
                return;
        }
        mBaseValue = baseValue;
        mIsAttributeDirty = true;
    }
}


float Attribute::getAfterEffectValue()
{
    return mAfterEffectValue;
}


void Attribute::setAfterEffectValue(float value)
{
    if(mAfterEffectValue != value)
    {
        if(mAfterEffectValue > value)
        {
            if(mIsLockDecrease)
                return;
        }
        if(mAfterEffectValue < value)
        {
            if(mIsLockIncrease)
                return;
        }
        mAfterEffectValue = value;
        //mIsAttributeDirty = true;
    }
}

void Attribute::calculateAfterEffectValue()  //每帧计算，或有effect加入、有effect失效时计算，标记一个attributeDirty
{
    if(!mIsAttributeDirty)
    {
        return;
    }
    /*
    std::<list>::iterator iter;
    for(iter = mEffectList.begin(); iter != mEffectList.end(); ++iter)
    {
        
    }
    */
    //to do
}

void Attribute::update(float dt)
{
    if(!mEffectList.empty())
    {
        int i = 0;
        cocos2d::Vector<IEffect*> toRemoveEffectList;
        for( ; i < mEffectList.size(); i++ )
        {
            auto pEffect = mEffectList.at(i);
            pEffect->updateEffectStatus(dt);
            if(pEffect->getEffectStatus()  == EffectStatus::OVERDUE)
            {
                toRemoveEffectList.pushBack(pEffect);
            }
        }
        int j = 0;
        for(; j < toRemoveEffectList.size(); j++ )
        {
            auto pToRemoveEffect = toRemoveEffectList.at(j);
            removeEffect(pToRemoveEffect);
        }
        
        if(mIsAttributeDirty)
        {
            mIsAttributeDirty = false;
            int i = 0;
            mAfterEffectValue = mBaseValue;
            mIsLockIncrease = false; //恢复默认状态
            mIsLockDecrease = false; //恢复默认状态
            sortAllEffect();
            for( ; i < mEffectList.size(); i++ )
            {
                auto pEffect = mEffectList.at(i);
                if(pEffect->getEffectStatus() == EffectStatus::EFFECTING)
                {
                    pEffect->calcuAfterEffectValue();
                }
            }
            
        }
    }
}

/*
bool Attribute::isAttributeDirty()
{
    return mIsAttributeDirty;
}
*/
void Attribute::setLockIncrease(bool isLock) //禁止属性增加
{
    if(mIsLockIncrease != isLock)
    {
        mIsLockIncrease = isLock;
        mIsAttributeDirty = true;
    }
}

void Attribute::setLockDecrease(bool isLock) //禁止属性减少
{
    if(mIsLockDecrease != isLock)
    {
        mIsLockDecrease = isLock;
        mIsAttributeDirty = true;
    }
}

bool Attribute::isLockIncrease()
{
    return mIsLockIncrease;
}

bool Attribute::isLockDecrease()
{
    return mIsLockDecrease;
}

bool nodeComparisonLess(IEffect* n1, IEffect* n2)
{
    return( n1->getPriority() < n2->getPriority() ||
           ( n1->getPriority() == n2->getPriority() && n1->getStartTime() > n2->getStartTime() )
           );
}

void Attribute::sortAllEffect()
{
    std::sort(std::begin(mEffectList), std::end(mEffectList), nodeComparisonLess);
}