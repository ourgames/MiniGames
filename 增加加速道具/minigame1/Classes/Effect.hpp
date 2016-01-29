//
//  Effect.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>

#include <string>
using namespace std;

class IAttribute;

typedef enum
{
    SPEED_X, //X方向速度
    SPEED_Y, //Y方向速度
    STAMINA,//体力
    SOCRE,//分数
    COLLISION_SIZE_X,//X方向碰撞距离
    COLLISION_SIZE_Y,//Y方向碰撞距离
    MAGNET_SIZE_X,//X方向吸收距离
    MAGNET_SIZE_Y,//Y方向吸收距离
    POSITION_X,//X方向位置信息
    POSITION_Y,//Y方向位置信息
    
}AttributeType;

typedef enum
{
    WAITING, //等待生效
    EFFECTING, //正在生效
    OVERDUE, //已经过期失效
}EffectStatus;

class IEffect : public cocos2d::Ref
{
public:
    //virtual void updateEffectTime(float ) = 0;
    virtual float getStartTime() = 0;
    //virtual float getEndTime() = 0;
    //virtual float getDurationTime() = 0;
    virtual void updateEffectStatus(float ) = 0;
    virtual EffectStatus getEffectStatus() = 0;
    virtual AttributeType getAttributeKey() = 0;
    virtual void calcuAfterEffectValue() = 0;
    virtual int getPriority() = 0;
    //virtual void onEffectStart() = 0;
    //virtual void onEffectFinish() = 0;
    virtual void setTargetAttribute(IAttribute * pAttribute) = 0;
    
    virtual ~IEffect() {}
};

typedef enum
{
    ADD,
    MUL,
    EQUAL,
    LOCK,
}EffectNumType;

typedef enum
{
    INSTANT,//立即生效的effect
    DURATION,//持续生效的effect
}EffectInstantType;

typedef enum
{
    BLOCKHITSTAMINA,//碰撞时体力影响的effect
    BLOCKAVOIDSCORE,//未碰撞，躲过得分的effect
    BLCOKDIZZY,//眩晕障碍
    ITEMUPSPEED,//加速
    ITEMINVINCIBLE,//无敌
    MAGNETX,//X方向吸引距离
    MAGNETY,//Y方向吸引距离
    LEFTTOUCH,//左侧触摸，追踪障碍添加左侧toucheffect
    RIGHTTOUCH,//右侧触摸，追踪障碍添加右侧toucheffect
    PLAYERSTAMINA,//玩家体力值每帧减少值的effect
    POSITIONX,//X方向位置信息
    POSITIONY,//Y方向位置信息
}EffectType;

typedef enum
{
    LEFT,
    RIGHT,
}TouchDirection;//触摸方向

class BaseEffect : public IEffect
{
public:
    BaseEffect(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType) : mPriority(priority), mAttributeKey(attributeKey), mStartTime(startTime), mDurationTime(durationTime), mNumber(number), mNumberType(numberType)
    {
        mEndTime = startTime + durationTime;
        mEffectStatus = EffectStatus::WAITING;
    }
    virtual ~BaseEffect() {}
    virtual EffectStatus getEffectStatus() {return mEffectStatus;}
    virtual AttributeType getAttributeKey() {return mAttributeKey; }
    virtual int getPriority() {return mPriority; }
    virtual void setTargetAttribute(IAttribute * pAttribute) {mTargetAttribute = pAttribute;}
    virtual float getStartTime() {return mStartTime; }
protected:
    int mPriority;
    AttributeType mAttributeKey;
    float mStartTime;
    float mDurationTime;
    float mEndTime;
    float mNumber;
    EffectNumType mNumberType;
    EffectStatus mEffectStatus;
    IAttribute * mTargetAttribute;
};

class DurationEffect : public BaseEffect
{
public:
    DurationEffect(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType);
    virtual ~DurationEffect();
    
    static DurationEffect * create(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType);
    virtual bool init();
    
    //virtual void updateEffectTime(float dt);
    //virtual float getStartTime();
    //virtual float getEndTime();
    //virtual float getDurationTime();
    virtual void updateEffectStatus(float dt) ;
    //virtual EffectStatus getEffectStatus() ;
    //virtual string getAttributeKey();
    virtual void calcuAfterEffectValue();
    //virtual int getPriority();
    virtual void onEffectStart() ;
    virtual void onEffectFinish() ;
    
    
private:
    
};

class InstantEffect : public BaseEffect
{
public:
    InstantEffect(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType);
    virtual ~InstantEffect();
    
    static InstantEffect * create(int priority, AttributeType attributeKey, float startTime, float durationTime, float number, EffectNumType numberType);
    virtual bool init();
    //virtual void updateEffectTime(float dt);
    //virtual float getStartTime();
    //virtual float getEndTime();
    //virtual float getDurationTime();
    virtual void updateEffectStatus(float dt) ;
    //virtual EffectStatus getEffectStatus() ;
    //virtual string getAttributeKey();
    virtual void calcuAfterEffectValue();
    //virtual int getPriority();
    virtual void onEffectStart() ;
    virtual void onEffectFinish() ;
    
    
private:
    
};
#endif /* Effect_hpp */
