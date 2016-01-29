//
//  Track.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/29.
//
//

#include "Track.hpp"
#include "GlobalVar.hpp"

Track::Track()
{
//    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
//    //创建背景图片
//    bg = cocos2d::CCArray::createWithCapacity(3);
//    bg->retain();
//    cocos2d::Sprite * _bg;
//    for (int i = 0; i < 3; i++) {
//        _bg = cocos2d::Sprite::create("yejing.jpg");
//        _bg->setAnchorPoint(cocos2d::ccp(0,0));
//        _bg->setPosition(origin.x,origin.y + i * _bg->boundingBox().size.height );
//        //this->addChild(_bg,-100);
//        this->addChild(_bg);
//        bg->addObject(_bg);
//    }
    
    if (mAttributeList.empty()) {
        mAttributeList.reserve(MAXSIZE);
    }
    if (mAttributeKeyList.empty()) {
        mAttributeKeyList.reserve(MAXSIZE);
    }
}

//void Track::bgUpdate(float dt)
//{
//    // 背景移动
//    cocos2d::Sprite * _bg;
//    int _count = bg->count();
//    for (int i = 0; i < _count; i++) {
//        _bg = dynamic_cast<cocos2d::Sprite *>(bg->objectAtIndex(i));
//        if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
//            cocos2d::Sprite * next_bg = dynamic_cast<cocos2d::Sprite *>(bg->objectAtIndex((i + 2) % 3));
//            _bg->setPositionY(next_bg->getPositionY() + next_bg->boundingBox().size.height);
//            _bg->setPositionY(_bg->getPositionY() - 50 * dt);
//        }
//        else
//        {
//            _bg->setPositionY(_bg->getPositionY() - 50 * dt);
//        }
//    }
//    
//}
////
Track::~Track()
{
    mAttributeList.clear();
    mAttributeKeyList.clear();
}

Track * Track::create()
{
    Track * track = new (std::nothrow) Track();
    if (track && track->init()) {
        track->autorelease();
        return track;
    }
    CC_SAFE_DELETE(track);
    return nullptr;
}

bool Track::init()
{
    bool result;
    
    IAttribute * pXSpeedAttribute = Attribute::create(AttributeType::SPEED_X, 0);
    IAttribute * pYSpeedAttribute = Attribute::create(AttributeType::SPEED_Y, 0);
    
    if (pXSpeedAttribute && pYSpeedAttribute ) {
        addAttribute(pXSpeedAttribute);
        addAttribute(pYSpeedAttribute);
        result = true;
    }
    else result = false;
    
    return result;
}

void Track::addAttribute(IAttribute * pAttribute)
{
    if(pAttribute)
    {
        int key = pAttribute->getKey();
        if(mAttributeList.at(key) == nullptr)
        {
            mAttributeList.insert(key, pAttribute);
            pAttribute->setDisplayObject(this);
            mAttributeKeyList.push_back(key);
        }
        
    }
}

void Track::addEffect(IEffect * pEffect)
{
    if(!pEffect)
        return;
    int key = pEffect->getAttributeKey();
    IAttribute * pAttribute = mAttributeList.at(key);
    if(pAttribute)
    {
        pAttribute->addEffect(pEffect);
    }
}

void Track::update(float dt)
{
    //bgUpdate(dt);
    updatePosition(dt);
    updateAttribute(dt);
}

 void Track::updatePosition(float dt)
{
    float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
    float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
    this->setPositionX(this->getPositionX() + dt * xSpeed);
    this->setPositionY(this->getPositionY() + dt * ySpeed);
    
}
 void Track::updateAttribute(float dt)
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
