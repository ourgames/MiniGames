//
//  Effect.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Effect.hpp"
#include "Attribute.hpp"


DurationEffect::DurationEffect(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType) : BaseEffect( priority,  attributeKey,  startTime,  durationTime,  number,  numberType)
{
    //mEndTime = startTime + durationTime;
}

DurationEffect::~DurationEffect()
{
    
}

void DurationEffect::updateEffectStatus(float dt)
{
    mStartTime = mStartTime - dt;
    mEndTime = mStartTime + mDurationTime;
    if(mEffectStatus == EffectStatus::WAITING)
    {
        if(mStartTime <= 0.0)
        {
            onEffectStart();
            mEffectStatus = EffectStatus::EFFECTING;
        }
    }
    else if(mEffectStatus == EffectStatus::EFFECTING)
    {
        if(mEndTime < 0.0 && mDurationTime > 0.0) //mDurationTime <= 0.0则表示为永久的effect,没有过期时间
        {
            onEffectFinish();
            mEffectStatus = EffectStatus::OVERDUE;
        }
    }
}

void DurationEffect::calcuAfterEffectValue()
{
    if(mEffectStatus != EffectStatus::EFFECTING)
        return;
    IAttribute * pAttribute = mTargetAttribute;
    if(pAttribute)
    {
        //if(mDurationTime > 0.0) //持续类的effect
        {
            if(mNumberType != EffectNumType::Lock) //数值更改类的effect
            {
                float afterValue = 0.0;
                float value = pAttribute->getAfterEffectValue();
                if(mNumberType == EffectNumType::ADD)
                {
                    afterValue = value + mNumber;
                }
                if(mNumberType == EffectNumType::MUL)
                {
                    afterValue = value * mNumber;
                }
                if(mNumberType == EffectNumType::EQUAL)
                {
                    afterValue =  mNumber;
                }
                if(afterValue < 0)
                {
                    afterValue = 0;
                    //to do
                }
                //return afterValue;
                pAttribute->setAfterEffectValue(afterValue);
            }
            
            if(mNumberType == EffectNumType::Lock)
            {
                if(mNumber > 0)
                {
                    pAttribute->setLockIncrease(true);
                }
                else
                {
                    pAttribute->setLockDecrease(true);
                }
                
            }
        }
    }
}

void DurationEffect::onEffectStart()
{
    
}

void DurationEffect::onEffectFinish()
{
    
}


//begin instant effect
InstantEffect::InstantEffect(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType) : BaseEffect( priority,  attributeKey,  startTime,  durationTime,  number,  numberType)
{
    //mEndTime = startTime + durationTime;
}

InstantEffect::~InstantEffect()
{
    
}

void InstantEffect::updateEffectStatus(float dt)
{
    mStartTime = mStartTime - dt;
    mEndTime = mStartTime + mDurationTime;
    if(mEffectStatus == EffectStatus::WAITING)
    {
        if(mStartTime <= 0.0)
        {
            mEffectStatus = EffectStatus::EFFECTING;
            onEffectStart();
        }
    }
    else if(mEffectStatus == EffectStatus::EFFECTING)
    {
        //if(mEndTime < 0.0)
        {
            onEffectFinish();
            mEffectStatus = EffectStatus::OVERDUE;
        }
    }
}

void InstantEffect::calcuAfterEffectValue()
{
}

void InstantEffect::onEffectStart()
{
    IAttribute * pAttribute = mTargetAttribute;
    if(pAttribute)
    {
        //pAttribute->setBaseValue(mNumber);
        float afterValue = 0.0;
        float value = pAttribute->getBaseValue();
        if(mNumberType == EffectNumType::ADD)
        {
            afterValue = value + mNumber;
        }
        if(mNumberType == EffectNumType::MUL)
        {
            afterValue = value * mNumber;
        }
        if(mNumberType == EffectNumType::EQUAL)
        {
            afterValue =  mNumber;
        }
        if(afterValue < 0)
        {
            afterValue = 0;
            //to do
        }
        //return afterValue;
        pAttribute->setBaseValue(afterValue);
    }
}

void InstantEffect::onEffectFinish()
{
    
}
