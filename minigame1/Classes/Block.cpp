//
//  Block.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#include "Block.hpp"

//BaseBlock::BaseBlock(cocos2d::Vec2 position, cocos2d::Size collisionSize, cocos2d::Vec2 speed,BlockType type):BaseDisplayObject(position, collisionSize, speed),mBlockType(type)
//{
//    
//}

BaseBlock * BaseBlock::create(BlockType type, cocos2d::Vec2 position)
{
    BaseBlock * baseblock = new (std::nothrow) BaseBlock();
    if (baseblock && baseblock->init(type,position)) {
        baseblock->autorelease();
        return baseblock;
    }
    CC_SAFE_DELETE(baseblock);
    return nullptr;
}

BaseBlock::BaseBlock()
{
    if (mBlockEffectList.empty()) {
        mBlockEffectList.reserve(BLOCKEFFECTLISTSIZE);
    }
}

bool BaseBlock::init(BlockType type, cocos2d::Vec2 position)
{
    cocos2d::Size collisionSize;
    cocos2d::Vec2 speed;
    float score;
    float stamina;
    float time;
    std::string filename;
    
    bool result;

    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::string blockid = CommonUtil::itos((int)type + BLOCKIDBASE);
    
    //碰撞盒信息
    std::string collision = CommonUtil::getPropById(blockid, "collision");
    CCArray * colli = CommonUtil::split(collision.c_str(), ",");
    collisionSize.width = (dynamic_cast<CCString*>(colli->getObjectAtIndex(0)))->floatValue();
    collisionSize.height = (dynamic_cast<CCString*>(colli->getObjectAtIndex(1)))->floatValue();
    //速度信息
    std::string speedstr = CommonUtil::getPropById(blockid, "speed");
    speedstr.erase(0,1);
    speedstr.erase(speedstr.end()-1, speedstr.end());
    CCArray * speedli = CommonUtil::split(speedstr.c_str(), ",");
    speed.x = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(0)))->floatValue();
    speed.y = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(1)))->floatValue();
    //躲过得分数
    score = atof(CommonUtil::getPropById(blockid, "score").c_str());
    //碰撞消耗的体力值
    stamina = atof(CommonUtil::getPropById(blockid, "stamina").c_str());
    //碰撞效果影响时间
    time = atof(CommonUtil::getPropById(blockid, "time").c_str());
    //图片文件名
    filename = CommonUtil::getPropById(blockid, "filename");
    //effectlist
    std::string efflist = CommonUtil::getPropById(blockid, "effectlist");
    CCArray * efflistarr = CommonUtil::split(efflist.c_str(), ",");
    
    Ref * obj;
   
    CCARRAY_FOREACH(efflistarr, obj)
    {
        int temp = dynamic_cast<CCString*>(obj)->intValue();
        mBlockEffectList.push_back(temp);
    }
    
    if (BaseDisplayObject::init(position, collisionSize, speed)) {
        mBlockType = type;
        
        SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
        actor = Sprite::createWithSpriteFrameName(filename);
        //actor->setScale(0.7);
        //actor->setPosition(visibleSize.width/2, visibleSize.height/2);
        //actor = Sprite::create(filename);
        this->addChild(actor,1);
        
        mScore = score;
        mStamina = stamina;
        mTime = time;
        
        result = true;
    }
    else
        result = false;
    
    return result;
}

BlockType BaseBlock::getType()
{
    return mBlockType;
}

void BaseBlock::update(float dt)
{
    updatePosition(dt);
    updateAttribute(dt);
}

BaseBlock::~BaseBlock()
{
    mBlockEffectList.clear();
}

void BaseBlock::addCollisionEffect(IDisplayObject *pCollisionTarget)
{
    //发生碰撞，读表生成effect
    for (int i = 0; i < mBlockEffectList.size(); i++) {
        
        BaseEffect * effect;
        
        int eftype = mBlockEffectList.at(i);
        std::string eftypestr = CommonUtil::itos(eftype + EFFECTIDBASE);
        
        //
        int priority = atoi(CommonUtil::getPropById(eftypestr, "priority").c_str());
        
        AttributeType attributekey = (AttributeType)atoi(CommonUtil::getPropById(eftypestr, "attributekey").c_str());
        
        float starttime = atof(CommonUtil::getPropById(eftypestr, "starttime").c_str());
        
        float durationtime = atof(CommonUtil::getPropById(eftypestr, "durationtime").c_str());
        
        float value = atof(CommonUtil::getPropById(eftypestr, "value").c_str());
        //effect numtype
        EffectNumType enumtype = (EffectNumType)atoi(CommonUtil::getPropById(eftypestr, "enumtype").c_str());
        //
        EffectInstantType  einstanttype = (EffectInstantType)atoi(CommonUtil::getPropById(eftypestr, "instantable").c_str());
        //effect的type类型
        EffectType type = (EffectType)atoi(CommonUtil::getPropById(eftypestr, "type").c_str());
        
        if (einstanttype == EffectInstantType::INSTANT && type == EffectType::BLOCKHITSTAMINA) {
            value = this->mStamina;
            effect = InstantEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        if (einstanttype == EffectInstantType::DURATION && type == EffectType::BLCOKDIZZY) {
            durationtime = this->mTime;
            effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        effect->retain();
        pCollisionTarget->addEffect(effect);
    }
    
}

void BaseBlock::addAvoidEffect(IDisplayObject *pCollisionTarget)
{
    //发生碰撞，读表生成effect
    for (int i = 0; i < mBlockEffectList.size(); i++) {
        
        BaseEffect * effect;
        
        int eftype = mBlockEffectList.at(i);
        std::string eftypestr = CommonUtil::itos(eftype + EFFECTIDBASE);
        
        //
        int priority = atoi(CommonUtil::getPropById(eftypestr, "priority").c_str());
        
        AttributeType attributekey = (AttributeType)atoi(CommonUtil::getPropById(eftypestr, "attributekey").c_str());
        
        float starttime = atof(CommonUtil::getPropById(eftypestr, "starttime").c_str());
        
        float durationtime = atof(CommonUtil::getPropById(eftypestr, "durationtime").c_str());
        
        float value = atof(CommonUtil::getPropById(eftypestr, "value").c_str());
        //effect numtype
        EffectNumType enumtype = (EffectNumType)atoi(CommonUtil::getPropById(eftypestr, "enumtype").c_str());
        //
        EffectInstantType  einstanttype = (EffectInstantType)atoi(CommonUtil::getPropById(eftypestr, "instantable").c_str());
        //effect的type类型
        EffectType type = (EffectType)atoi(CommonUtil::getPropById(eftypestr, "type").c_str());
        
        if (einstanttype == EffectInstantType::INSTANT && type == EffectType::BLOCKAVOIDSCORE) {
            value = this->mScore;
            effect = InstantEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        effect->retain();
        pCollisionTarget->addEffect(effect);
    }
    
}

void BaseBlock::onCollision(IDisplayObject *pCollisionTarget)
{
    if(mCollisionBox.intersectsRect(pCollisionTarget->getCollisionBox()))
    {
        addCollisionEffect(pCollisionTarget);
        this->mAlive = false;
        this->setVisible(false);
    }
    
}

void BaseBlock::onAvoid(IDisplayObject *pCollisionTarget)
{
    if(this->mPosition.y < pCollisionTarget->getPosition().y) {
        addAvoidEffect(pCollisionTarget);
    }
}




