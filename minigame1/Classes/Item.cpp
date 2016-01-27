//
//  Item.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#include "Item.hpp"

Item * Item::create(ItemType type, cocos2d::Vec2 position)
{
    Item * item = new (std::nothrow) Item();
    if (item && item->init(type, position)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}


Item::Item()
{
    if (mItemEffectList.empty()) {
        mItemEffectList.reserve(ITEMEFFECTLISTSIZE);
    }
}

Item::~Item()
{
    mItemEffectList.clear();
}

bool Item::init(ItemType type, cocos2d::Vec2 position)
{
    cocos2d::Size magnetSize;
    cocos2d::Vec2 speed;
  
    float value;
    float time;
    std::string filename;
    
    bool result;
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::string itemid = CommonUtil::itos((int)type + ITEMIDBASE);
    
    // magnet
    std::string magstr = CommonUtil::getPropById(itemid, "magnetsize");
    CCArray * magli = CommonUtil::split(magstr.c_str(), ",");
    magnetSize.width = (dynamic_cast<CCString*>(magli->getObjectAtIndex(0)))->floatValue();
    magnetSize.height = (dynamic_cast<CCString*>(magli->getObjectAtIndex(1)))->floatValue();
    //速度信息
    std::string speedstr = CommonUtil::getPropById(itemid, "speed");
    speedstr.erase(0,1);
    speedstr.erase(speedstr.end()-1, speedstr.end());
    CCArray * speedli = CommonUtil::split(speedstr.c_str(), ",");
    speed.x = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(0)))->floatValue();
    speed.y = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(1)))->floatValue();
   
    //
    value = atof(CommonUtil::getPropById(itemid, "value").c_str());
    //碰撞效果影响时间
    time = atof(CommonUtil::getPropById(itemid, "time").c_str());
    //图片文件名
    filename = CommonUtil::getPropById(itemid, "filename");
    //effectlist
    std::string efflist = CommonUtil::getPropById(itemid, "effectlist");
    CCArray * efflistarr = CommonUtil::split(efflist.c_str(), ",");
    
    Ref * obj;
    
    CCARRAY_FOREACH(efflistarr, obj)
    {
        int temp = dynamic_cast<CCString*>(obj)->intValue();
        mItemEffectList.push_back(temp);
    }
    
    if (BaseDisplayObject::init(position, magnetSize, speed)) {
        mItemType = type;
        
        SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
        actor = Sprite::createWithSpriteFrameName(filename);
        actor->setAnchorPoint(ccp(0,0));
        this->addChild(actor,1);
        
        mValue = value;
        mTime = time;
        
        result = true;
    }
    else
        result = false;
    
    return result;
    
}

ItemType Item::getType()
{
    return mItemType;
}

void Item::update(float dt)
{
    updatePosition(dt);
    updateAttribute(dt);
}

void Item::addCollisionEffect(IDisplayObject *pCollisionTarget)
{
    //发生碰撞，读表生成effect
    for (int i = 0; i < mItemEffectList.size(); i++) {
        
        BaseEffect * effect;
        
        int eftype = mItemEffectList.at(i);
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
        
        if (einstanttype == EffectInstantType::INSTANT) {
            value = this->mValue;
            effect = InstantEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        if (einstanttype == EffectInstantType::DURATION && type == EffectType::MAGNETY) {
            durationtime = this->mTime;
            value = this->mValue;
            effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        if (einstanttype == EffectInstantType::DURATION && type == EffectType::MAGNETX) {
            durationtime = this->mTime;
            value = this->mValue;
            effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        
        if (einstanttype == EffectInstantType::DURATION && type == EffectType::ITEMUPSPEED) {
            durationtime = this->mTime;
            value = this->mValue;
            effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }
        if (einstanttype == EffectInstantType::DURATION && type == EffectType::ITEMINVINCIBLE) {
            durationtime = this->mTime;
            //value = this->mValue;
            effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
        }

        
        //effect->retain();
        pCollisionTarget->addEffect(effect);
    }

}

void Item::onCollision(IDisplayObject *pCollisionTarget)
{
    cocos2d::Rect collisionBox = pCollisionTarget->getMagnetBox();
    if(mCollisionBox.intersectsRect(collisionBox))
    {
        addCollisionEffect(pCollisionTarget);
        auto action = MoveTo::create(5.0f, pCollisionTarget->getPosition());
        this->runAction(action);
        this->mAlive = false;
        this->setVisible(false);
    }
    
}
